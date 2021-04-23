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
	/* totalcomas + 1 es igual a la cantidad de tipo que posee el pokemon evaluado.
	Esta función ayuda a saber cuantos tipos posee el pokemon que se está evaluando
	a tiempo real.                                                               */  
	int totalcomas = 1;
	for(int i = 0; vector[i]; i++){
		if(vector[i] == ',') totalcomas++;
	}
	return totalcomas;
}

Pokemon_y_sus_tipos *llenarVector(char *vectorTipos, Pokemon_y_sus_tipos *pokemon_en_evaluacion, int tallavector){
	/*Esta funcion llena en un vector dinámico cada uno de los tipos que posee
	el pokemon que se evalua en tiempo real. Por cada iteración este vector va
	cambiando ya que se evalua un nuevo pokemon. 
	En cada casilla del vector se encuentra un tipo que posee el pokemon    */
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
	//Declaración de variables//
	bool existeTipoDePokemon = false;	
	int tallavector;
	Pokemon_y_sus_tipos* pokemon_en_evaluacion = NULL;

	//Lectura de entrada//
	printf("\nIngrese tipo de Pokemon a buscar: ");
	scanf("%[^\n]s", tipo);
	getchar();

	infoPokemon *P = (infoPokemon*) firstMap(MapaPokemon);
	assert(P != NULL);

	//Se recorre el mapa entero con 'P' y se va evaluando si el pokemon posee el tipo que se busca//
	while(P != NULL){
		//Se busca primero la cantidad de tipos que posee el pokemon para inicializar vector//
		tallavector = totalTipos(P->Px->tipo);
		//Se inicializa vector tipo struct//
		pokemon_en_evaluacion = (Pokemon_y_sus_tipos*) malloc(tallavector*sizeof(Pokemon_y_sus_tipos));
		assert(pokemon_en_evaluacion != NULL);
		//Se llena vector con cada casilla con una especie de tipo//
		pokemon_en_evaluacion = llenarVector(P->Px->tipo, pokemon_en_evaluacion, tallavector);

		//Se evalua pokemon si posee tipo buscado//
		for(int i = 0; i < tallavector; i++){
			//Si se encuentra tipo se imprime por pantalla//
			if( strcmp(pokemon_en_evaluacion[i].tipo, tipo) == 0){
				printf("\n%d - %s - %d - %d - %s\n", P->PokUser->id, P->PokUser->nombre, P->PokUser->PC, P->PokUser->PS, pokemon_en_evaluacion[i].tipo);
				existeTipoDePokemon = true;
				break;// Agregue esta  linea porque tiene sentido :) //
			}
		}

		//Testing
		/*for(int i = 0; i < tallavector; i++){
			printf("%s ", pokemon_en_evaluacion[i].tipo);
		}
		printf("\nTotal tipos: %d\n", tallavector);
		*/
		//Fin Testing//


		//Se libera memoria del vector dinámico que guarda cada uno de los tipos que posee el pokemon//
		free(pokemon_en_evaluacion);
		//Se continua con el siguiente pokemon del mapa//
		P = (infoPokemon*) nextMap(MapaPokemon);
	}

	//En caso de nunca haberse cambiado esta variable a true, signfica que no hay pokemon registrado con tipo ingresado//
	if(existeTipoDePokemon == false) printf("\nNO EXISTE REGISTRO DE POKEMON DE TIPO INGRESADO\n");
	return;
}
