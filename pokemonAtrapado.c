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

void pokemonAtrapado(Map *PokemonUsuario_id, Map *Pokedex_num, Map *Pokedex_nombre, int *totalPokemon){
	if(PokemonUsuario_id == NULL || Pokedex_num == NULL || Pokedex_nombre == NULL){
		printf("Por favor importe archivos antes de iniciar esta funcion\n\n");
		return;
	}

	if( *totalPokemon == 100){
		printf("No se puede ingresar otro pokemon porque haz llenado el limite de memoria por usuario.\n");
		printf("Usa la funcion librerar pokemon primero para liberar memoria para un nuevo ingreso\n\n");
		return;
	}

	//Incialización de variables//
	char nombre[50];
	//bool existiaPokemonEnPokedex = false;
	memset(nombre, '\0', 50);

	//Se pide nombre del pokemon por usuario//
	printf("Por favor ingrese nombre del pokemon atrapado: ");
	scanf("%[^\n]s", nombre);
	getchar();

	// Se busca el nombre del pokemon en la pokedex
	Pokedex *busquedaEnPokedex = (Pokedex*) searchMap(Pokedex_nombre, nombre);

	//En caso de encontrarse pokemon en la pokedex solo se ingresan datos del usuario//
	if(busquedaEnPokedex){
		//Inicialización de variables para guardar datos//
		Pokemon_usuario *PokUser = (Pokemon_usuario *) malloc(sizeof(Pokemon_usuario) );
		assert(PokUser != NULL);

		PokUser->nombre = (char *) malloc(50 * sizeof(char) );
		assert(PokUser->nombre != NULL);

		PokUser->sexo = (char *) malloc(7 * sizeof(char) );
		assert(PokUser->sexo != NULL);
	
		//PREGUNTAR SI hay que poner id por usuario o no//
		//Se ingresan datos por usuario//
		printf("Por favor ingrese ID: ");
		scanf("%d", &PokUser->id);
		printf("Por favor ingrese PC: ");
		scanf("%d", &PokUser->PC);
		printf("Por favor ingrese PS: ");
		scanf("%d", &PokUser->PS);
		getchar();
		printf("Por favor ingrese sexo: ");
		scanf("%[^\n]s", PokUser->sexo);
		getchar();
		strcpy(PokUser->nombre, nombre);

		//Testing//
		printf("%s %d %d %s\n\n", PokUser->nombre, PokUser->PC, PokUser->PS, PokUser->sexo);
		insertMap(PokemonUsuario_id, &PokUser->id, PokUser); // HAY QUE REVISAR SI ID SE CREA O SE PIDO POR USUARIO//
		return;
	}

	//En caso de no existir pokemon en la pokedex se agrega en el resto de la seccion del código//	
	if(busquedaEnPokedex == NULL){
		//Inicialización de variables para guardar datos//
		Pokemon_usuario *PokUser = (Pokemon_usuario *)	malloc(sizeof(Pokemon_usuario));
		assert(PokUser != NULL);

		PokUser->nombre = (char *) malloc(50 * sizeof(char) );
		assert(PokUser->nombre != NULL);

		PokUser->sexo = (char *) malloc(7 * sizeof(char) );
		assert(PokUser->sexo != NULL);

		Pokedex *Px = (Pokedex *) malloc(sizeof(Pokedex) );
		assert(Px != NULL);

		Px->nombre = (char *) malloc(50 * sizeof(char) );
		assert(Px->nombre != NULL);

		Px->evolucionPosterior = (char *) malloc(20 * sizeof(char ) );
		assert(Px->evolucionPosterior != NULL);

		Px->evolucionPrevia = (char *) malloc(20 * sizeof(char) );
		assert(Px->evolucionPrevia != NULL);

		Px->region = (char *) malloc(20 * sizeof(char) );
		assert(Px->region != NULL);

		Px->tipo = (char * ) malloc(30 * sizeof(char) );
		assert(Px->tipo != NULL);

		//Se solicitan datos por pantalla y se guardan a continuacion//
		printf("Por favor ingrese ID: ");
		scanf("%d", &PokUser->id);
		printf("Por favor ingrese PC: ");
		scanf("%d", &PokUser->PC);
		printf("Por favor ingrese PS: ");
		scanf("%d", &PokUser->PS);
		getchar();
		printf("Por favor ingrese sexo: ");
		scanf("%[^\n]s", PokUser->sexo);
		getchar();

		printf("\nPokemon ingresado no se encuentra en la pokedex. Porfavor ingrese datos para generar registro\n\n");
		printf("Por favor ingrese tipo: ");
		scanf("%[^\n]s", Px->tipo);
		getchar();
		printf("Por favor ingrese evolucion previa: ");
		scanf("%[^\n]s", Px->evolucionPrevia);
		getchar();
		printf("Por favor ingrese evolucion posterior: ");
		scanf("%[^\n]s", Px->evolucionPosterior);
		getchar();
		printf("Por favor ingrese numero pokedex: ");
		scanf("%d", &Px->numeroPokedex);
		getchar();
		printf("Por favor ingrese region: ");
		scanf("%[^\n]s", Px->region);
		getchar();

		strcpy(PokUser->nombre, nombre);
		strcpy(Px->nombre, nombre);
		Px->existencia = 1;



		printf("%s %d %d %s\n\n", PokUser->nombre, PokUser->PC, PokUser->PS, PokUser->sexo);
		insertMap(PokemonUsuario_id, &PokUser->id, PokUser); // HAY QUE REVISAR SI ID SE CREA O SE PIDO POR USUARIO//
		insertMap(Pokedex_num, &Px->numeroPokedex, Px);
		insertMap(Pokedex_nombre, Px->nombre, Px);
	}

	return;
}