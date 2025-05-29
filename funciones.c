#include "header.h"

#define VELOCIDAD_TIPO 40   // ms entre caracteres
#define PAUSA_LINEA 100      // ms entre líneas
#define PAUSA_PUNTUACION 250 // ms extra para .!?

/*void mostrar_personajes_disponibles(const char* archivo) {
    FILE* f = fopen(archivo, "rb");
    if (f == NULL) {
        puts("No se pudo abrir el archivo de personajes.");
        return;
    }

    Personaje p;
    int i = 1;
    while (fread(&p, sizeof(Personaje), 1, f) == 1) {
        printf("---- Personaje #%d ----\n", i++);
        printf("Nombre: %s\n", p.nombre);
        printf("Vida: %.1f / %.1f\n", p.vida, p.vidaMax);
        printf("Cosmo: %.1f / %.1f\n", p.cosmo, p.cosmoMax);
        printf("Ataque: %.1f\n", p.ataque);
        printf("Armadura: %.1f | Defensa: %.1f\n", p.armadura, p.defensa);

        // Mostrar arma
        printf("Arma: %s (Daño: %.1f%%)\n", p.arma.nombre, p.arma.danio_porcentual);

        // Mostrar técnicas
        printf("Técnicas:\n");
        for (int j = 0; j < p.cant_tec; j++) {
            printf("  - %s | Daño: %.1f | Cosmo: %d\n",
                   p.tecnicas[j].nombre,
                   p.tecnicas[j].ataque_tec,
                   p.tecnicas[j].cosmo_necesario);
        }

        // Mostrar inventario
        printf("Inventario:\n");
        for (int j = 0; j < 2; j++) {
            if (p.invent[j].usos > 0) {
                printf("  - %s (usos: %d)\n", p.invent[j].elemento, p.invent[j].usos);
            }
        }

        printf("\n");
    }

    fclose(f);
}
*/
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
        break;
    case 2:
        printf("\n   -> Iniciando nueva partida...\n\n");
        Sleep(1000);
        break;
    default:
        printf("\n   Saliendo del juego. Hasta la proxima!\n");
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
    printf("PARTIDA CARGADA");
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
            printf("%d. %s (%d usos)\n", i+1, p->invent[i].elemento, p->invent[i].usos);
        } else {
            printf("%d. ---\n", i+1);
        }
    }
}

int InventarioVacio(Personaje *p) {
    for (int i = 0; i < p->cant_item; i++) {
        if (strlen(p->invent[i].elemento) > 0 && p->invent[i].usos > 0) {
            return 0; // Hay objetos disponibles
        }
    }
    printf("\n¡Inventario vacio!\n");
    return 1;
}

// ----------------- //
/*void InicializarPersonaje(Personaje *personaje, Personaje *p_guardado,int selec)
{
    if(selec == 1)
    {
        personaje = p_guardado;
        return;
    }
    FILE* fPersonaje = fopen("Datos_iniciales/personajes.dat","rb");
    if(!fPersonaje)
    {
        printf("\nNo se pudo abrir el archivo de personajes");
        return;

	printf("\nElija algun personaje: ");
	int opt_personaje = validarIntRango(1,5);
    fseek(fPersonaje,sizeof(personaje),opt_personaje); //Me muevo a la estructura de personaje que quiero usar
    fread(&personaje,sizeof(personaje),1,fPersonaje); // Leo los datos de ese personaje
    fclose(fPersonaje);

}
*/

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
/*
    for (int i=0;i<5;i++){
        printf("\n=== %s ===\n", p->nombre);
        printf("Vida: %.1f/%.1f\n", p->vida, p->vidaMax);
        printf("Cosmo: %.1f/%.1f\n", p->cosmo, p->cosmoMax);
        printf("Ataque: %.1f\n", p->ataque);
        printf("Armadura: %.1f\n", p->armadura);
        printf("Defensa: %.1f\n", p->defensa);

        printf("\nArma: %s (%.2fx daño)\n", p->arma.nombre, p->arma.danio_porcentual);

        printf("\nTécnicas %d:\n", p->cant_tec);
        for (int j = 0; j < p->cant_tec; j++) {
            printf("- %s (Daño: %.1f, Cosmo: %d)\n",
                p->tecnicas[j].nombre,
                p->tecnicas[j].ataque_tec,
                p->tecnicas[j].cosmo_necesario);
        }

        printf("\nInventario:\n");
        for (int k = 0; k < p->cant_item; k++) {
            if (strlen(p->invent[k].elemento) > 0) {
                printf("- %s (usos: %d)\n", p->invent[k].elemento, p->invent[k].usos);
            }
        }
        printf("\n");
        p++;
    }
    p-=5;
	opt_personaje = validarIntRango(1,5) - 1;
    p+=opt_personaje;
*/
}

void establecer_color_texto(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
