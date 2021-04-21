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

typedef struct{
	Pokemon_usuario* PokUser; 
	Pokedex* Px;
}infoPokemon;

void buscarMisPokemonPorTipo(char tipo[20], Map *Pokemon_tipo){
	
	printf("\nIngrese tipo de Pokemon a buscar: ");
	scanf("%[^\n]s", tipo);
	getchar();

	//BUSQUEDA DE POKEMON POR TIPO - NO SE COMO BUSCAR MAS DE UNO :( //
	infoPokemon *P = searchMap(Pokemon_tipo,tipo);
	if(P){
		printf("\n%s %d %d\n", P->PokUser->nombre, P->PokUser->PC, P->PokUser->PS);
	}
	else printf("\nNO EXISTE POKEMON DE TIPO INGRESADO\n");
	return;
}