#include "header.h"

void leer_historia(FILE *archivo, char *buffer, size_t tam_buffer)
{

    system("cls");
    int skip=0; //saltear introduccion
    do
    {
        //buffer[strcspn(buffer, "\n")] = '\0'; // Eliminar salto de línea

        if (buffer[0] == '|') break;

        printf("%5s"," ");
        skip = efecto_typing(buffer,skip);
    }while (fgets(buffer, tam_buffer, archivo));

    establecer_color_texto(14);
    printf("\n  ╔══════════════════════════════════════════════════╗\n");
    printf("  ║        PRESIONA ENTER PARA CONTINUAR...          ║\n");
    printf("  ╚══════════════════════════════════════════════════╝\n");
    establecer_color_texto(7); // Restaurar color

    while (getchar() != '\n'); // Limpiar buffer
    getchar(); // Esperar Enter
}

// Función principal para jugar la historia
/*void jugar_historia(const char *archivo_historia, DatosPartida *guardado, const char *archivo_enemigos)
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
    Personaje personajeBatalla;
    fseek(fHistoria, guardado->posicion_historia, SEEK_SET); // Continuar desde última posición

    char linea[200];
    fgets(linea, sizeof(linea), fHistoria);

    puts("DECLARO VARIABLES");
    printf("\n");
    while (!feof(fHistoria) && opcion_Menu != -1)
    {
        printf("ENTRÓ A LEER");
        leer_historia(fHistoria, linea, sizeof(linea));

        if (linea[0] == '|') // Cada vez que encuentra el delimitador entra en una batalla
        {
            printf("ENTRÓ A BATALLA");

            while (opcion_Menu != -1 && resultado_batalla != 1)
            {

                Elegir_Personaje(guardado->pj_guardado,&personajeBatalla);//la cambie de posicion asi si se pierde el combate pueden probar con otro personaje

                system("cls");
                printf("\n\t>>> ¡BATALLA %d! <<<\n", guardado->num_batalla + 1);
                putchar('\n');
                system("pause");

                Enemigo enemigo = cargar_enemigo_n(guardado->num_batalla, archivo_enemigos);
                resultado_batalla = ejecutar_batalla(&personajeBatalla, &enemigo); // 1 gana ; 0 pierde ; -1 decide escapar de la batalla
                if (resultado_batalla != 1) // Consultar si desea intentarlo de nuevo o desea guardar la partida.
                {
                    printf("Intentar de nuevo? (1)\nGuardar partida y salir? (-1)\n");
                    scanf("%d", &opcion_Menu);
                }
            }

            // Solo se incrementa el número de batallas si la batalla es ganada
            if (resultado_batalla == 1)
            {

                // ESPACIO PARA DAR RECOMPENSAS AL JUGADOR CON EL PERSONAJE QUE HAYA ELEGIDO

                //

                posicion_Historia_postBatalla = ftell(fHistoria); // En este caso que ganamos, actualizo el fseek
                guardado->num_batalla++;
                guardado->posicion_historia = posicion_Historia_postBatalla; // Guardar para continuar historia después de la última batalla ganada
                guardar_partida("Partida.dat", guardado);
            }
        }
        else if (opcion_Menu != -1)
        {
            // En este caso que NO ganamos, no se actualiza el fseek
            guardado->num_batalla++;  // Solo incrementar la batalla si no es un bucle de batallas fallidas
            guardado->posicion_historia = posicion_Historia_postBatalla; // Guardar para comenzar historia luego de la última batalla ganada
            //Elegir_Personaje(guardado->pj_guardado,&personajeBatalla);//permitir elegir con que persoanje pelear la batalla de nuevo.
            guardar_partida("save.dat", guardado);
        }

        resultado_batalla = 0;  // Resetear el resultado de la batalla después de cada iteración
        fgets(linea, sizeof(linea), fHistoria);  // Leer la siguiente línea de la historia
    }

    fclose(fHistoria);
}
*/
/*void jugar_historia(const char *archivo_historia, DatosPartida *guardado, const char *archivo_enemigos)
{
    FILE *fHistoria = fopen(archivo_historia, "r");
    if (!fHistoria)
    {
        perror("No se pudo abrir historia");
        return;
    }

    int resultado_batalla = 0;
    int opcion_Menu = 1;
    long posicion_Historia_postBatalla;
    Personaje personajeBatalla;
    int salir;

    fseek(fHistoria, guardado->posicion_historia, SEEK_SET);

    char linea[200];
    fgets(linea, sizeof(linea), fHistoria);

    while (!feof(fHistoria) && opcion_Menu != -1)
    {
        leer_historia(fHistoria, linea, sizeof(linea));

        if (linea[0] == '|') // INICIO DE BATALLA
        {
            do
            {
                Elegir_Personaje(guardado->pj_guardado, &personajeBatalla);
                Enemigo enemigo = cargar_enemigo_n(guardado->num_batalla, archivo_enemigos);

                system("cls");
                printf("\n>>> ¡BATALLA %d! <<<\n\n", guardado->num_batalla + 1);
                puts(enemigo.Inicio_Batalla);
                putchar('\n');
                system("pause");

                resultado_batalla = ejecutar_batalla(&personajeBatalla, &enemigo);

                if (resultado_batalla == HUYE)//-1
                {
                    printf("\nHas escapado. ¿Deseás guardar y salir? (1 = Sí, 0 = No): ");
                    scanf("%d", &salir);
                    if (salir == 1) {
                        guardar_partida("Guardado/Partida.dat", guardado);
                        fclose(fHistoria);
                        return;
                    }
                }
                else if (resultado_batalla == DERROTADO)//0
                {
                    printf("\n¿Intentar de nuevo? (1 = Sí, -1 = Salir): ");
                    scanf("%d", &opcion_Menu);
                }

            }while (opcion_Menu != -1 && resultado_batalla != 1);

            // Si ganó la batalla
            if (resultado_batalla == GANA)//1
                {
                    //Sincronizar inventario del personaje elegido con su original
                    for (int i = 0; i < 5; i++) {
                        if (strcmp(guardado->pj_guardado[i].nombre, personajeBatalla.nombre) == 0) {
                            ActualizarInventario(&guardado->pj_guardado[i], &personajeBatalla);
                            break;
                        }
                    }
                    posicion_Historia_postBatalla = ftell(fHistoria);
                    guardado->num_batalla++;
                    guardado->posicion_historia = posicion_Historia_postBatalla;

                    int guardar = 0;
                    printf("\n¿Deseás guardar tu progreso? (1 = Sí / 0 = No): ");
                    guardar = validarIntRango(0,1);

                    if (guardar == 1) {
                        guardar_partida("Guardado/Partida.dat", guardado);
                        printf("✅ Partida guardada exitosamente.\n");
                        system("pause");
                    } else {
                        printf("⚠️ Progreso no guardado.\n");
                        system("pause");
                    }
                }
        }

        // Leer siguiente línea de la historia
        resultado_batalla = 0;
        fgets(linea, sizeof(linea), fHistoria);
    }

    fclose(fHistoria);
}
*/
void jugar_historia(const char *archivo_historia, DatosPartida *guardado, const char *archivo_enemigos)
{
    FILE *fHistoria = fopen(archivo_historia, "r");
    if (!fHistoria) {
        perror("No se pudo abrir historia");
        return;
    }

    int resultado_batalla = 0;
    int opcion_Menu = 1;
    Personaje personajeBatalla;
    char linea[200];

    // Posicionarse en la última línea guardada
    fseek(fHistoria, guardado->posicion_historia, SEEK_SET);
    fgets(linea, sizeof(linea), fHistoria);

    while (!feof(fHistoria) && opcion_Menu != -1)
    {
        leer_historia(fHistoria, linea, sizeof(linea));

        if (linea[0] == '|') // INICIO DE BATALLA
        {
            do {
                Elegir_Personaje(guardado->pj_guardado, &personajeBatalla);
                Enemigo enemigo = cargar_enemigo_n(guardado->num_batalla, archivo_enemigos);

                system("cls");
                printf("\n>>> ¡BATALLA %d! <<<\n\n", guardado->num_batalla + 1);
                puts(enemigo.Inicio_Batalla);
                putchar('\n');
                system("pause");

                resultado_batalla = ejecutar_batalla(&personajeBatalla, &enemigo);

                if (resultado_batalla == HUYE) {
                    int salir = 0;
                    printf("\nHas escapado. ¿Deseás guardar y salir? (1 = Sí, 0 = No): ");
                    scanf("%d", &salir);
                    if (salir == 1) {
                        guardar_partida("Guardado/Partida.dat", guardado);
                        fclose(fHistoria);
                        return;
                    }
                } else if (resultado_batalla == DERROTADO) {
                    printf("\n¿Intentar de nuevo? (1 = Sí, -1 = Salir): ");
                    scanf("%d", &opcion_Menu);
                }

            } while (opcion_Menu != -1 && resultado_batalla != GANA);

            if (resultado_batalla == GANA) {
                // Actualizar personaje real con el que peleó
                for (int i = 0; i < 5; i++) {
                    if (strcmp(guardado->pj_guardado[i].nombre, personajeBatalla.nombre) == 0) {
                        ActualizarInventario(&guardado->pj_guardado[i], &personajeBatalla);
                        break;
                    }
                }

                // Leer línea después del marcador de batalla
                fgets(linea, sizeof(linea), fHistoria);

                // Guardar progreso
                guardado->posicion_historia = ftell(fHistoria);
                guardado->num_batalla++;

                guardar_partida("Guardado/Partida.dat", guardado);
                printf("\n¡Progreso y recompensa guardados automáticamente!\n");
                system("pause");
            }
        }

        resultado_batalla = 0;
        fgets(linea, sizeof(linea), fHistoria);  // siguiente línea de historia
    }

    fclose(fHistoria);
}


int efecto_typing(const char* texto, int skip)
{
    for (int i = 0; texto[i] != '\0'; i++)
    {
        putchar(texto[i]);
        fflush(stdout);

        if (texto[i] != ' ' && skip== 0)
            Sleep(VELOCIDAD_TIPO);

        if (!skip && kbhit())
        {
            char c = _getch();
            if (c == '\r')
                { // Enter es '\r' en Windows
                skip = 1;
                }
        }
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
    if(skip == 0)
        Sleep(PAUSA_LINEA);

    return skip;
}
