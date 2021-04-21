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
	do{
		memset(opcionIoE, '\0', 100);
		printf("\nopcion 1: Importar archivo.csv\n");
		printf("opcion 2: Exportar archivo .csv\n");
		printf("\nIngrese opcion: ");
		scanf("%[^\n]s", opcionIoE);
		getchar();

		if(opcionIoE[1] != '\0'){
			printf("\nPor favor ingrese opcion valida\n");
		}

	}while( (opcionIoE[0] < '1') || (opcionIoE[0] > '2'));


	//EXPORTAR ARCHIVO .CSV//
	if(opcionIoE[0] == '2'){
		if(MapaPokemon == NULL){
			printf("\nImportar!\n");
			return MapaPokemon;
		}
		printf("\nIngrese nombre del archivo .csv: ");
		scanf("%[^\n]s", nombre_archivo);
		getchar();

		//ABIR ARCHIVO A EXPORTAR //
		FILE *fp = fopen(nombre_archivo, "r+");
		
		char linea[1000];
		int i;
		infoPokemon *P;

		//ESCRIBIR INFO EN ARCHIVO A EXPORTAR //
		fprintf( fp, "id,nombre,tipos,pc,ps,sexo,evolucion previa,evolucion posterior,numero pokedex,region\n");

		P = (infoPokemon*) firstMap(MapaPokemon);
		while(P != NULL){
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
		printf("\nArchivo .csv exportado con exito!\n");
		return MapaPokemon;
	}
	
	//IMPORTAR ARCHIVO .CSV //
	printf("\nIngrese nombre del archivo .csv: ");
	scanf("%[^\n]s", nombre_archivo);
	getchar();

	//ABRIR ARCHIVO A IMPORTAR //
	FILE *fp = fopen(nombre_archivo, "r");
	if(fp == NULL){
		printf("\nARCHIVO NO ENCONTRADO\n");
		return MapaPokemon;
	}

	char linea[2000];
	char * aux;
	infoPokemon *P;
	int i;

	//SALTAR LECTURA DE LA PRIMERA LINEA //
	fgets(linea, 1000, fp);

	//LECTURA DE DATOS POR LINEA //
	while( fgets(linea, 2000, fp) != NULL){

		//DIMENSIONAR VARIABLES //
		P = (infoPokemon*) malloc(sizeof(infoPokemon));
		if(P == NULL){
			printf("Error en inicializar memoria en variable P\n\n");
			exit(1);
		}

		P->PokUser = (Pokemon_usuario*)malloc(sizeof(Pokemon_usuario));
		if(P->PokUser == NULL){
			printf("Error en inicializar memoria en variable P->PokUser\n\n");
			exit(1);
		}
		P->PokUser->nombre = malloc(50*sizeof(char));
		if(P->PokUser->nombre == NULL){
			printf("Error en inicializar memoria en variable P->PokUser->nombre\n\n");
			exit(1);
		}
		P->PokUser->sexo = malloc(7*sizeof(char));
		if(P->PokUser->sexo == NULL){
			printf("Error en inicializar memoria en variable P->PokUser->sexo\n\n");
			exit(1);
		}

		P->Px = malloc(sizeof(Pokedex));
		if(P->Px == NULL){
			printf("Error en inicializar memoria en variable P->Px\n\n");
			exit(1);
		}
		P->Px->evolucionPosterior = malloc(20*sizeof(char));
		if(P->Px->evolucionPosterior == NULL){
			printf("Error en inicializar memoria en variable P->Px->evolucionPosterior\n\n");
			exit(1);
		}
		P->Px->evolucionPrevia = malloc(20*sizeof(char));
		if(P->Px->evolucionPrevia == NULL){
			printf("Error en inicializar memoria en variable P->Px->evolucionPrevia\n\n");
			exit(1);
		}
		P->Px->nombre = malloc(50*sizeof(char));
		if(P->Px->nombre == NULL){
			printf("Error en inicializar memoria en variable P->Px->nombre\n\n");
			exit(1);
		}
		P->Px->region = malloc(20*sizeof(char));
		if(P->Px->region == NULL){
			printf("Error en inicializar memoria en variable P->Px->region\n\n");
			exit(1);
		}
		P->Px->tipo = malloc(30*sizeof(char));
		if(P->Px->tipo == NULL){
			printf("Error en inicializar memoria en variable P->Px->tipo\n\n");
			exit(1);
		}

		//EXISTENCIA
		P->Px->existencia = 1;

		for(i = 0; i <10; i++){
			
			//ID
			if(i == 0){
				aux = get_csv_field(linea,i);
				P->PokUser->id = atoi(aux);

				printf("\n%d - ", P->PokUser->id);
			}

			//NOMBRE
			if(i == 1){
				P->PokUser->nombre = get_csv_field(linea,i);
				strcpy(P->Px->nombre, P->PokUser->nombre);

				printf("%s - %s - ", P->PokUser->nombre, P->Px->nombre);
			}

			//TIPO
			if(i == 2){
				P->Px->tipo = get_csv_field(linea,i);

				printf("%s - ", P->Px->tipo);
			}

			//PC
			if(i == 3){
				aux = get_csv_field(linea,i);
				P->PokUser->PC = atoi(aux);

				printf("%d - ", P->PokUser->PC);
			}

			//PS
			if(i == 4){
				aux = get_csv_field(linea,i);
				P->PokUser->PS = atoi(aux);

				printf("%d - ", P->PokUser->PS);
			}

			//SEXO
			if(i == 5){
				P->PokUser->sexo = get_csv_field(linea,i);

				printf("%s - ", P->PokUser->sexo);
			}

			//EVOLUCION PREVIA
			if(i == 6){
				P->Px->evolucionPrevia = get_csv_field(linea,i);

				printf("%s - ", P->Px->evolucionPrevia);
			}

			//EVOLUCION POSTERIOR
			if(i == 7){
				P->Px->evolucionPosterior = get_csv_field(linea,i);

				printf("%s - ", P->Px->evolucionPosterior);
			}

			//NUMERO POKEDEX
			if(i == 8){
				aux = get_csv_field(linea,i);
				P->Px->numeroPokedex = atoi(aux);

				printf("%d - ", P->Px->numeroPokedex);
			}

			//REGION
			if(i == 9){
				P->Px->region = get_csv_field(linea,i);

				printf("%s\n", P->Px->region);
			}

		}
		//INSERTAR EN MAPA //
		insertMap(MapaPokemon, &P->PokUser->id, P);

		*totalPokemon = *totalPokemon + 1;
	}
	//CERRAR ARCHIVO IMPORTADO//
	fclose(fp);
	printf("\nImportacion realizada con exito\n\n");
	printf("TOTAL POKEMON: %d\n", *totalPokemon);
	return MapaPokemon;
}