#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

void buscarPorNombreEnPokedex(Map *MapaPokemon, char nombre[50]){
	if(MapaPokemon == NULL){
		printf("No se tiene registro previo para realizar esta funcion\n\n");
		return;
	}
	bool existeRegistroPokemon = false;

	printf("Ingrese nombre de Pokemon: ");
	scanf("%[^\n]s", nombre);
	getchar();

	// Se recorre MapaPokemon y se imprime los Pokemones de la Pokedex que corresponden al nombre ingresado
	infoPokemon *aux = (infoPokemon*) firstMap(MapaPokemon);

	printf("Pokemones %s:\n", nombre);
	while(aux != NULL){
		if( strcmp(aux->Px->nombre, nombre) == 0){
			printf("%s - %d - %s - %s - %s - %d - %s\n", aux->Px->nombre, aux->Px->existencia, aux->Px->tipo, aux->Px->evolucionPrevia, aux->Px->evolucionPosterior, aux->Px->numeroPokedex, aux->Px->region);
			existeRegistroPokemon = true;
		}
		aux = (infoPokemon*) nextMap(MapaPokemon);
	}

	// Si no se encuentran Pokemones con el nombre ingresado, se indica que no existe registro
	if(existeRegistroPokemon == false) printf("No existe registro de %s en la Pokedex\n");
	return;
}