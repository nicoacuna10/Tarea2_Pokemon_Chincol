#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
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

void pokemonAtrapado(Map *MapaPokemon, int *totalPokemon){
	//COMENTARIO: Hay que revisar si existe la sección de contar la existencia de los pokemones se guarda en total pokemon//
	if( *totalPokemon == 100){
		printf("No se puede ingresar otro pokemon porque haz llenado el limite de memoria por usuario.\n");
		printf("Usa la funcion librerar pokemon primero para liberar memoria para un nuevo ingreso\n\n");
	}

	//Incialización de variables//
	char nombre[50];
	bool existiaPokemonEnPokedex = false;
	memset(nombre, '\0', 50);
	infoPokemon *buscarPokemonEnMapa = (infoPokemon *) firstMap(MapaPokemon);
	assert(buscarPokemonEnMapa != NULL);

	//Se pide nombre del pokemon por usuario//
	printf("Por favor ingrese nombre del pokemon atrapado: ");
	scanf("%[^\n]s", nombre);
	getchar();


	/*Se busca si el pokemon se encuentra en la pokedex.
	  En caso de estar solo se agrega +1 a existencia y se cierra la función */
	while(buscarPokemonEnMapa != NULL){
		if(strcmp(buscarPokemonEnMapa->Px->nombre, nombre) == 0){
			buscarPokemonEnMapa->Px->existencia++;
			existiaPokemonEnPokedex = true;
			break;
		}
		buscarPokemonEnMapa = (infoPokemon *) nextMap(MapaPokemon);
	}

	//En caso de encontrarse pokemon en la pokedex solo se ingresan datos del usuario//
	if(existiaPokemonEnPokedex == true){
		//Inicialización de variables para guardar datos//
		infoPokemon *aux = (infoPokemon *) malloc(sizeof(infoPokemon) );
		assert(aux != NULL);

		aux->PokUser = (Pokemon_usuario *)	malloc(sizeof(Pokemon_usuario));
		assert(aux->PokUser != NULL);

		aux->PokUser->nombre = (char *) malloc(50 * sizeof(char) );
		assert(aux->PokUser->nombre != NULL);

		aux->PokUser->sexo = (char *) malloc(7 * sizeof(char) );
		assert(aux->PokUser->sexo != NULL);
	
		//PREGUNTAR SI hay que poner id por usuario o no//
		//Se ingresan datos por usuario//
		printf("Por favor ingrese PC: ");
		scanf("%d", &aux->PokUser->PC);
		printf("Por favor ingrese PS: ");
		scanf("%d", &aux->PokUser->PS);
		getchar();
		printf("Por favor ingrese sexo: ");
		scanf("%[^\n]s", aux->PokUser->sexo);
		getchar();
		strcpy(aux->PokUser->nombre, nombre);

		//Testing//
		printf("%s %d %d \n\n", aux->PokUser->nombre, aux->PokUser->PC, aux->PokUser->PS, aux->PokUser->sexo);
		//No esta imprimiendo sexo//
	return;
	}


	return;
}