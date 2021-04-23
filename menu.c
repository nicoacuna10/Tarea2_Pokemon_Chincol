#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void menu(int *opcion){
 	char entrada[5000];
	bool esDiez = false;

	do{
 		memset(entrada, '\0', 5000);	

		printf(" ---------------------------------------------------- \n");
		printf("|                 MENU DE APLICACION                 |\n");
		printf(" ---------------------------------------------------- \n");
		printf("| opcion 1: Importar desde archivo                   |\n");
		printf("| opcion 2: Ingresar pokemon atrapado                |\n");
		printf("| opcion 3: Buscar siguiente evoluacion              |\n");
		printf("| opcion 4: Buscar  mis pokemons por tipo            |\n");
		printf("| opcion 5: Buscar mis pokemons por nombre           |\n");
		printf("| opcion 6: Buscar nombre en pokedex                 |\n");
		printf("| opcion 7: Mostrar todos los pokemons de la pokedex |\n");
		printf("| opcion 8: Mostrar mis pokemons ordenados por PC    |\n");
		printf("| opcion 9: Liberar pokemon                          |\n");
		printf("| opcion 10: Mostrar pokemon por region              |\n");
		printf("| opcion 0: Salir del programa                       |\n");
		printf(" ---------------------------------------------------- \n");

		printf("\nIngrese opcion: ");
		scanf("%[^\n]s", entrada);
		getchar();

		//Se corrobora si entrada no es válida o se ingreso 10//
		if(entrada[1] != '\0'){
			
			if(entrada[1] != '0'){
			printf("¡Entrada no valida!\n\n");
			}
			if( (entrada[0] == '1') && (entrada[1] == '0') ) {
				esDiez = true;
			}
		}	

	}while( ( (  entrada[0] < '0') || ( entrada[0] > '9') )  );

	//Se ingresan datos correspondientes para main.c//
	if(esDiez == true)
		(*opcion) = 10;
	else
		(*opcion) = entrada[0] - 48;

	printf("\n%d\n", *opcion);
	return;
}