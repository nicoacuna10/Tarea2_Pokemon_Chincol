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

void buscarPorNombreEnPokedex(Map *Pokedex_nombre){
	if(Pokedex_nombre == NULL){
		printf("No se tiene registro previo para realizar esta funcion\n\n");
		return;
	}

	bool existeRegistroPokemon = false;
	char nombre[50];
	printf("Ingrese nombre de Pokemon: ");
	scanf("%[^\n]s", nombre);
	getchar();

	// Se recorre MapaPokemon y se imprime los Pokemones de la Pokedex que corresponden al nombre ingresado
	Pokedex *aux = (Pokedex*) searchMap(Pokedex_nombre, nombre);

	// Si se encuentra el pokemon, se muestra la informacion de la Pokedex
	if(aux){
		printf("Pokemones %s:\n", nombre);
		printf("%s - %d - %s - %s - %s - %d - %s\n", aux->nombre, aux->existencia, aux->tipo, aux->evolucionPrevia, aux->evolucionPosterior, aux->numeroPokedex, aux->region);
	}
	
	// Si no se encuentran Pokemones con el nombre ingresado, se indica que no existe registro
	if(!aux) printf("No existe registro de %s en la Pokedex\n");
	free(aux);
	return;
}