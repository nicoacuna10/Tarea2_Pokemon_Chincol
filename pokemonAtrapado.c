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
	if(MapaPokemon == NULL){
		printf("Por favor importe archivos antes de iniciar esta funcion\n\n");
		return;/// HAY QUE PENSAR SI SE DEBE INICIALIZAR MAPA AQUI//
	}


	//COMENTARIO: Hay que revisar si existe la sección de contar la existencia de los pokemones se guarda en total pokemon//
	if( *totalPokemon == 100){
		printf("No se puede ingresar otro pokemon porque haz llenado el limite de memoria por usuario.\n");
		printf("Usa la funcion librerar pokemon primero para liberar memoria para un nuevo ingreso\n\n");
		return;
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
		printf("Por favor ingrese ID: ");
		scanf("%d", &aux->PokUser->id);
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
		printf("%s %d %d %s\n\n", aux->PokUser->nombre, aux->PokUser->PC, aux->PokUser->PS, aux->PokUser->sexo);
		insertMap(MapaPokemon, &aux->PokUser->id, aux); // HAY QUE REVISAR SI ID SE CREA O SE PIDO POR USUARIO//
		return;
	}

	//En caso de no existir pokemon en la pokedex se agrega en el resto de la seccion del código//	
	if(existiaPokemonEnPokedex == false){
		//Inicialización de variables para guardar datos//
		infoPokemon *aux = (infoPokemon *) malloc(sizeof(infoPokemon) );
		assert(aux != NULL);

		aux->PokUser = (Pokemon_usuario *)	malloc(sizeof(Pokemon_usuario));
		assert(aux->PokUser != NULL);

		aux->PokUser->nombre = (char *) malloc(50 * sizeof(char) );
		assert(aux->PokUser->nombre != NULL);

		aux->PokUser->sexo = (char *) malloc(7 * sizeof(char) );
		assert(aux->PokUser->sexo != NULL);

		aux->Px = (Pokedex *) malloc(sizeof(Pokedex) );
		assert(aux->Px != NULL);

		aux->Px->nombre = (char *) malloc(50 * sizeof(char) );
		assert(aux->Px->nombre != NULL);

		aux->Px->evolucionPosterior = (char *) malloc(20 * sizeof(char ) );
		assert(aux->Px->evolucionPosterior != NULL);

		aux->Px->evolucionPrevia = (char *) malloc(20 * sizeof(char) );
		assert(aux->Px->evolucionPrevia != NULL);

		aux->Px->region = (char *) malloc(20 * sizeof(char) );
		assert(aux->Px->region != NULL);

		aux->Px->tipo = (char * ) malloc(30 * sizeof(char) );
		assert(aux->Px->tipo != NULL);

		//Se solicitan datos por pantalla y se guardan a continuacion//
		printf("Por favor ingrese ID: ");
		scanf("%d", &aux->PokUser->id);
		printf("Por favor ingrese PC: ");
		scanf("%d", &aux->PokUser->PC);
		printf("Por favor ingrese PS: ");
		scanf("%d", &aux->PokUser->PS);
		getchar();
		printf("Por favor ingrese sexo: ");
		scanf("%[^\n]s", aux->PokUser->sexo);
		getchar();

		printf("\nPokemon ingresado no se encuentra en la pokedex. Porfavor ingrese datos para generar registro\n\n");
		printf("Por favor ingrese tipo: ");
		scanf("%[^\n]s", aux->Px->tipo);
		getchar();
		printf("Por favor ingrese evolucion previa: ");
		scanf("%[^\n]s", aux->Px->evolucionPrevia);
		getchar();
		printf("Por favor ingrese evolucion posterior: ");
		scanf("%[^\n]s", aux->Px->evolucionPosterior);
		getchar();
		printf("Por favor ingrese numero pokedex: ");
		scanf("%d", &aux->Px->numeroPokedex);
		getchar();
		printf("Por favor ingrese region: ");
		scanf("%[^\n]s", aux->Px->region);
		getchar();

		strcpy(aux->PokUser->nombre, nombre);
		strcpy(aux->Px->nombre, nombre);
		aux->Px->existencia = 1;



		printf("%s %d %d %s\n\n", aux->PokUser->nombre, aux->PokUser->PC, aux->PokUser->PS, aux->PokUser->sexo);
		insertMap(MapaPokemon, &aux->PokUser->id, aux); // HAY QUE REVISAR SI ID SE CREA O SE PIDO POR USUARIO//
	}

	return;
}