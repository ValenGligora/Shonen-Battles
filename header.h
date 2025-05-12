#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define NO_SE_ENCONTRO_PARTIDA 2

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

} Tecnica; // estar�a interesante hacer un tda que reserve espacio seg�n la cantidad de habilidad que tenga el personaje, sino pongo como maximo 3 tecnicas

typedef struct
{
    char Nombre[20];
    float Vida;
    float ataque;
    float Cosmo;
    float Armadura;
    float defensa;
    Arma arma;
    Tecnica tecnicas[5];
    int cant_tec;
    Inventario invent[3];
} Personaje;

typedef struct
{
    long posicion_historia;
    int num_batalla;
    Personaje pj_guardado; // estado del personaje completo
} DatosPartida;

// ------------------------------ -------------------- --------------------------- //

// -------------------------ENCABEZADO FUNCIONES -----------------------//

//--PRUEBA--
void crear_archivo_historia();
// void crear_archivo_Personajes_Principales();

//--ARCHIVO PARTIDA--
FILE *cargar_partida(int n, DatosPartida *datos, const char *nombreArchivo);
void guardar_partida(const char*, DatosPartida *save);

//--JUEGO--
// int menu_principal();                                     // Mostrar inicio: "iniciar juego", "salir", "continuar aventura"
int menu_principal();
void jugar_historia(const char *archivo_historia, DatosPartida *save, const char *archivo_enemigos);
//--BATALLA--
void batalla(FILE, Personaje);  // Se desarrolla cada batalla
int sigue_con_vida(Personaje);  // Consulta si sigue con vida
void mostrar_estado(Personaje); // Mostrar vida, acciones disponibles, etc

void InicializarPersonaje(Personaje *, Personaje *,int selec); // el siguiente parametro seria el nombre del archivo con los atributos del personaje
void CargarEnemigo(int n, const char *archivo, Personaje enem);
int ejecutar_batalla(Personaje *prota, Personaje *enemigo);

int ValidarEleccion(int, int, int, int *, Tecnica tecnicas[], float cosmo);
int validarIntRango(int, int);
int EleccionRandomEnemigo(Personaje *enemigo, int *opt_tec_enemigo);

void EjecutarAccion(int, int, Personaje *, Personaje *, int);
float CalcularAtaque(Personaje *prota);
float CalcularAtaqueTecnica(Personaje *p, int num_tec);
void recibeDanio(float danio, Personaje *p, int eleccion);

// ------------------------------ -------------------- --------------------------- //

#endif // HEADER_H_INCLUDED
