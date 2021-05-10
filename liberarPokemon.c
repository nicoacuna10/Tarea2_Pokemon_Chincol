#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
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

void liberarPokemon(Map **PokemonUsuario_id, Map **Pokedex_nombre, int *totalPokemon, int *totalPokemonPokedex){
	// Si el mapa no está inicializado, se cierra la función //
	if(*PokemonUsuario_id == NULL || *Pokedex_nombre == NULL){
		printf("Por favor importe datos antes de ingresar a esta funcion.\n\n");
		return;
	}

	int id;

	printf("Por favor ingrese id de pokemon a liberar: ");
	scanf("%d", &id);
	getchar();

	// Se elimina el pokemon con id ingresado por usuario //
	Pokemon_usuario *aux = (Pokemon_usuario*) eraseMap(*PokemonUsuario_id, &id);

	// Si se eliminó el pokemon del almacenamiento, se descuenta 1 la existencia de la Pokedex //
	if(aux != NULL){
		Pokedex *registro = (Pokedex*) searchMap(*Pokedex_nombre, aux->nombre);
		if(registro->existencia > 0) registro->existencia--;
	
		printf("Pokemon eliminado con exito!\n\n");
		
		*totalPokemon = *totalPokemon - 1;
	}
	
	if(aux == NULL) printf("No existe registro de pokemon con id ingresado\n\n");
	return;
}