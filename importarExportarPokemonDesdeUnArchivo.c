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

/*
  función para comparar claves de tipo int
  retorna 1 si son iguales
*/
int is_equal_int(void * key1, void * key2) {
    if(*(int*)key1 == *(int*)key2) return 1;
    return 0;
}

/*
  función para comparar claves de tipo int
  retorna 1 si son key1<key2
*/
int lower_than_int(void * key1, void * key2) {
    if(*(int*)key1 < *(int*)key2) return 1;
    return 0;
}

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

Map *importarExportarPokemonDesdeUnArchivo(char *nombre_archivo, Map *MapaPokemon, int *totalPokemon){
	//CREAR MAPA //
	MapaPokemon = createMap(is_equal_int);

	char opcionIoE[100];
	printf("\nImportar (1) o Exportar (2) archivo .csv: ");
	scanf("%[^\n]s", opcionIoE);
    getchar();
	

	//EXPORTAR ARCHIVO .CSV//
	if(opcionIoE[0] == 2){
		if(MapaPokemon == NULL){
			printf("\nImportar!\n");
			return MapaPokemon;
		}
		printf("\nIngrese nombre del archivo .csv: ");
		scanf("%s", nombre_archivo);

		//ABIR ARCHIVO A EXPORTAR //
		FILE *fp = fopen(nombre_archivo, "r+");
		
		char linea[1000];
		int i;
		infoPokemon *P;

		//ESCRIBIR INFO EN ARCHIVO A EXPORTAR //
		fprintf( fp, "id,nombre,tipos,pc,ps,sexo,evolucion previa,evolucion posterior,numero pokedex,region\n");

		P = (infoPokemon*) firstMap(MapaPokemon);
		while(i < *totalPokemon){
			fprintf(fp, "%d,%s,", P->PokUser->id, P->PokUser->nombre);
			fprintf(fp, "%s,%d,", P->Px->tipo, P->PokUser->PC);
			fprintf(fp, "%d,%s,", P->PokUser->PS, P->PokUser->sexo);
			fprintf(fp, "%s,%s,", P->Px->evolucionPrevia, P->Px->evolucionPosterior);
			fprintf(fp, "%d,%s\n", P->Px->numeroPokedex, P->Px->region);
			i++;
			P = (infoPokemon*) nextMap(MapaPokemon);
		}

		//CERRRAR ARCHIVO EXPORTADO //
		fclose(fp);
		return MapaPokemon;
	}
	
	//IMPORTAR ARCHIVO .CSV //
	printf("\nIngrese nombre del archivo .csv: ");
	scanf("%[^\n]s", nombre_archivo);
	getchar();

	//NOTA: LUEGO QUE INGRESO NOMBRE DEL ARCHIVO ME BOTA DEL PROGRAMA :( // 

	//ABRIR ARCHIVO A IMPORTAR //
	FILE *fp = fopen(nombre_archivo, "r");
	if(fp == NULL){
		printf("\nARCHIVO NO ENCONTRADO\n");
		return MapaPokemon;
	}

	char linea[1000];
	char * aux;
	infoPokemon *P;
	int i;

	//SALTAR LECTURA DE LA PRIMERA LINEA //
	fgets(linea, 1000, fp);

	//DIMENSIONAR VARIABLES //
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

	//LECTURA DE DATOS POR LINEA //
	while( fgets(linea, 1000, fp) != NULL){

		//EXISTENCIA
		P->Px->existencia = 1;

		for(i = 0; i <10; i++){
			
			//ID
			if(i == 0){
				aux = get_csv_field(linea,i);
				P->PokUser->id = atoi(aux);

				printf("\n%d\n", P->PokUser->id);
			}

			//NOMBRE
			if(i == 1){
				P->PokUser->nombre = get_csv_field(linea,i);
				strcpy(P->Px->nombre, P->PokUser->nombre);

				printf("\n%s\n\n%s\n", P->PokUser->nombre, P->Px->nombre);
			}

			//TIPO
			if(i == 2){
				P->Px->tipo = get_csv_field(linea,i);

				printf("\n%s\n", P->Px->tipo);
			}

			//PC
			if(i == 3){
				aux = get_csv_field(linea,i);
				P->PokUser->PC = atoi(aux);

				printf("\n%d\n", P->PokUser->PC);
			}

			//PS
			if(i == 4){
				aux = get_csv_field(linea,i);
				P->PokUser->PC = atoi(aux);

				printf("\n%d\n", P->PokUser->PS);
			}

			//SEXO
			if(i == 5){
				P->PokUser->sexo = get_csv_field(linea,i);

				printf("\n%s\n", P->PokUser->sexo);
			}

			//EVOLUCION PREVIA
			if(i == 6){
				P->Px->evolucionPrevia = get_csv_field(linea,i);

				printf("\n%s\n", P->Px->evolucionPrevia);
			}

			//EVOLUCION POSTERIOR
			if(i == 7){
				P->Px->evolucionPosterior = get_csv_field(linea,i);

				printf("\n%s\n", P->Px->evolucionPosterior);
			}

			//NUMERO POKEDEX
			if(i == 8){
				aux = get_csv_field(linea,i);
				P->Px->numeroPokedex = atoi(aux);

				printf("\n%d\n", P->Px->numeroPokedex);
			}

			//REGION
			if(i == 9){
				P->Px->region = get_csv_field(linea,i);

				printf("\n%s\n", P->Px->region);
			}

		}
		*totalPokemon++;
		//INSERTAR EN MAPA //
		insertMap(MapaPokemon, &P->PokUser->id, P);
	}
	//CERRAR ARCHIVO IMPORTADO//
	fclose(fp);
	return MapaPokemon;
}