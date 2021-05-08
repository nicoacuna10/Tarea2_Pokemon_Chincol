#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

void importarExportarPokemonDesdeUnArchivo(char *nombre_archivo, Map **PokemonUsuario_id, Map **Pokedex_num, Map **Pokedex_nombre,int *totalPokemon, int *totalPokemonPokedex){

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
		// Si no se ha importado, se muestra un mensaje indicando que primero importe un archivo .csv //
		if(*totalPokemon == 0 || *totalPokemonPokedex == 0){
			printf("\nImportar!\n");
			return;
		}
		printf("\nIngrese nombre del archivo .csv: ");
		scanf("%[^\n]s", nombre_archivo);
		getchar();

		//ABIR ARCHIVO A EXPORTAR //
		FILE *fp = fopen(nombre_archivo, "w");
		if(fp == NULL){
			printf("Error al abrir archivo\n\n");
			return;
		}
		
		char linea[1000];
		int contadorTipos;
		Pokemon_usuario *PokUser;
		Pokedex *Px;

		//ESCRIBIR INFO EN ARCHIVO A EXPORTAR //
		fprintf( fp, "id,nombre,tipos,pc,ps,sexo,evolucion previa,evolucion posterior,numero pokedex,region\n");

		// Se recorre el almacenamiento del usuario para escribir la información en el archivo a exportar //
		PokUser = (Pokemon_usuario*) firstMap(*PokemonUsuario_id);
		while(PokUser != NULL){

			// Se busca la información del pokemon en la Pokedex
			Px = (Pokedex*) searchMap(*Pokedex_nombre, PokUser->nombre);
			
			/* Se usa un contador para obtener la cantidad de tipos que tiene el Pokemon. El contador comienza en uno,
			   se recorre la cadena de caracteres y cada vez que se encuentre una coma se suma 1 al contador */
			contadorTipos = 1;
			for(int i = 0; Px->tipo[i]; i++){
				if(Px->tipo[i] == ',') contadorTipos++;
			}

			/* Se escribe en el archivo la información de el pokemon. Si el pokemon tiene más de un tipo, estos se 
			   escriben entre comillas.*/
			if(contadorTipos > 1){
				fprintf(fp, "%d,%s,\"%s\",%d,%d,%s,%s,%s,%d,%s\n", PokUser->id, PokUser->nombre, Px->tipo, PokUser->PC, PokUser->PS, PokUser->sexo, Px->evolucionPrevia, Px->evolucionPosterior, Px->numeroPokedex, Px->region);
			}else fprintf(fp, "%d,%s,%s,%d,%d,%s,%s,%s,%d,%s\n", PokUser->id, PokUser->nombre, Px->tipo, PokUser->PC, PokUser->PS, PokUser->sexo, Px->evolucionPrevia, Px->evolucionPosterior, Px->numeroPokedex, Px->region);

			PokUser = (Pokemon_usuario*) nextMap(*PokemonUsuario_id);
		}

		//CERRRAR ARCHIVO EXPORTADO //
		fclose(fp);
		printf("\nArchivo .csv exportado con exito!\n");
		return;
	}
	
	//IMPORTAR ARCHIVO .CSV //
	printf("\nIngrese nombre del archivo .csv: ");
	scanf("%[^\n]s", nombre_archivo);
	getchar();

	//ABRIR ARCHIVO A IMPORTAR //
	FILE *fp = fopen(nombre_archivo, "r");
	if(fp == NULL){
		printf("\nARCHIVO NO ENCONTRADO\n");
		return;
	}

	char linea[2000];
	Pokemon_usuario *PokUser;
	Pokedex *Px;
	int i;

	//SALTAR LECTURA DE LA PRIMERA LINEA //
	fgets(linea, 1000, fp);

	//LECTURA DE DATOS POR LINEA //
	while( fgets(linea, 2000, fp) != NULL){

		//DIMENSIONAR VARIABLES //

		PokUser = (Pokemon_usuario*)malloc(sizeof(Pokemon_usuario));
		if(PokUser == NULL){
			printf("Error en inicializar memoria en variable P->PokUser\n\n");
			exit(1);
		}
		PokUser->nombre = malloc(50*sizeof(char));
		if(PokUser->nombre == NULL){
			printf("Error en inicializar memoria en variable P->PokUser->nombre\n\n");
			exit(1);
		}
		PokUser->sexo = malloc(9*sizeof(char));
		if(PokUser->sexo == NULL){
			printf("Error en inicializar memoria en variable P->PokUser->sexo\n\n");
			exit(1);
		}

		Px = (Pokedex*) malloc(sizeof(Pokedex));
		if(Px == NULL){
			printf("Error en inicializar memoria en variable P->Px\n\n");
			exit(1);
		}
		Px->evolucionPosterior = malloc(20*sizeof(char));
		if(Px->evolucionPosterior == NULL){
			printf("Error en inicializar memoria en variable P->Px->evolucionPosterior\n\n");
			exit(1);
		}
		Px->evolucionPrevia = malloc(20*sizeof(char));
		if(Px->evolucionPrevia == NULL){
			printf("Error en inicializar memoria en variable P->Px->evolucionPrevia\n\n");
			exit(1);
		}
		Px->nombre = malloc(50*sizeof(char));
		if(Px->nombre == NULL){
			printf("Error en inicializar memoria en variable P->Px->nombre\n\n");
			exit(1);
		}
		Px->region = malloc(20*sizeof(char));
		if(Px->region == NULL){
			printf("Error en inicializar memoria en variable P->Px->region\n\n");
			exit(1);
		}
		Px->tipo = malloc(30*sizeof(char));
		if(Px->tipo == NULL){
			printf("Error en inicializar memoria en variable P->Px->tipo\n\n");
			exit(1);
		}

		//EXISTENCIA
		Px->existencia = 1;

		// 10 elementos que se leen del archivo .csv
		for(i = 0; i <10; i++){
			char * aux;
			
			//ID
			if(i == 0){
				aux = get_csv_field(linea,i);
				PokUser->id = atoi(aux);

				printf("\n%d - ", PokUser->id);
			}

			//NOMBRE
			if(i == 1){
				PokUser->nombre = get_csv_field(linea,i);
				strcpy(Px->nombre, PokUser->nombre);

				printf("%s - %s - ", PokUser->nombre, Px->nombre);
			}

			//TIPO
			if(i == 2){
				Px->tipo = get_csv_field(linea,i);

				printf("%s - ", Px->tipo);
			}

			//PC
			if(i == 3){
				aux = get_csv_field(linea,i);
				PokUser->PC = atoi(aux);

				printf("%d - ", PokUser->PC);
			}

			//PS
			if(i == 4){
				aux = get_csv_field(linea,i);
				PokUser->PS = atoi(aux);

				printf("%d - ", PokUser->PS);
			}

			//SEXO
			if(i == 5){
				PokUser->sexo = get_csv_field(linea,i);

				printf("%s - ", PokUser->sexo);
			}

			//EVOLUCION PREVIA
			if(i == 6){
				Px->evolucionPrevia = get_csv_field(linea,i);

				printf("%s - ", Px->evolucionPrevia);
			}

			//EVOLUCION POSTERIOR
			if(i == 7){
				Px->evolucionPosterior = get_csv_field(linea,i);

				printf("%s - ", Px->evolucionPosterior);
			}

			//NUMERO POKEDEX
			if(i == 8){
				aux = get_csv_field(linea,i);
				Px->numeroPokedex = atoi(aux);

				printf("%d - ", Px->numeroPokedex);
			}

			//REGION
			if(i == 9){
				Px->region = get_csv_field(linea,i);

				printf("%s\n", Px->region);
			}

		}
		//INSERTAR EN MAPA POKEMON USUARIO //
		insertMap(*PokemonUsuario_id, &PokUser->id, PokUser);
		*totalPokemon = *totalPokemon + 1;

		//VERIFICAR EXISTENCIA PREVIA EN LA POKEDEX
		bool PokemonRepetido = false;
		Pokedex *registro, *registro2;
		if(*PokemonUsuario_id != NULL && *Pokedex_num != NULL && *Pokedex_nombre != NULL){
			// Se busca el pokemon en la pokedex.
			registro = (Pokedex*) searchMap(*Pokedex_nombre, PokUser->nombre);
			registro2 = (Pokedex*) searchMap(*Pokedex_num, &Px->numeroPokedex);

			// Si se encuentra el la pokedex, se suma 1 a la existencia de dicho pokemon. //
			if(registro!= NULL && registro2 != NULL){
				registro->existencia++;
				PokemonRepetido = true;
			}
			
		}
		
		// Si no existe registro previo en la Pokedex, se agrega el pokemon al registro de la Pokedex. //
		if(PokemonRepetido == false){
			// INSERTAR EN MAPAS POKEDEX //
			insertMap(*Pokedex_num, &Px->numeroPokedex, Px);
			insertMap(*Pokedex_nombre, Px->nombre, Px);
			*totalPokemonPokedex = *totalPokemonPokedex + 1;

			//free(registro); 
			//free(registro2);
		}
		

	}
	//CERRAR ARCHIVO IMPORTADO//
	fclose(fp);

	
	printf("\nImportacion realizada con exito\n\n");
	printf("TOTAL POKEMON: %d\n", *totalPokemon);
	printf("TOTAL POKEMON POKEDEX: %d\n", *totalPokemonPokedex);

	//INICIO TESTING //

	//TESTING ALMACENAMIENTO//
	printf("\nTESTING ALMACENAMIENTO:\n");
	Pokemon_usuario *test = (Pokemon_usuario*) firstMap(*PokemonUsuario_id);
	while(test != NULL){
		printf("\n%d | %s | %d | %d | %s\n", test->id, test->nombre, test->PC, test->PS, test->sexo);
		test = (Pokemon_usuario*) nextMap(*PokemonUsuario_id);
	}
	free(test);

	//TESTING POKEDEX CON CLAVE NUMERO DE POKEDEX//
	printf("\nTESTING POKEDEX CON CLAVE NUM:\n");
	Pokedex *test2 = (Pokedex*) firstMap(*Pokedex_num);
	i = 0;
	while(test2 != NULL){
		printf("\n%d: %d | %s | %s | %s | %s | %d | %s\n", i+1, test2->existencia, test2->nombre, test2->tipo, test2->evolucionPrevia, test2->evolucionPosterior, test2->numeroPokedex, test2->region);
		test2 = (Pokedex*) nextMap(*Pokedex_num);
		i++;
	}
	printf("%d\n", i);
	free(test2);

	//TESTING POKEDEX CON CLAVE NOMBRE POKEMON //
	printf("\nTESTING POKEDEX CON CLAVE NOMBRE:\n");
	Pokedex *test3 = (Pokedex*) firstMap(*Pokedex_nombre);
	i = 0;
	while(test3 != NULL){
		printf("\n%d: %d | %s | %s | %s | %s | %d | %s\n", i+1, test3->existencia, test3->nombre, test3->tipo, test3->evolucionPrevia, test3->evolucionPosterior, test3->numeroPokedex, test3->region);
		test3 = (Pokedex*) nextMap(*Pokedex_nombre);
		i++;
	}
	printf("%d\n", i);
	free(test3);
	//FIN TESTING //

	return;
}