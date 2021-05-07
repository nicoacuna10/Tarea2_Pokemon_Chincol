#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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


void evolucionarPokemon(Map* PokemonUsuario_id, Map* Pokedex_num, Map* Pokedex_nombre){
	// Si alguno de los mapas no se encuentra inicializado, se cierra función //
	if(PokemonUsuario_id == NULL || Pokedex_num == NULL || Pokedex_nombre == NULL){
		printf("Por favor importe datos antes de entrar a esta funcion\n\n");
		return;
	}

	// Solicitud de datos por entrada //
	int id;
	printf("Ingrese id Pokemon: ");
	scanf("%d", &id);
	getchar();

	// Se busca el pokemon en el almacenamiento del usuario //
	Pokemon_usuario *usuario = (Pokemon_usuario*) searchMap(PokemonUsuario_id, &id);
	if(!usuario){
		printf("No existe pokemon con la id %d\n\n", id);
		free(usuario);
		return;
	}

	// Se imprime información del Pokemon a evolucionar//
	printf("\n%d | %s | %d | %d | %s\n", usuario->id, usuario->nombre, usuario->PC, usuario->PS, usuario->sexo);

	Pokedex *pokemonDeEntrada = (Pokedex*) searchMap(Pokedex_nombre, usuario->nombre);

	// Si el pokemon no tiene evolución posterior se entrega mensaje por pantalla //
	if( strcmp(pokemonDeEntrada->evolucionPosterior, "No tiene") == 0){
		printf("El pokemon %s no tiene evolucion posterior\n\n", usuario->nombre);
		free(usuario);
		free(pokemonDeEntrada);
		return;
	}

	// Se actualiza información de usuario con pokemon evolucionado //
	pokemonDeEntrada->existencia--;
	strcpy(usuario->nombre, pokemonDeEntrada->evolucionPosterior);
	usuario->PC *= 1.5;
	usuario->PS *= 1.25;
	Pokedex *pokemonDeSalida= (Pokedex*) searchMap(Pokedex_nombre, pokemonDeEntrada->evolucionPosterior);
	if(pokemonDeSalida != NULL) pokemonDeEntrada->existencia++;
	else{
		// Inicialización de variables //
		Pokedex *agregarPokemonAPokedex = (Pokedex*)malloc(sizeof(Pokedex));
		agregarPokemonAPokedex->nombre = (char *)malloc(50 * sizeof(char));
		assert(agregarPokemonAPokedex->nombre != NULL);
		agregarPokemonAPokedex->tipo = (char *)malloc(30 * sizeof(char));
		assert(agregarPokemonAPokedex->tipo != NULL);
		agregarPokemonAPokedex->evolucionPrevia = (char *)malloc(20 * sizeof(char));
		assert(agregarPokemonAPokedex->evolucionPrevia != NULL);
		agregarPokemonAPokedex->evolucionPosterior = (char *)malloc(20 * sizeof(char));
		assert(agregarPokemonAPokedex->evolucionPosterior != NULL);
		agregarPokemonAPokedex->region = (char *)malloc(20 * sizeof(char));
		assert(agregarPokemonAPokedex->region != NULL);

		// Copia de datos a mapa Pokedex //
		strcpy(agregarPokemonAPokedex->nombre, pokemonDeEntrada->evolucionPosterior);
		strcpy(agregarPokemonAPokedex->tipo, pokemonDeEntrada->tipo);
		strcpy(agregarPokemonAPokedex->evolucionPrevia, pokemonDeEntrada->nombre);
		strcpy(agregarPokemonAPokedex->evolucionPosterior, "No tiene\0");
		strcpy(agregarPokemonAPokedex->region, pokemonDeEntrada->region);
		agregarPokemonAPokedex->existencia = 1;
		agregarPokemonAPokedex->numeroPokedex = pokemonDeEntrada->numeroPokedex+1;
		insertMap(Pokedex_num, &agregarPokemonAPokedex->numeroPokedex, agregarPokemonAPokedex);
		insertMap(Pokedex_nombre, agregarPokemonAPokedex->nombre, agregarPokemonAPokedex);
		//free(agregarPokemonAPokedex);
	}


	printf("\n%d | %s | %d | %d | %s\n\n", usuario->id, usuario->nombre, usuario->PC, usuario->PS, usuario->sexo);
	printf("Pokemon evolucionado exitosamente!\n\n");

	free(usuario);
	free(pokemonDeEntrada);
	free(pokemonDeSalida);
	return;
}