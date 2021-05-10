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

void buscarMisPokemonPorTipo(Map *PokemonUsuario_id, Map *Pokedex_num){
	// Si los mapas no se encuentran inicializados, se imprime un mensaje y se vuelve al menu de opciones. //
	if(PokemonUsuario_id == NULL || Pokedex_num == NULL){
		printf("No se tiene registro de pokemones. Por favor importe desde un archivo\n\n");
		return;
	}


	//Declaración de variables//
	bool existeTipoDePokemon = false;
	char tipo[20], num[7];	
	int tallavector, j = 0, espacios, k;
	Pokemon_y_sus_tipos* pokemon_en_evaluacion = NULL;

	//Lectura de entrada//
	printf("\nIngrese tipo de Pokemon a buscar: ");
	scanf("%[^\n]s", tipo);
	getchar();

	Pokedex *aux = (Pokedex*) firstMap(Pokedex_num);

	//Se recorre por fuerza bruta la pokedex con 'aux' y se va evaluando si el pokemon posee el tipo que se busca//
	while(aux != NULL){
		//Se busca primero la cantidad de tipos que posee el pokemon para inicializar vector//
		tallavector = totalTipos(aux->tipo);
		//Se inicializa vector tipo struct//
		pokemon_en_evaluacion = (Pokemon_y_sus_tipos*) malloc(tallavector*sizeof(Pokemon_y_sus_tipos));
		assert(pokemon_en_evaluacion != NULL);
		//Se llena vector con cada casilla con una especie de tipo//
		pokemon_en_evaluacion = llenarVector(aux->tipo, pokemon_en_evaluacion, tallavector);

		// Se recorre el almacenamiento del usuario para imprimir los pokemones del tipo correspondiente
		Pokemon_usuario *aux2 = (Pokemon_usuario*) firstMap(PokemonUsuario_id);

		while(aux2 != NULL){
			if( strcmp(aux2->nombre, aux->nombre) == 0){
				//Se evalua pokemon si posee tipo buscado//
				for(int i = 0; i < tallavector; i++){
					//Si se encuentra tipo se imprime por pantalla//
					if( strcmp(pokemon_en_evaluacion[i].tipo, tipo) == 0){
						if(j == 0){
							printf(" ---------------------------------------------------------------------------------\n");
							printf("| ID  | NOMBRE               | PC     | PS     | SEXO      | TIPO                 |\n");
							printf(" ---------------------------------------------------------------------------------\n");
						}
						printf("| %d", aux2->id);
						sprintf(num, "%d", aux2->id);
						espacios = 3 - strlen(num);
						for(k = 0; k < espacios; k++) printf(" ");

						printf(" | %s", aux2->nombre);
						espacios = 20 - strlen(aux2->nombre);
						for(k = 0; k < espacios; k++) printf(" ");

						printf(" | %d", aux2->PC);
						sprintf(num, "%d", aux2->PC);
						espacios = 6 - strlen(num);
						for(k = 0; k < espacios; k++) printf(" ");

						printf(" | %d", aux2->PS);
						sprintf(num, "%d", aux2->PS);
						espacios = 6 - strlen(num);
						for(k = 0; k < espacios; k++) printf(" ");

						printf(" | %s", aux2->sexo);
						espacios = 9 - strlen(aux2->sexo);
						for(k = 0; k <espacios; k++) printf(" ");
						

						printf(" | %s", pokemon_en_evaluacion[i].tipo);
						espacios = 20 - strlen(pokemon_en_evaluacion[i].tipo);
						for(k = 0; k < espacios; k++) printf(" ");

						printf("|\n ---------------------------------------------------------------------------------\n");
						existeTipoDePokemon = true;
						j++;
						break;
					}
				}
			}

			aux2 = (Pokemon_usuario*) nextMap(PokemonUsuario_id);
		}
		//Se libera memoria del vector dinámico que guarda cada uno de los tipos que posee el pokemon//
		free(pokemon_en_evaluacion);
		//Se continua con el siguiente pokemon del mapa//
		aux = (Pokedex*) nextMap(Pokedex_num);
	}
	//En caso de nunca haberse cambiado esta variable a true, signfica que no hay pokemon registrado con tipo ingresado//
	if(existeTipoDePokemon == false) printf("\nNO EXISTE REGISTRO DE POKEMON DE TIPO INGRESADO\n");
	return;
}
