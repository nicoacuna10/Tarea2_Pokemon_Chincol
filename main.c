#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

typedef struct{
	int id;
	char* nombre;
	int PC;
	int PS;
	char sexo;
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

/*void menu(int *opcion);
void *importarExportarPokemonDesdeUnArchivo(char *nombre_archivo);
void pokemonAtrapado(char* nombre, char** tipos, int PC, int PS, char* sexo, char* evolucionPrevia, char* evolucionPosterior, int numeroPokedex, char* region);
void evolucionarPokemon(int id);
void buscarMisPokemonPorTipo(char* tipo);
void buscarMisPokemonPorNombre(char* nombre);
void buscarPorNombreEnPokedex(char* nombre);
void mostrarTodosLosPokemonDeLaPokedex();
void mostrarPokemonPorMayorPC();
void liberarPokemon(int id);
void mostrarPokemonPorRegion(char* region);*/

int main(void){

	return 0;
}