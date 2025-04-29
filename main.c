#include "header.h"

int main(){

    FILE* juego;
    int selec;

    //crear_archivo_historia();
    //crear_archivo_Personajes_Principales()

    selec = menu_principal();//mostrar opciones en pantalla tales como cargar partida, nueva partida, salir del juego, (opciones?: posibilidad de poner juego en ingles? algo más?)
    if(selec == 3) return 0;
    juego = cargar_partida(selec);

    historia_principal(juego);

    return 0;
}



//FUNCIONES

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

    return game;
    /* si se carga la partida hay que extraer la informacino y almacenarla en la memoria dinamica
    sino se crea el archivo y se los debe cargar con los datos iniciales de la partida*/
}

guardar_partida(FILE* game); // guardar juego, se podria preguntar si desa salir del juego o si desea seguir jugando.


/*
El archivo que contenga la historia principal, puede contener en cada linea un texto que narre lo que sucede/ va a suceder
y el nombre del archivo de batalla al que se haga referencia
*/
//Inicio Funciones de prueba, y tener como ejemplo (al menos por ahora) para trabajar y ver como realizar la historia
void crear_archivo_historia() {
    FILE* archivo = fopen("Historia Principal", "wb");
    if (archivo == NULL) {
        puts("No se pudo crear el archivo");
        exit(1);
    }

    Capitulo capitulos[3] = {
        {"Ejemplo de texto para rellenar","batalla 1.bin"},
        {"Ejemplo de texto para rellenar antes de la 2da batalla","batalla 2.bin"},
        {"Más texto de ejemplo rellenar","batalla 3.bin"}
    };
    fwrite(capitulos, sizeof(Capitulo), 3, archivo);
    fclose(archivo);
}


void crear_archivo_Personajes_Principales() {
    FILE* archivo = fopen("Historia Principal", "wb");
    if (archivo == NULL) {
        puts("No se pudo crear el archivo");
        exit(1);
    }

    Personaje personajes[3] = {
        {"Personaje 1",100,30,20},
        {"Personaje 12",100,20,60},
        {"Personaje 3",100,10.2,70}
    };
    fwrite(personajes, sizeof(Personaje), 3, archivo);
    fclose(archivo);
}

//FIN Funciones de prueba


void historia_principal(Personaje *personajes){
    FILE* archivo = fopen("Historia Principal", "rb");
    if (archivo == NULL) {
        puts("No se pudo crear el archivo");
        exit(1);
    }

    Capitulo capituloN;
    Personaje *auxPersonajes = personajes;
    int opcion=0;

    while(fread(&capituloN, sizeof(Capitulo), 1, archivo) == 1){
        printf("\n****************************");
        printf("\n%s",capituloN.texto_narrativo);
        printf("\nA que personaje deseas utilizar?");
        for(int i=0; i<3; i++){
            printf("\n%d- %s",i+1,auxPersonajes->Nombre);
            auxPersonajes++;
        }
        scanf("%d", &opcion);
        auxPersonajes+-3;

        while(opcion>3 || opcion <=0){
            printf("Entrada no valida. Intentalo de nuevo.\n\n");
            getchar();
            scanf("%d", &opcion);
        }
        
        batalla(capituloN.batalla,personajes,opcion);
    }

    fclose(archivo);
}

//devuelve 1-> gana el héroe , 0-> gana el villano
int batalla(const char nombreArchivo,Personaje* per,int opcion){
    FILE* archivo = fopen(nombreArchivo, "");
    if (archivo == NULL) {
        puts("No se pudo crear el archivo");
        exit(1);
    }

    //continuar

//prueba0 de commit diego
}




