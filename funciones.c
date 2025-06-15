#include "header.h"

#define VELOCIDAD_TIPO 40   // ms entre caracteres
#define PAUSA_LINEA 100      // ms entre líneas
#define PAUSA_PUNTUACION 250 // ms extra para .!?

void mostrar_menu()
{
    system("cls"); // Limpiar pantalla

    establecer_color_texto(14);
    printf("\n%10s    ______________________________________________________ \n"," ");
    printf(" %10s  |                                                      |\n"," ");
    printf(" %10s  |                 SAINT SEIYA THE GAME                 |\n"," ");
    printf(" %10s  |______________________________________________________|\n\n"," ");


    establecer_color_texto(11);
    printf("%10s    ______________________________________________________\n"," ");
    printf("%10s   |                                                      |\n"," ");
    printf("%10s   |      1. Continuar partida                            |\n"," ");
    printf("%10s   |      2. Nueva partida                                |\n"," ");
    printf("%10s   |      3. Salir del juego                              |\n"," ");
    printf("%10s   |______________________________________________________|\n\n"," ");

    establecer_color_texto(15);
    printf("   Elige una opcion (1-3): ");
}

int menu_principal()
{
    int opcion = 0;

    mostrar_menu();
    scanf("%d", &opcion);

    while (opcion < 1 || opcion > 3)
    {
        establecer_color_texto(12);
        printf("\n   Entrada no valida. Intentalo de nuevo.\n\n");

        establecer_color_texto(15);
        printf("   Elige una opcion (1-3): ");
        scanf("%d", &opcion);
    }
    establecer_color_texto(10);
    switch (opcion)
    {
    case 1:
        printf("\n   -> Continuando la partida...\n\n");
        Sleep(1000);
        break;
    case 2:
        printf("\n   -> Iniciando nueva partida...\n\n");
        Sleep(1000);
        break;
    default:
        printf("\n   Saliendo del juego. Hasta la proxima!\n");
        Sleep(1000);
    }

    // Restaurar color original
    establecer_color_texto(7);
    return opcion;
}

void cargar_partida(int n, DatosPartida *datos, const char *nombreArchivo)
{
    FILE *partida;

    if (n == 1) {
        partida = fopen(nombreArchivo, "rb");
        if (partida == NULL) {
            puts("No se pudo cargar la partida");
            exit(1);
        }
        fread(datos, sizeof(DatosPartida), 1, partida);
        fclose(partida);
    }
    //printf("PARTIDA CARGADA");
}
void guardar_partida(const char *archivo, DatosPartida *save)
{
    FILE *f = fopen(archivo, "wb");
    if (!f)
        return;
    fwrite(save, sizeof(DatosPartida), 1, f);
    fclose(f);
}

//--BATALLA--

float CalcularDanioTecnicaEnemigo(Enemigo *e, int num_tec) {
    Tecnica *tec = &e->tecnicas[num_tec];
    float danio_base = e->ataque;
    float danio_final = danio_base * (tec->ataque_tec / 100.0f);
    e->cosmo -= tec->cosmo_necesario;
    return danio_final;
}
int validarIntRango(int min, int max)
{
    int num;
    int error = 0;
    do
    {
        if (error)
            printf("\n Elija una opcion valida\n");
		scanf("%d", &num);
		error = 1;
        while (getchar() != '\n'); // Limpiar buffer
    }
    while (num < min || num > max);
    return num;
}
int ValidarEleccion(int min, int max) {
    int opcion;
    while (1) {
        scanf("%d", &opcion);
        if (opcion >= min && opcion <= max) {
            return opcion;
        }
        printf("Opcion no valida. Intente nuevamente (%d-%d): ", min, max);
    }
}

void MostrarInventario(Personaje *p) {
    printf("\nInventario:\n");
    for (int i = 0; i < p->cant_item; i++) {
        if (strlen(p->invent[i].elemento) > 0 && p->invent[i].usos > 0) {
            printf("%d. %s (%d usos)\n", i + 1, p->invent[i].elemento, p->invent[i].usos);
        } else {
            printf("%d. ---\n", i + 1);
        }
    }
}



int InventarioVacio(Personaje *p) {
    for (int i = 0; i < p->cant_item; i++) {
        if (strlen(p->invent[i].elemento) > 0 && p->invent[i].usos > 0) {
            return 0; // Hay objetos disponibles
        }
    }
    printf("\n¡Inventario vacío!\n");
    return 1;
}

// ----------------- //
/*
// ***********inicio nuevo****************
void InicializarPersonajeVector(Personaje *p_guardado) {
    FILE* fPersonaje = fopen("Datos_iniciales/personajes.dat", "rb");
    if(!fPersonaje) {
        printf("\nError: No se pudo abrir personajes.dat\n");
        exit(EXIT_FAILURE);
    }

    // Verificar tamaño del archivo
    fseek(fPersonaje, 0, SEEK_END);
    long fileSize = ftell(fPersonaje);
    rewind(fPersonaje);

    if(fileSize < sizeof(Personaje) * 5) {
        printf("\nError: Archivo personajes.dat corrupto o incompleto\n");
        fclose(fPersonaje);
        exit(EXIT_FAILURE);
    }

    // Leer los 5 personajes
    size_t read = fread(p_guardado, sizeof(Personaje), 5, fPersonaje);
    if(read != 5) {
        printf("\nError: Solo se leyeron %u personajes\n", read);
        fclose(fPersonaje);
        exit(EXIT_FAILURE);
    }

    fclose(fPersonaje);
}
*/

void Elegir_Personaje(Personaje* p, Personaje* pParaBatalla){
    int opt_personaje;
    char decision ='a';
    while(decision != 'Y')
    {
        system("cls");
        printf("\nElija algun personaje (1-5): \n");

        for(int i=0;i<5;i++)
        {
            printf("\n%d)\t%3s\t<-\n",i+1,p->nombre);
            p++;
        }
        putchar('\n');

        p-=5;
        opt_personaje = validarIntRango(1,5) - 1;
        p+=opt_personaje;

        system("cls");
        mostrarPersonaje(*p);
        printf("\nDecisión final?(Y/N):");
            scanf("%c", &decision);
            while (getchar() != '\n'); // Limpiar buffer
            decision = toupper(decision);

        while(decision !='Y' && decision !='N')
        {
            printf("Decision inválida intente de nuevo (Y/N):");
            scanf("%c", &decision);
            while (getchar() != '\n'); // Limpiar buffer
            decision = toupper(decision);
        }

        if(decision !='Y')
            p-=opt_personaje;
    }
    p-=opt_personaje;
    memcpy(pParaBatalla, &p[opt_personaje], sizeof(Personaje));

}

void establecer_color_texto(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
