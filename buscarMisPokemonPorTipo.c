#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
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
	bool existeTipoDePokemon = false;	

	printf("\nIngrese tipo de Pokemon a buscar: ");
	scanf("%[^\n]s", tipo);
	getchar();

	//BUSQUEDA DE POKEMON POR TIPO - NO SE COMO BUSCAR MAS DE UNO :( //
	infoPokemon *P = firstMap(Pokemon_tipo);
	assert(P != NULL);
	//searchMap(Pokemon_tipo,tipo);

	while(P != NULL){

		//Es !strcmp porque si son iguales entrega cero, y para if es un valor falso, por lo que no entra en la función//
		if( (strcmp(P->Px->tipo, tipo) ) == 0 ){
			printf("Hola\n");
			printf("\n%s %d %d\n", P->PokUser->nombre, P->PokUser->PC, P->PokUser->PS);
			existeTipoDePokemon = true;
		}
		P = nextMap(Pokemon_tipo);
	}

	if(existeTipoDePokemon == false) printf("\nNO EXISTE REGISTRO DE POKEMON DE TIPO INGRESADO\n");

	return;
}