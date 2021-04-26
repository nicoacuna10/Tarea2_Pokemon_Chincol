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

void liberarPokemon(Map *PokemonUsuario_id, Map *Pokedex_num, Map *Pokedex_nombre){
	if(PokemonUsuario_id == NULL || Pokedex_num == NULL || Pokedex_nombre == NULL){
		printf("Por favor importe datos antes de ingresar a esta funcion.\n\n");
		return;
	}

	int id;


	printf("Por favor ingrese id de pokemon a liberar: ");
	scanf("%d", &id);
	getchar();

	// ELIMINAR POKEMON DEL ALMACENAMIENTO CON LLAVE ID
	Pokemon_usuario *aux = (Pokemon_usuario*) eraseMap(PokemonUsuario_id, &id);
	assert(aux != NULL);

	// Si se elimino el pokemon del almacenamiento, se descuenta 1 la existencia de la Pokedex
	if(aux){
		Pokedex *registro = (Pokedex*) searchMap(Pokedex_nombre, aux->nombre);
		registro->existencia--;
		Pokedex *registro2 = (Pokedex*) searchMap(Pokedex_num, &registro->numeroPokedex);
		registro2->existencia--;
		printf("Pokemon eliminado\n\n");
		free(registro);
		free(registro2);
	}
	

	if(!aux) printf("No existe registro de pokemon con id ingresado\n\n");
	free(aux);
	
	return;
}