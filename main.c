#include "header.h"

int main(){

    FILE* juego;
    int selec; //
    selec = menu_principal();//mostrar opciones en pantalla tales como cargar partida, nueva partida, salir del juego, (opciones?: posibilidad de poner juego en ingles? algo más?)
    if(selec == 3) return 0;
    juego = cargar_partida(selec);
    
    return 0;
}

int menu_principal(){

    int opcion=0;
        printf("+--------------------------------+\n");
        printf("|     SAINT SEIYA THE GAME       |\n");
        printf("+--------------------------------+\n");
        //printf("|  1. Continuar partida          |\n"); que cambia de cargar partida? y como se podria implementar?
        printf("|  2. Cargar partida             |\n");
        printf("|  3. Nueva partida              |\n");
        printf("|  4. Salir del juego            |\n");
        printf("+--------------------------------+\n");
        //se podria hacer mas bonito
    printf("\nElige una opcion (2-4): ");
    scanf("%d", &opcion);

    while (opcion<2 ||opcion>4){

        printf("Entrada no valida. Intentalo de nuevo.\n\n");
        getchar();
        scanf("%d", &opcion);
    }

    switch (opcion) {
        case 1: printf("\n-> Continuando la partida...\n\n"); break;
        case 2: printf("\n-> Cargando partida...\n\n");   break;
        case 3: printf("\n-> Iniciando nueva partida...\n\n"); break;
        default: printf("\nSaliendo del juego. ¡Hasta la proxima!\n");
        }

    return opcion;
}

FILE* cargar_partida(int n){

    FILE* game;
    if(n==2){ // cargar partida
        game = fopen("Partida.dat","rb");
        if (game == NULL)
        {
            puts("No se pudo cargar la partida");
            exit(1);
        }
        
    }
    else{ // nueva partida
        game= fopen("Partida.dat","wb");
        if (game == NULL)
        {
            puts("No se pudo crear la partida");
            exit(1);
        }
    }
    /* si se carga la partida hay que extraer la informacino y almacenarla en la memoria dinamica 
    sino se crea el archivo y se los debe cargar con los datos iniciales de la partida*/
}

guardar_partida(FILE* game); // guardar juego, se podria preguntar si desa salir del juego o si desea seguir jugando.