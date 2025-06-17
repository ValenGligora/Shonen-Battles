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
                printf("Hola");

                for (int i = 0; i < 5; i++) {
                    if (strcmp(guardado->pj_guardado[i].nombre, personajeBatalla.nombre) == 0) {
                        ActualizarInventario(&guardado->pj_guardado[i], &personajeBatalla);
                        break;
                    }

                }

                // Leer línea después del marcador de batalla
               // fgets(linea, sizeof(linea), fHistoria);

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

    }
    if(skip == 0)
        Sleep(PAUSA_LINEA);

    return skip;
}
