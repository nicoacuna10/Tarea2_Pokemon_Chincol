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

void buscarMisPokemonPorNombre(Map *PokemonUsuario_id){
	// Si el mapa no se encuentra inicializado, se imprime un mensaje y se vuelve al menu de opciones. //
	if(PokemonUsuario_id == NULL){
		printf("No se tiene registro previo para realizar esta funcion\n\n");
		return;
	}

	// Declaración de variables //
	bool hayPokemon = false;
	char nombre[50], num[7];
	int j = 0, k, espacios;

	printf("Ingrese nombre de Pokemon: ");
	scanf("%[^\n]s", nombre);
	getchar();

	// Se recorre Mapa Pokemon y se imprimen los Pokemones del almacenamiento del usuario que corresponden con el nombre ingresado
	Pokemon_usuario *aux = (Pokemon_usuario*) firstMap(PokemonUsuario_id);

	printf("Pokemones %s:\n", nombre);
	while(aux != NULL){
		if( strcmp(aux->nombre, nombre) == 0){
			if( j == 0){
				printf(" ----------------------------------------------------------\n");
				printf("| ID  | NOMBRE               | PC     | PS     | SEXO      |\n");
				printf(" ----------------------------------------------------------\n");
			}
			printf("| %d", aux->id);
			sprintf(num, "%d", aux->id);
			//itoa(aux->id, num, 10);
			espacios = 3 - strlen(num);
			for(k = 0; k < espacios; k++) printf(" ");

			printf(" | %s", aux->nombre);
			espacios = 20 - strlen(aux->nombre);
			for(k = 0; k < espacios; k++) printf(" ");

			printf(" | %d", aux->PC);
			sprintf(num, "%d", aux->PC);
			//itoa(aux->PC, num, 10);
			espacios = 6 - strlen(num);
			for(k = 0; k < espacios; k++) printf(" ");

			printf(" | %d", aux->PS);
			sprintf(num, "%d", aux->PS);
			//itoa(aux->PS, num, 10);
			espacios = 6 - strlen(num);
			for(k = 0; k < espacios; k++) printf(" ");

			printf(" | %s", aux->sexo);
			espacios = 9 - strlen(aux->sexo);
			for(k = 0; k < espacios; k++) printf(" ");
			
			printf(" |\n ----------------------------------------------------------\n");

			hayPokemon = true;
			j++;
		}
		aux = (Pokemon_usuario*) nextMap(PokemonUsuario_id);

	}

	// Si no se encuentran Pokemones con el nombre ingresado, se indica que no existe registro
	if(hayPokemon == false) printf("No existe registro de pokemon %s en almacenamiento de usuario\n\n", nombre);

	return;
}