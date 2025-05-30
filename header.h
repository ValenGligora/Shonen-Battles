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

typedef struct{
    char Nombre[20];
    float vida;
    float vidaMax;
    float ataque;
    float cosmo;
    float cosmoMax;
    float defensa;
    Tecnica tecnicas[2];
    char Inicio_Batalla[250];
} Enemigo;

typedef struct
{
    long posicion_historia;
    int num_batalla;
    Personaje pj_guardado[5]; // atributos de los personajes
} DatosPartida;

// ------------------------------ -------------------- --------------------------- //

// -------------------------ENCABEZADO FUNCIONES -----------------------//

//--FUNCIONES NO IMPLEMENTADAS--
void crear_archivo_historia();
void batalla(FILE, Personaje);  // Se desarrolla cada batalla la batalla habria que hacerla con memoria dinamica que es parte de la consigna
int sigue_con_vida(Personaje);  // Consulta si sigue con vida
void mostrar_estado(Personaje); // Mostrar vida, acciones disponibles, etc
// void crear_archivo_Personajes_Principales();


//--Historia.c--

void jugar_historia(const char *archivo_historia, DatosPartida *save, const char *archivo_enemigos);
int efecto_typing(const char* texto,int skip);

void mostrar_personajes_disponibles(const char*);

//--Funciones.c--

void mostrar_menu();
int menu_principal();
void cargar_partida(int n, DatosPartida *datos, const char *nombreArchivo);
void guardar_partida(const char*, DatosPartida *save);

int ValidarEleccion(int min, int max);
int validarIntRango(int, int);
void MostrarInventario(Personaje *p);
int InventarioVacio(Personaje *p);
void Elegir_Personaje(Personaje* p,Personaje* pParaBatalla);

void establecer_color_texto(int color);


//--Comabte.c--
float CalcularDanioTecnicaEnemigo(Enemigo *e, int num_tec);
int ejecutar_batalla(Personaje *prota, Enemigo *enemigo);
void UsarObjeto(Personaje *p, int obj_index);
float CalcularAtaque(Personaje *prota);
float CalcularAtaqueTecnica(Personaje *p, int num_tec);
float CalcularDanioTecnica(Personaje *p, int num_tec);
void recibeDanio(float danio, Personaje *p, int eleccion);
void Defender(Personaje *p);

//--Perosnajes.c--

void InicializarPersonajeVector(Personaje *p_guardado);
void mostrarPersonaje(Personaje p);
void EjecutarAccion(int, int, Personaje *, Personaje *, int);

//--Enemigos.c--

Enemigo cargar_enemigo_n(int n, const char *archivo);
int EleccionRandomEnemigo(Enemigo *enemigo, int *opt_tec_enemigo);
void EjecutarAccionEnemiga(Enemigo *enemigo, Personaje *prota, int accion, int opt_tec,int opt_oponente);

// ------------------------------ -------------------- --------------------------- //

#endif // HEADER_H_INCLUDED
