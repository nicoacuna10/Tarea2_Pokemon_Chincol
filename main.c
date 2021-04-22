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

/*
  función para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

/*
  función para comparar claves de tipo string
  retorna 1 si son key1<key2
*/
int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

void menu(int *opcion);

void *importarExportarPokemonDesdeUnArchivo(char *nombre_archivo, Map *MapaPokemon, int *totalPokemon);
//*void pokemonAtrapado(char* nombre, char** tipos, int PC, int PS, char* sexo, char* evolucionPrevia, char* evolucionPosterior, int numeroPokedex, char* region);
//void evolucionarPokemon(int id);
void buscarMisPokemonPorTipo(char tipo[20], Map *MapaPokemon);
//void buscarMisPokemonPorNombre(char* nombre);
//void buscarPorNombreEnPokedex(char* nombre);
void mostrarTodosLosPokemonDeLaPokedex(Map *MapaPokemon, int totalPokemon);
//void mostrarPokemonPorMayorPC();
//void liberarPokemon(int id);
//void mostrarPokemonPorRegion(char* region);

int main(void){
	int opcionElegida, totalPokemon = 0;
	char nombre_archivo[100];
	Map *MapaPokemon, *Pokemon_tipo;
	char tipo[20];

	do{
		menu(&opcionElegida);
		if(opcionElegida == 0) break;
		if(opcionElegida == 1) MapaPokemon = importarExportarPokemonDesdeUnArchivo(nombre_archivo, MapaPokemon, &totalPokemon);
		//if(opcionElegida == 2) pokemonAtrapado();
		//if(opcionElegida == 3) evolucionarPokemon();
		if(opcionElegida == 4){
			/*//CREAR MAPA //
			Pokemon_tipo = createMap(is_equal_string);

			//INSERTAR DATOS EN MAPA CON CLAVE TIPO // 
			infoPokemon *aux = (infoPokemon*) firstMap(MapaPokemon);
			while(aux != NULL){
				insertMap(Pokemon_tipo, aux->Px->tipo, aux);
				aux = (infoPokemon*) nextMap(MapaPokemon);
			}

			// Testing
			int i = 1;
			aux = (infoPokemon*) firstMap(Pokemon_tipo);
			while(aux != NULL){
				printf("\n%d - %s - %d - %d - %s\n", i, aux->PokUser->nombre, aux->PokUser->PC, aux->PokUser->PS, aux->Px->tipo);
				aux = (infoPokemon*) nextMap(Pokemon_tipo);
				i++;
			}
			//*/
			buscarMisPokemonPorTipo(tipo, MapaPokemon);
		}
		//if(opcionElegida == 5) buscarMisPokemonPorNombre();
		//if(opcionElegida == 6) buscarPorNombreEnPokedex();
		if(opcionElegida == 7) mostrarTodosLosPokemonDeLaPokedex(MapaPokemon, totalPokemon);
		//if(opcionElegida == 8) mostrarPokemonPorMayorPc();
		//if(opcionElegida == 9) liberarPokemon();
		//if(opcionElegida == 10) mostrarPokemonPorRegion();
	}while(menu != 0);





	return 0;
}