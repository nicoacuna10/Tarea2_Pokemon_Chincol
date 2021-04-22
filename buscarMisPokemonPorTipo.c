#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Map.h"

typedef struct{
	char tipo[20];
}Pokemon_y_sus_tipos;

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

int totalTipos(char* vector){
	// totalcomas + 1 es igual a la cantidad de tipo que posee el pokemon evaluado // 
	int totalcomas = 1;
	for(int i = 0; vector[i]; i++){
		if(vector[i] == ',') totalcomas++;
	}
	return totalcomas;
}

Pokemon_y_sus_tipos *llenarVector(char *vectorTipos, Pokemon_y_sus_tipos *pokemon_en_evaluacion, int tallavector){
	int j = 0, k = 0;
	for(int i = 0; i < tallavector; i++){
		memset(pokemon_en_evaluacion[i].tipo, '\0', 20);
	}
	for(int i = 0; vectorTipos[i]; i++){
		if(vectorTipos[i] == ','){
			pokemon_en_evaluacion[j].tipo[k] = '\0';
			j++;
			k = 0;
			i += 2;
		}
		pokemon_en_evaluacion[j].tipo[k] = vectorTipos[i];
		k++;
	}
	return pokemon_en_evaluacion;
}

void buscarMisPokemonPorTipo(char tipo[20], Map *MapaPokemon){
	bool existeTipoDePokemon = false;	
	int tallavector;
	Pokemon_y_sus_tipos* pokemon_en_evaluacion = NULL;

	printf("\nIngrese tipo de Pokemon a buscar: ");
	scanf("%[^\n]s", tipo);
	getchar();

	infoPokemon *P = (infoPokemon*) firstMap(MapaPokemon);
	assert(P != NULL);

	while(P != NULL){
		tallavector = totalTipos(P->Px->tipo);
		pokemon_en_evaluacion = (Pokemon_y_sus_tipos*) malloc(tallavector*sizeof(Pokemon_y_sus_tipos));
		assert(pokemon_en_evaluacion != NULL);
		pokemon_en_evaluacion = llenarVector(P->Px->tipo, pokemon_en_evaluacion, tallavector);
		
		//Es !strcmp porque si son iguales entrega cero, y para if es un valor falso, por lo que no entra en la función//
		for(int i = 0; i < tallavector; i++){
			if( strcmp(pokemon_en_evaluacion[i].tipo, tipo) == 0){
				printf("\n%d - %s - %d - %d - %s\n", P->PokUser->id, P->PokUser->nombre, P->PokUser->PC, P->PokUser->PS, pokemon_en_evaluacion[i].tipo);
				existeTipoDePokemon = true;
			}
		}

		//Testing
		/*for(int i = 0; i < tallavector; i++){
			printf("%s ", pokemon_en_evaluacion[i].tipo);
		}
		printf("\nTotal tipos: %d\n", tallavector);
		*/
		free(pokemon_en_evaluacion);
		P = (infoPokemon*) nextMap(MapaPokemon);
	}

	if(existeTipoDePokemon == false) printf("\nNO EXISTE REGISTRO DE POKEMON DE TIPO INGRESADO\n");
	return;
}
