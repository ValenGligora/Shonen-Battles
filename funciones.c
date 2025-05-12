#include "header.h"
#include <windows.h> // Para system() y SetConsoleTextAttribute()

#include <time.h>

#define VELOCIDAD_TIPO 10    // ms entre caracteres
#define PAUSA_LINEA 200      // ms entre líneas
#define PAUSA_PUNTUACION 100 // ms extra para .!?

FILE* cargar_partida(int n, DatosPartida *datos, const char *nombreArchivo)
{
    FILE *partida;
    if (n == 1)
    {
        // Cargar partida (Opcion numero 1)
        partida = fopen(nombreArchivo, "rb");
        if (partida == NULL)
        {
            puts("No se pudo cargar la partida");
            exit(1);
        }
        fread(datos, sizeof(DatosPartida), 1, partida); // Lee etiqueta de historia en la que quedó y todos los datos del personaje
    }
    else
    {
        // Nueva partida
        partida = fopen(nombreArchivo, "wb");

        datos->num_batalla=0;
        datos->posicion_historia=0;

        if (partida == NULL)
        {
            puts("No se pudo crear la partida");
            exit(1);
        }
    }
    fclose(partida);
    return partida;
    /* si se carga la partida hay que extraer la informacino y almacenarla en la memoria dinamica
    sino se crea el archivo y se los debe cargar con los datos iniciales de la partida*/
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
void InicializarPersonaje(Personaje *personaje, Personaje *p_guardado,int selec)
{
    if(selec == 1)
    {
        personaje = p_guardado;
        return;
    }
    FILE* fPersonaje = fopen("protagonistas_saga.dat","rb");
    if(!fPersonaje)
    {
        printf("\nNo se pudo abrir el archivo de personajes");
        return;
    }
    fread(&personaje,sizeof(personaje),1,fPersonaje); 	// Por ahora vamos a cargar siempre el primero en la lista de personajes
    fclose(fPersonaje);

}
Personaje cargar_enemigo_n(int n, const char *archivo)
{
    Personaje enem;
    FILE *f = fopen(archivo, "rb");
    if (!f)
    {
        perror("No se pudo abrir archivo de enemigos");
        exit(1);
    }

    fseek(f, sizeof(Personaje) * n, SEEK_SET); // saltar a enemigo n
    fread(&enem, sizeof(Personaje), 1, f);
    fclose(f);
    return enem;
}

int ejecutar_batalla(Personaje *prota, Personaje *enemigo)
{
    int opcion;
    int opt_tec;
    int opt_tec_enemigo;
    int eleccionEnemigo;
    // aca va la parte del menu

    printf("Elija opcion: 1-atacar , 2-defenderse, 3-habilidad");
    opcion = ValidarEleccion(1, 3, prota->cant_tec, &opt_tec, prota->tecnicas, prota->Cosmo);

    eleccionEnemigo = EleccionRandomEnemigo(enemigo, &opt_tec_enemigo);

    while (opcion != 4) // la opcion 4 seria salir de la batalla, escapar
    {
        EjecutarAccion(opcion, opt_tec, prota, enemigo, eleccionEnemigo);
        if (enemigo->Vida <= 0)
        {
            return 1; // Ganó
        }

        EjecutarAccion(opcion, opt_tec, enemigo, prota, eleccionEnemigo);
        if (prota->Vida <= 0)
        {
            return 0; // Perdió
        }
    }
    return -1;  // Eligió escapar
}
int ValidarEleccion(int min, int max, int cantTec, int *opt_tec, Tecnica tecnicas[], float cosmo)
{
    int n = -1;

    while (n == -1)
    {
        n = validarIntRango(min, max);

        // if (n == 2)
        //  opt_tec = seleccionarTecnica(&tecnicas,cant_tec,cosmo);
        // menu que muestre la tecnicas disponibles
        // debe validar que alcance el cosmo para poder realizarla
        // si el usuario se arreepiente de elegir esta opcion , el valor de n pasa a ser -1

        // en este caso voy a elegir siempre la [0], pero lo debe hacer la funcion selecccionarTecnica();
        if (n == 2)
            *opt_tec = 0; // elijo la primer tecnica
    }
    return n;
}
int validarIntRango(int min, int max)
{
    int num;
    int error = 0;
    do
    {
        scanf("%d", &num);
        error = 1;
        if (error)
            printf("\n Elija una opcion valida");
    }
    while (num < min || num > max);
    return num;
}
int EleccionRandomEnemigo(Personaje *enemigo, int *opt_tec_enemigo)
{
    srand(time(NULL));
    int numAccion = -1;

    while (numAccion == -1)
    {
        int numAccion = rand() % 3 + 1;

        // if (numAccion == 2)
        //  opt_tec = seleccionarTecnica(&tecnicas,cant_tec,cosmo);
        // menu que muestre la tecnicas disponibles
        // debe validar que alcance el cosmo para poder realizarla
        // si el usuario se arreepiente de elegir esta opcion , el valor de n pasa a ser -1

        // en este caso voy a elegir siempre la [0], pero lo debe hacer la funcion selecccionarTecnica();
        if (numAccion == 2)
            *opt_tec_enemigo = 0; // elijo la primer tecnica
    }

    return numAccion;
}

void EjecutarAccion(int opt, int opt_tec, Personaje *emisor, Personaje *receptor, int eleccionOponente)
{
    float danio;
    switch (opt)
    {
    case 1:
        danio = CalcularAtaque(emisor);
        recibeDanio(danio, receptor, eleccionOponente);
        break;
    case 2:
        printf("\n%s est� a la defensiva", emisor->Nombre);

        break;
    case 3:

        danio = CalcularAtaqueTecnica(emisor, 0); // el segundo parametro es opt_tec
        recibeDanio(danio, receptor, eleccionOponente);
        break;
    }
}
float CalcularAtaque(Personaje *p)
{
    float ataqueCalculado;

    ataqueCalculado = p->ataque + p->ataque * p->arma.danio_porcentual;
    return ataqueCalculado;
}
float CalcularAtaqueTecnica(Personaje *p, int num_tec) // hacemos una funcion nueva por que capaz tiene otros efectos las tecnica, ademas consume cosmo
{
    float ataqueCalculado;

    ataqueCalculado = p->tecnicas[num_tec].ataque_tec + p->ataque * p->arma.danio_porcentual;
    p->Cosmo -= p->tecnicas[num_tec].cosmo_necesario;

    return ataqueCalculado;
}
void recibeDanio(float danio, Personaje *p, int eleccion)
{
    float defensa;
    if (eleccion == 2)
        defensa = p->defensa;
    else
        defensa = 0;

    float danioInfligido = danio - danio * p->Armadura - danio * defensa;

    p->Vida -= danioInfligido;
}


void establecer_color_texto(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

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




void efecto_typing(const char* texto)
{
    for (int i = 0; texto[i] != '\0'; i++)
    {
        putchar(texto[i]);
        fflush(stdout);

        if (texto[i] != ' ')
            Sleep(VELOCIDAD_TIPO);

        /*
            switch(texto[i]) {
                case '.': case '!': case '?': case ':':
                    Sleep(PAUSA_PUNTUACION);
                    break;
                case ',': case ';':
                    Sleep(PAUSA_PUNTUACION/2);
                    break;

            }
        */
    }
}

void leer_historia(FILE *archivo, char *buffer, size_t tam_buffer)
{

    system("cls");
    while (fgets(buffer, tam_buffer, archivo))
    {
        //buffer[strcspn(buffer, "\n")] = '\0'; // Eliminar salto de línea

        if (buffer[0] == '|') break;

        printf("%5s"," ");
        efecto_typing(buffer);
        Sleep(PAUSA_LINEA);
    }

    establecer_color_texto(14);
    printf("\n  ╔══════════════════════════════════════════════════╗\n");
    printf("  ║       PRESIONA ENTER PARA CONTINUAR...        ║\n");
    printf("  ╚══════════════════════════════════════════════════╝\n");
    establecer_color_texto(7); // Restaurar color

    while (getchar() != '\n'); // Limpiar buffer
    getchar(); // Esperar Enter
}

// Función principal para jugar la historia
void jugar_historia(const char *archivo_historia, DatosPartida *guardado, const char *archivo_enemigos)
{
    FILE *fHistoria = fopen(archivo_historia, "r");
    if (!fHistoria)
    {
        perror("No se pudo abrir historia");
        return;
    }

    int resultado_batalla = 0;
    int opcion_Menu = 1; // distinto de -1 para entrar
    long posicion_Historia_postBatalla;
    fseek(fHistoria, guardado->posicion_historia, SEEK_SET); // Continuar desde última posición

    char linea[200];
    fgets(linea, sizeof(linea), fHistoria);

    printf("\n");
    while (!feof(fHistoria) && opcion_Menu != -1)
    {
        leer_historia(fHistoria, linea, sizeof(linea));

        if (linea[0] == '|') // Cada vez que encuentra el delimitador entra en una batalla
        {
            while (opcion_Menu != -1 && resultado_batalla != 1)
            {
                printf("\n>>> ¡Batalla %d! <<<\n", guardado->num_batalla + 1);
                Personaje enemigo = cargar_enemigo_n(guardado->num_batalla, archivo_enemigos);
                resultado_batalla = ejecutar_batalla(&guardado->pj_guardado, &enemigo); // 1 gana ; 0 pierde ; -1 decide escapar de la batalla
                if (resultado_batalla != 1) // Consultar si desea intentarlo de nuevo o desea guardar la partida.
                {
                    printf("Intentar de nuevo? 1 , Guardar partida y salir? -1");
                    scanf("%d", &opcion_Menu);
                }
            }

            // Solo se incrementa el número de batallas si la batalla es ganada
            if (resultado_batalla == 1)
            {
                posicion_Historia_postBatalla = ftell(fHistoria); // En este caso que ganamos, actualizo el fseek
                guardado->num_batalla++;
                guardado->posicion_historia = posicion_Historia_postBatalla; // Guardar para continuar historia después de la última batalla ganada
                guardar_partida("save.dat", guardado);
            }
        }
        else if (opcion_Menu != -1)
        {
            // En este caso que NO ganamos, no se actualiza el fseek
            guardado->num_batalla++;  // Solo incrementar la batalla si no es un bucle de batallas fallidas
            guardado->posicion_historia = posicion_Historia_postBatalla; // Guardar para comenzar historia luego de la última batalla ganada
            guardar_partida("save.dat", guardado);
        }

        resultado_batalla = 0;  // Resetear el resultado de la batalla después de cada iteración
        fgets(linea, sizeof(linea), fHistoria);  // Leer la siguiente línea de la historia
    }

    fclose(fHistoria);
}
