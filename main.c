#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"

typedef struct{
	int id;
	char* nombre;
	float PC;
	float PS;
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
  función para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

/*
  función para comparar claves de tipo string
  retorna 1 si son key1<key2
*/
int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

void menu(int *opcion);

void *importarExportarPokemonDesdeUnArchivo(char *nombre_archivo, Map *MapaPokemon, int *totalPokemon, int *totalPokemonPokedex);
void pokemonAtrapado(Map *MapaPokemon, int *totalPokemon);
void evolucionarPokemon(Map *MapaPokemon);
void buscarMisPokemonPorTipo(Map *MapaPokemon, char tipo[20]);
void buscarMisPokemonPorNombre(Map *MapaPokemon, char nombre[50]);
void buscarPorNombreEnPokedex(Map *MapaPokemon, char nombre[50]);
void mostrarTodosLosPokemonDeLaPokedex(Map *MapaPokemon, int totalPokemonPokedex);
void mostrarPokemonPorMayorPC(Map *MapaPokemon);
void liberarPokemon(Map * MapaPokemon);
void mostrarPokemonPorRegion(Map *MapaPokemon, char region[20]);

int main(void){
	int opcionElegida, totalPokemon = 0, totalPokemonPokedex = 0;
	char nombre_archivo[100];
	Map *MapaPokemon, *Pokemon_tipo;
	char tipo[20], region[20], nombre[50];

	do{
		menu(&opcionElegida);
		if(opcionElegida == 0) break;
		if(opcionElegida == 1) MapaPokemon = importarExportarPokemonDesdeUnArchivo(nombre_archivo, MapaPokemon, &totalPokemon, &totalPokemonPokedex);
		if(opcionElegida == 2) pokemonAtrapado(MapaPokemon, &totalPokemon);
		if(opcionElegida == 3) evolucionarPokemon(MapaPokemon);
		if(opcionElegida == 4){
			/*//CREAR MAPA //
			Pokemon_tipo = createMap(is_equal_string);

			//INSERTAR DATOS EN MAPA CON CLAVE TIPO // 
			infoPokemon *aux = (infoPokemon*) firstMap(MapaPokemon);
			while(aux != NULL){
				insertMap(Pokemon_tipo, aux->Px->tipo, aux);
				aux = (infoPokemon*) nextMap(MapaPokemon);
			}

			// Testing
			int i = 1;
			aux = (infoPokemon*) firstMap(Pokemon_tipo);
			while(aux != NULL){
				printf("\n%d - %s - %d - %d - %s\n", i, aux->PokUser->nombre, aux->PokUser->PC, aux->PokUser->PS, aux->Px->tipo);
				aux = (infoPokemon*) nextMap(Pokemon_tipo);
				i++;
			}
			//*/
			buscarMisPokemonPorTipo(MapaPokemon, tipo);
		}
		if(opcionElegida == 5) buscarMisPokemonPorNombre(MapaPokemon, nombre);
		if(opcionElegida == 6) buscarPorNombreEnPokedex(MapaPokemon, nombre);
		if(opcionElegida == 7) mostrarTodosLosPokemonDeLaPokedex(MapaPokemon, totalPokemonPokedex);
		if(opcionElegida == 8) mostrarPokemonPorMayorPC(MapaPokemon);
		if(opcionElegida == 9) liberarPokemon(MapaPokemon);
		if(opcionElegida == 10) mostrarPokemonPorRegion(MapaPokemon, region);
	}while(menu != 0);




	printf("\n¡Adios!\n");
	return 0;
}