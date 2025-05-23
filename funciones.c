#include "header.h"
#include <windows.h> // Para system() y SetConsoleTextAttribute()

#include <time.h>

#define VELOCIDAD_TIPO 10    // ms entre caracteres
#define PAUSA_LINEA 200      // ms entre líneas
#define PAUSA_PUNTUACION 100 // ms extra para .!?



#include <stdio.h>
#include <stdlib.h>

void mostrar_personajes_disponibles(const char* archivo) {
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
        for (int j = 0; j < 3; j++) {
            if (p.invent[j].usos > 0) {
                printf("  - %s (usos: %d)\n", p.invent[j].elemento, p.invent[j].usos);
            }
        }

        printf("\n");
    }

    fclose(f);
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
            printf("\n Elija una opcion valida");
		scanf("%d", &num);
		error = 1;
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

int InventarioVacio(Personaje *p) {
    for (int i = 0; i < 3; i++) {
        if (strlen(p->invent[i].elemento) > 0 && p->invent[i].usos > 0) {
            return 0; // Hay objetos disponibles
        }
    }
    printf("\n¡Inventario vacio!\n");
    return 1;
}
void MostrarInventario(Personaje *p) {
    printf("\nInventario:\n");
    for (int i = 0; i < 3; i++) {
        if (strlen(p->invent[i].elemento) > 0 && p->invent[i].usos > 0) {
            printf("%d. %s (%d usos)\n", i+1, p->invent[i].elemento, p->invent[i].usos);
        } else {
            printf("%d. ---\n", i+1);
        }
    }
}
void UsarObjeto(Personaje *p, int obj_index) {
    if (obj_index < 0 || obj_index >= 3) return;

    printf("\n%s usa %s!\n", p->nombre, p->invent[obj_index].elemento);

    // Efectos según tipo de objeto (debes implementar esta lógica)
    if (strstr(p->invent[obj_index].elemento, "Cura") != NULL) {
        p->vida += 50;
        if (p->vida > p->vidaMax) p->vida = p->vidaMax;
        printf("¡Restauradas 50 puntos de vida!\n");
    }
    else if (strstr(p->invent[obj_index].elemento, "Cosmo") != NULL) {
        p->cosmo += 30;
        if (p->cosmo > p->cosmoMax) p->cosmo = p->cosmoMax;
        printf("¡Restaurados 30 puntos de cosmo!\n");
    }

    p->invent[obj_index].usos--;
    if (p->invent[obj_index].usos <= 0) {
        memset(p->invent[obj_index].elemento, 0, 30); // Eliminar objeto si no quedan usos
    }
}
int IntentarHuir() {
    return (rand() % 100) < 70; // 70% probabilidad
}

float CalcularAtaque(Personaje *p)
{
    float ataqueCalculado;

    ataqueCalculado = p->ataque + p->ataque * p->arma.danio_porcentual;
    return ataqueCalculado;
}
float CalcularDanioTecnica(Personaje *p, int num_tec) {
    Tecnica *tec = &p->tecnicas[num_tec];

    // Daño base con arma
    float danio_base = p->ataque + (p->ataque * p->arma.danio_porcentual);

    // Daño final modificado por la técnica (asumimos ataque_tec como multiplicador)
    float danio_final = danio_base * tec->ataque_tec;

    // Consumir cosmo
    p->cosmo -= tec->cosmo_necesario;

    return danio_final;
}

void recibeDanio(float danio, Personaje *p, int eleccion)
{
    float defensa;
    if (eleccion == 2)
        defensa = p->defensa;
    else
        defensa = 0;

    float danioInfligido = danio - danio * p->armadura - danio * defensa;

    p->vida -= danioInfligido;
}

void Defender(Personaje *p) {
    // Aumentar la defensa temporalmente (se resetea al final del turno en ejecutar_batalla)
    p->defensa = p->armadura * 1.5f;  // Aumento del 50% en la defensa

    // También regenera un pequeño porcentaje de cosmo
    float cosmoRegenerado = p->cosmoMax * 0.1f;  // 10% del cosmo máximo
    p->cosmo += cosmoRegenerado;
    if (p->cosmo > p->cosmoMax) {
        p->cosmo = p->cosmoMax;
    }

    printf("%s adopta una postura defensiva! (+%.f defensa, +%.f cosmo)\n",
           p->nombre, p->armadura * 0.5f, cosmoRegenerado);
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
        printf("\n%s est� a la defensiva", emisor->nombre);

        break;
    case 3:

        danio = CalcularDanioTecnica(emisor,opt_tec);
        recibeDanio(danio, receptor, eleccionOponente);
        break;
    }
}
void EjecutarAccionEnemiga(Personaje *enemigo, Personaje *prota, int accion, int opt_tec,int opt_oponente) {
    switch(accion) {
        case 1: // Ataque básico
            printf("\n%s ataca con un golpe basico!\n", enemigo->nombre);
            EjecutarAccion(accion,opt_tec,enemigo, prota, opt_oponente);
            break;
        case 2: // Defensa
            printf("\n%s se defiende!\n", enemigo->nombre);
            Defender(enemigo);
            break;
        case 3: // Técnica
            printf("\n%s usa %s!\n", enemigo->nombre, enemigo->tecnicas[opt_tec].nombre);
            float danio = CalcularDanioTecnica(enemigo, opt_tec);
			recibeDanio(danio, prota, opt_oponente);
            break;
    }
}
int EleccionRandomEnemigo(Personaje *enemigo, int *opt_tec_enemigo)
{
    srand(time(NULL));
    int numAccion = -1;

    while (numAccion == -1)
    {
        numAccion = rand() % 3 + 1;

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

int ejecutar_batalla(Personaje *prota, Personaje *enemigo) {
    int opcion, opt_tec, opt_obj, opt_tec_enemigo, eleccionEnemigo;

    while (1) {
		prota->defensa = 0;
		enemigo->defensa = 0;
        system("cls || clear");

        // Mostrar estado de los combatientes
        printf("============================================\n");
        printf("| %-20s VS %-20s |\n", prota->nombre, enemigo->nombre);
        printf("| Vida: %-4.0f/%-4.0f    Vida: %-4.0f/%-4.0f |\n",
               prota->vida, prota->vidaMax, enemigo->vida, enemigo->vidaMax);
        printf("| Cosmo: %-3.0f/%-3.0f   Cosmo: %-3.0f/%-3.0f |\n",
               prota->cosmo, prota->cosmoMax, enemigo->cosmo, enemigo->cosmoMax);
        printf("============================================\n\n");

        // Menú de opciones
        printf("1. Atacar con %s\n", prota->arma.nombre);
        printf("2. Defenderse\n");
        printf("3. Usar tecnica (%d disponibles)\n", prota->cant_tec);
        printf("4. Usar objeto\n");
        printf("5. Huir\n");
        printf("\nElija opcion (1-5): ");

        opcion = validarIntRango(1, 5);

        // Turno del jugador
        switch(opcion) {
            case 1: // Ataque básico
                printf("\n%s ataca con %s!\n", prota->nombre, prota->arma.nombre);
                EjecutarAccion(1, 0, prota, enemigo, 0);
                break;

            case 2: // Defensa
                printf("\n%s se prepara para defender!\n", prota->nombre);
                EjecutarAccion(2, 0, prota, enemigo, 0);
                break;

            case 3: // Técnicas
                if (prota->cant_tec == 0) {
                    printf("\nNo tienes tecnicas disponibles!\n");
                    system("pause");
                    continue;
                }

                printf("\nTecnicas disponibles:\n");
                for (int i = 0; i < prota->cant_tec; i++) {
                    printf("%d. %s (%.1f ATQ, %d Cosmo)\n",
                          i+1, prota->tecnicas[i].nombre,
                          prota->tecnicas[i].ataque_tec,
                          prota->tecnicas[i].cosmo_necesario);
                }
                printf("\nElija tecnica (1-%d): ", prota->cant_tec);

                opt_tec = validarIntRango(1, prota->cant_tec) - 1;

                if (prota->cosmo < prota->tecnicas[opt_tec].cosmo_necesario) {
                    printf("\n¡Cosmo insuficiente! Necesitas %d\n", prota->tecnicas[opt_tec].cosmo_necesario);
                    system("pause");
                    continue;
                }

                printf("\n%s usa %s!\n", prota->nombre, prota->tecnicas[opt_tec].nombre);
                EjecutarAccion(3, opt_tec, prota, enemigo, 0);
                break;

            case 4: // Objetos
                MostrarInventario(prota);
                if (InventarioVacio(prota)) {
                    system("pause");
                    continue;
                }

                printf("\nElija objeto (1-3) o 0 para cancelar: ");
                opt_obj = validarIntRango(0, 3);
                if (opt_obj == 0) continue;

                UsarObjeto(prota, opt_obj - 1);
                break;

            case 5: // Huir
                if (IntentarHuir()) {
                    printf("\n¡Has escapado de la batalla!\n");
                    return -1;
                }
                printf("\n¡La huida ha fallado!\n");
                break;
        }

        // Verificar si el enemigo fue derrotado
        if (enemigo->vida <= 0) {
            printf("\n¡%s ha sido derrotado!\n", enemigo->nombre);
            return 1;
        }

        // Turno del enemigo
        eleccionEnemigo = EleccionRandomEnemigo(enemigo, &opt_tec_enemigo);
        EjecutarAccionEnemiga(enemigo, prota, eleccionEnemigo, opt_tec_enemigo,opcion);

        // Verificar si el jugador fue derrotado
        if (prota->vida <= 0) {
            printf("\n¡Has sido derrotado!\n");
            return 0;
        }


        system("pause");
    }
}

// ----------------- //
void InicializarPersonaje(Personaje *personaje, Personaje *p_guardado,int selec)
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
    }
	printf("\nElija algun personaje: ");
	int opt_personaje = validarIntRango(1,5);
    fseek(fPersonaje,sizeof(personaje),opt_personaje); /*Me muevo a la estructura de personaje que quiero usar*/
    fread(&personaje,sizeof(personaje),1,fPersonaje); /* Leo los datos de ese personaje*/
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
