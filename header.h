#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h> // Para system() y SetConsoleTextAttribute()
#include <conio.h> // para _getch() y kbhit SOLO FUNCIONA EN WINDOWS
#include <windows.h>

#define NO_SE_ENCONTRO_PARTIDA 2

#define VELOCIDAD_TIPO 40   // ms entre caracteres
#define PAUSA_LINEA 100      // ms entre l�neas
#define PAUSA_PUNTUACION 250 // ms extra para .!?

#define INTENTAR_HUIR() ((rand() % 100) < 70)

// ------------------------------ ESTRUCTURAS --------------------------- //
typedef struct
{
    char elemento[30];
    int usos; // Cantidad de veces que el usuario puede usar el elemento
} Inventario;

typedef struct
{
    char nombre[30];
    float danio_porcentual;
} Arma;

typedef struct
{
    char nombre[30];
    float ataque_tec;
    int cosmo_necesario;

} Tecnica;

typedef struct
{
    char nombre[20];
    float vida;
    float vidaMax;
    float ataque;
    float cosmo;
    float cosmoMax;
    float armadura;
    float defensa;
    Arma arma;
    Tecnica tecnicas[3];
    int cant_tec;
    Inventario invent[5];
    int cant_item;
} Personaje;

typedef struct
{
    long posicion_historia;
    int num_batalla;
    Personaje pj_guardado[5]; // atributos de los personajes
} DatosPartida;

// ------------------------------ -------------------- --------------------------- //

// -------------------------ENCABEZADO FUNCIONES -----------------------//

//--PRUEBA--
void crear_archivo_historia();
// void crear_archivo_Personajes_Principales();

//--ARCHIVO PARTIDA--
void cargar_partida(int n, DatosPartida *datos, const char *nombreArchivo);

void guardar_partida(const char*, DatosPartida *save);
void mostrarPersonaje(Personaje p);

//--JUEGO--
// int menu_principal();                                     // Mostrar inicio: "iniciar juego", "salir", "continuar aventura"
int menu_principal();
void mostrar_personajes_disponibles(const char*);
void jugar_historia(const char *archivo_historia, DatosPartida *save, const char *archivo_enemigos);
int efecto_typing(const char* texto,int skip);
void establecer_color_texto(int color);

//--EXTRA--

void MostrarInventario(Personaje *p);
int InventarioVacio(Personaje *p);
void UsarObjeto(Personaje *p, int obj_index);


//--BATALLA--

void batalla(FILE, Personaje);  // Se desarrolla cada batalla la batalla habria que hacerla con memoria dinamica que es parte de la consigna
int sigue_con_vida(Personaje);  // Consulta si sigue con vida
void mostrar_estado(Personaje); // Mostrar vida, acciones disponibles, etc
void recibeDanio(float danio, Personaje *p, int eleccion);
void EjecutarAccion(int, int, Personaje *, Personaje *, int);

void Defender(Personaje *p);

void InicializarPersonajeVector(Personaje *p_guardado);
void Elegir_Personaje(Personaje* p,Personaje* pParaBatalla);

int ejecutar_batalla(Personaje *prota, Personaje *enemigo);

int ValidarEleccion(int min, int max);
int validarIntRango(int, int);

//--Enemigo--
int EleccionRandomEnemigo(Personaje *enemigo, int *opt_tec_enemigo);
void EjecutarAccionEnemiga(Personaje *enemigo, Personaje *prota, int accion, int opt_tec,int opt_oponente);
Personaje cargar_enemigo_n(int n, const char *archivo);

float CalcularAtaque(Personaje *prota);
float CalcularAtaqueTecnica(Personaje *p, int num_tec);
float CalcularDanioTecnica(Personaje *p, int num_tec);

// ------------------------------ -------------------- --------------------------- //

#endif // HEADER_H_INCLUDED
