#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"

typedef struct{
	int id;
	char* nombre;
	int PC;
	int PS;
	char* sexo;
}Pokemon_usuario;

typedef struct{
	char* nombre;
	int existencia;
	char* tipo;
	char* evolucionPrevia;
	char* evolucionPosterior;
	int numeroPokedex;
	char* region;
}Pokedex;

typedef struct{
	Pokemon_usuario* PokUser; 
	Pokedex* Px;
}infoPokemon;


char *get_csv_field (char * tmp, int k){
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}

Map *importarExportarPokemonDesdeUnArchivo(Map *MapaPokemon, char *nombre_archivo){
	int opcionIoE;
	printf("\nImportar (1) o Exportar (2) archivo .csv\n");
	scanf("%d", &opcionIoE);

	//EXPORTAR ARCHIVO .CSV//
	if(opcionIoE == 2){
		if(MapaPokemon == NULL){
			printf("\nImportar!\n");
			return MapaPokemon;
		}
		printf("\nIngrese nombre del archivo .csv\n");
		scanf("%[^\n]s", nombre_archivo);

		//ABIR ARCHIVO A EXPORTAR //
		FILE *fp = fopen(nombre_archivo, "wt");
		
		char linea[1000];
		char *aux;
		int i, TotalPokemon;
		infoPokemon *P;

		fputs("id,nombre,tipos,pc,ps,sexo,evolucion previa,evolucion posterior,numero pokedex,region\n", nombre_archivo);

		aux = (infoPokemon*) firstMap(MapaPokemon);
		while(i < TotalPokemon){
			fprintf(nombre_archivo, "%d,%s,", P->PokUser->id, P->PokUser->nombre);
			fprintf(nombre_archivo, "%s,%d,", P->Px->tipo, P->PokUser->PC);
			fprintf(nombre_archivo, "%d,%s,", P->PokUser->PS, P->PokUser->sexo);
			fprintf(nombre_archivo, "%s,%s,", P->Px->evolucionPrevia, P->Px->evolucionPosterior);
			fprintf(nombre_archivo, "%d,%s\n", P->Px->numeroPokedex, P->Px->region);
			i++;
			aux = (infoPokemon*) nextMap(MapaPokemon);
		}

		//CERRRAR ARCHIVO EXPORTADO //
		fclose(nombre_archivo);
                return MapaPokemon;
	}
	
	//IMPORTAR ARCHIVO .CSV//
	printf("\nIngrese nombre del archivo .csv\n");
	scanf("%[^\n]s", nombre_archivo);
	getchar();
	//ABRIR ARCHIVO A IMPORTAR //
	FILE *fp = fopen(nombre_archivo, "r");
	if(fp == NULL){
		printf("\nARCHIVO NO ENCONTRADO\n");
		return MapaPokemon;
	}

	char linea[1000];
	char * aux;
	infoPokemon *P;
	int i, key_id;

	//SALTAR LECTURA DE LA PRIMERA LINEA //
	fgets(linea, 1000, fp);

	//LECTURA DE DATOS POR LINEA//
	while( fgets(linea, 1000, fp) != NULL){

		P = (infoPokemon*) malloc(sizeof(infoPokemon));

		P->PokUser = (Pokemon_usuario*)malloc(sizeof(Pokemon_usuario));
		P->PokUser->nombre = malloc(50*sizeof(char));
		P->PokUser->sexo = malloc(7*sizeof(char));

		P->Px = malloc(sizeof(Pokedex));
		P->Px->evolucionPosterior = malloc(20*sizeof(char));
		P->Px->evolucionPrevia = malloc(20*sizeof(char));
		P->Px->nombre = malloc(50*sizeof(char));
		P->Px->region = malloc(20*sizeof(char));
		P->Px->tipo = malloc(20*sizeof(char));
		//EXISTENCIA
		P->Px->existencia = 1;

		for(i = 0; i <10; i++){
			
			//ID
			if(i == 0){
				aux = get_csv_field(linea,i);
				P->PokUser->id = atoi(aux);
				key_id = P->PokUser->id;
			}

			//NOMBRE
			if(i == 1){
				P->PokUser->nombre = get_csv_field(linea,i);
				strcpy(P->Px->nombre, P->PokUser->nombre);
			}

			//TIPO
			if(i == 2){
				P->Px->tipo = get_csv_field(linea,i);
			}

			//PC
			if(i == 3){
				aux = get_csv_field(linea,i);
				P->PokUser->PC = atoi(aux);
			}

			//PS
			if(i == 4){
				aux = get_csv_field(linea,i);
				P->PokUser->PC = atoi(aux);
			}

			//SEXO
			if(i == 5){
				P->PokUser->sexo = get_csv_field(linea,i);
			}

			//EVOLUCION PREVIA
			if(i == 6){
				P->Px->evolucionPrevia = get_csv_field(linea,i);
			}

			//EVOLUCION POSTERIOR
			if(i == 7){
				P->Px->evolucionPosterior = get_csv_field(linea,i);
			}

			//NUMERO POKEDEX
			if(i == 8){
				aux = get_csv_field(linea,i);
				P->Px->numeroPokedex = atoi(aux);
			}

			//REGION
			if(i == 9){
				P->Px->region = get_csv_field(linea,i);
			}

		}
		//INSERTAR EN MAPA //
		insertMap(MapaPokemon,key_id,P);
	}
	//CERRAR ARCHIVO IMPORTADO//
	fclose(nombre_archivo);
	return MapaPokemon;
}
