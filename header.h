#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h> // Para system() y SetConsoleTextAttribute()
#include <conio.h> // para _getch() y kbhit SOLO FUNCIONA EN WINDOWS
#include <windows.h>
#include <ctype.h>

#define NO_SE_ENCONTRO_PARTIDA 2

#define VELOCIDAD_TIPO 40   // ms entre caracteres
#define PAUSA_LINEA 100      // ms entre l�neas

#define GANA 1
#define DERROTADO 0
#define HUYE -1

#define CANT_PERSONAJES 5

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
    Inventario *invent;
    int cant_item;
    int max_item;
} Personaje;

typedef struct {
    Personaje pj;
    Inventario invent_copia[10];
} PersonajeSerializado;

typedef struct {
    long posicion_historia;
    int num_batalla;
    PersonajeSerializado p_serializados[5];
} DatosPartidaSerializada;

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

//--Historia.c--
void leer_historia(FILE *archivo, char *buffer, size_t tam_buffer);
void jugar_historia(const char *archivo_historia, DatosPartida *save, const char *archivo_enemigos);
int efecto_typing(const char* texto,int skip);

void mostrar_personajes_disponibles(const char*);

//--Funciones.c--

void mostrar_menu();
int menu_principal();
void SerializarPersonajes(Personaje *pj, PersonajeSerializado *serializados, int cantPer);
void cargar_partida(int n, DatosPartida *datos, const char *nombreArchivo);
void guardar_partida(const char*, DatosPartida *save);

int ValidarEleccion(int min, int max);
int validarIntRango(int, int);
void MostrarInventario(Personaje *p);
int InventarioVacio(Personaje *p);
void Elegir_Personaje(Personaje* p,Personaje* pParaBatalla);

void establecer_color_texto(int color);


//--Comabte.c--
void mostrarEstadoCombatientes(const Personaje* prota,const Enemigo* enemigo);
int mostrar_menu_acciones(const Personaje *prota);
void procesarTurnoJugador(int opcion, Personaje *prota, Enemigo *enemigo, int *continuarTurno);
int ejecutar_batalla(Personaje *prota, Enemigo *enemigo);
void UsarObjeto(Personaje *p, int obj_index);
float CalcularDanioTecnica(void *entidad, int num_tec, int tipo_entidad);
float recibeDanio(float danio, float defensaBase, float armadura,int eleccion);
void Defender(void* entidad, int tipo_entidad);
void RecibirRecompensa(Personaje *p);
void ActualizarInventario(Personaje *perOriginal, Personaje *perBatalla);

//--Perosnajes.c--

void InicializarPersonajeVector(Personaje *p_guardado);
void mostrarPersonaje(Personaje p);
void EjecutarAccion(int, int, Personaje *emisor, Enemigo *receptor, int);

//--Enemigos.c--

Enemigo cargar_enemigo_n(int n, const char *archivo);
int EleccionRandomEnemigo(Enemigo *enemigo, int *opt_tec_enemigo);
void EjecutarAccionEnemiga(Enemigo *enemigo, Personaje *prota, int accion, int opt_tec,int opt_oponente);

// ------------------------------ -------------------- --------------------------- //

#endif // HEADER_H_INCLUDED
