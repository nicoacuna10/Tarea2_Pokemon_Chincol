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

void menu(int *opcion);
/*
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
	int opcionElegida;



	do{
		menu(&opcionElegida);
		if(opcionElegida == 0) break;
		///if(opcionElegida == 1) importarExportarPokemonDesdeUnArchivo();
		//if(opcionElegida == 2) pokemonAtrapado();
		//if(opcionElegida == 3) evolucionarPokemon();
		//if(opcionElegida == 4) buscarMisPokemonPorTipo();
		//if(opcionElegida == 5) buscarMisPokemonPorNombre();
		//if(opcionElegida == 6) buscarPorNombreEnPokedex();
		//if(opcionElegida == 7) mostrarTodosLosPokemonDeLaPodex();
		//if(opcionElegida == 8) mostrarPokemonPorMayorPc();
		//if(opcionElegida == 9) liberarPokemon();
		//if(opcionElegida == 10) mostrarPokemonPorRegion();
	}while(menu != 0);





	return 0;
}