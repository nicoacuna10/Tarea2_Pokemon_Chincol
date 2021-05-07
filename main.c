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

void menu(int *opcion);

void importarExportarPokemonDesdeUnArchivo(char *nombre_archivo, Map **PokemonUsuario_id, Map **Pokedex_num , Map **Pokedex_nombre, int *totalPokemon, int *totalPokemonPokedex);
void pokemonAtrapado(Map *MapaPokemon, Map *Pokedex_num, Map *Pokedex_nombre, int *totalPokemon, int *totalPokemonPokedex);
void evolucionarPokemon(Map *PokemonUsuario_id, Map *Pokedex_num, Map *Pokedex_nombre);
void buscarMisPokemonPorTipo(Map *PokemonUsuario_id, Map *Pokedex_num);
void buscarMisPokemonPorNombre(Map *PokemonUsuario_id);
void buscarPorNombreEnPokedex(Map *Pokedex_nombre);
void mostrarTodosLosPokemonDeLaPokedex(Map *Pokemon_nombre, int totalPokemonPokedex);
void mostrarPokemonPorMayorPC(Map *PokemonUsuario_id, int totalPokemon);
void liberarPokemon(Map **PokemonUsuario_id, Map **Pokedex_nombre, int *totalPokemon, int *totalPokemonPokedex);
void mostrarPokemonPorRegion(Map *Pokedex_num);

int main(void){
	int opcionElegida, totalPokemon = 0, totalPokemonPokedex = 0;
	char nombre_archivo[100];

	// DEFINICIÓN MAPAS //
	Map *PokemonUsuario_id = NULL; 
	Map *Pokedex_num = NULL; 
	Map *Pokedex_nombre = NULL; 

	do{
		menu(&opcionElegida);
		if(opcionElegida == 0) break;
		if(opcionElegida == 1){
			if(PokemonUsuario_id == NULL) PokemonUsuario_id = createMap(is_equal_int); // ALMACENAMIENTO DEL USUARIO CON LLAVE EL ID DEL POKEMON
			if(Pokedex_num == NULL) Pokedex_num = createMap(is_equal_int); // POKEDEX CON LLAVE EL NUMERO DE LA POKEDEX
			if(Pokedex_nombre == NULL){
				Pokedex_nombre = createMap(is_equal_string); // POKEDEX CON LLAVE EL NOMBRE DEL POKEMON
				setSortFunction(Pokedex_nombre, lower_than_string);
			}
			importarExportarPokemonDesdeUnArchivo(nombre_archivo, &PokemonUsuario_id, &Pokedex_num, &Pokedex_nombre, &totalPokemon, &totalPokemonPokedex);
		}
		if(opcionElegida == 2) pokemonAtrapado(PokemonUsuario_id, Pokedex_num, Pokedex_nombre, &totalPokemon, &totalPokemonPokedex);
		if(opcionElegida == 3) evolucionarPokemon(PokemonUsuario_id, Pokedex_num, Pokedex_nombre);
		if(opcionElegida == 4) buscarMisPokemonPorTipo(PokemonUsuario_id, Pokedex_num);
		if(opcionElegida == 5) buscarMisPokemonPorNombre(PokemonUsuario_id);
		if(opcionElegida == 6) buscarPorNombreEnPokedex(Pokedex_nombre);
		if(opcionElegida == 7) mostrarTodosLosPokemonDeLaPokedex(Pokedex_nombre, totalPokemonPokedex);
		if(opcionElegida == 8) mostrarPokemonPorMayorPC(PokemonUsuario_id, totalPokemon);
		if(opcionElegida == 9) liberarPokemon(&PokemonUsuario_id, &Pokedex_nombre, &totalPokemon, &totalPokemonPokedex);
		if(opcionElegida == 10) mostrarPokemonPorRegion(Pokedex_num);
	}while(menu != 0);

	free(PokemonUsuario_id);
	free(Pokedex_num);
	free(Pokedex_nombre);

	printf("\n¡Adios!\n");
	return 0;
}
