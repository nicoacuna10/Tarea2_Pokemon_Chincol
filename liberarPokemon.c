#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
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

void liberarPokemon(Map *MapaPokemon){
	if(MapaPokemon == NULL){
		printf("Por favor importe datos antes de ingresar a esta funcion.\n\n");
		return;
	}

	bool existePokemon = false;
	char nombre[50];
	memset(nombre,'\0', 50);
	infoPokemon *aux = (infoPokemon *) firstMap(MapaPokemon);
	assert(aux != NULL);


	printf("Por favor ingrese nombre de pokemon a liberar: ");
	scanf("%[^\n]s", nombre);
	getchar();



	//EL CODIGO DEBERIA SER ASI O SIMILAR, Y CON LA CLAVE HASH INGRESAR Y ELIMINAR//
	/*
	aux = eraseMap(MapaPokemon, nombre);
	//Si es NULL significa que no existe en el almacenamiento//
	if(aux == NULL){
		printf("No existe pokemon en tu almacenamiento personal!\n\n");
		return;
	}
	*/	
	//ESTA ES LA PARTE PARCHE DE LO ANTERIOR//
	while(aux != NULL){
		if( strcmp(aux->PokUser->nombre, nombre) == 0){
			//HAY QUE CORROBORAR BIEN QUE ESTO FUNCIONA BIEEEEEEEEEEEENNNNNN :D //
			aux = (infoPokemon *) eraseMap(MapaPokemon, nombre);
			if(aux != NULL)break;
		}

		aux = (infoPokemon *) nextMap(MapaPokemon);
	}

	//Si se sigue acontinuación en el programa es porque se borro pokemon del almacenamiento personal//

	//Se busca nombre en la pokedex y se saca descuenta uno en caso de no ser cero//
	aux = (infoPokemon *) firstMap(MapaPokemon);
	while(aux != NULL){
		if( strcmp(aux->Px->nombre, nombre) == 0 ){
			if(aux->Px->nombre > 0) aux->Px->existencia--;
			break;
		}
		aux = (infoPokemon *) nextMap(MapaPokemon);
	}


	free(aux);
	return;
}