#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define NO_SE_ENCONTRO_PARTIDA 2
 
typedef struct{
    char elemento[5][30];
    int ce;
} Inventario;

typedef struct{
    char Nombre[20];
    float Vida;
    float Cosmo;
    float Armadura;
    Inventario invent; // si el invetario es una matriz se podria hacer que cada columna corresponda a un personaje por lo que esta declaracion no haria falta
} Personaje;

/*typedef struct{ es necesario este struct o podemos reutilizar el de personaje?
    char Nombre[20];
    float Vida;
    float Cosmo;
    float Armadura;
    char Texto_batalla[100];
} Villano;*/

//struct de PRUEBA para crear y escribir un archivo
typedef struct{
    char textoNarrativo[50];
    char batalla[30];
} Capitulo;

int menu_principal();//mostrar inicio: "iniciar juego", "salir", "continuar aventura"
FILE* cargar_partida(int n);
void batalla(FILE, Personaje); //se desarrolla cada batalla
int sigue_con_vida(Personaje);
void mostrar_estado(Personaje);// mostrar vida, acciones disponibles, etc
void guardar_proceso(FILE); //?

void crear_archivo_historia();
void crear_archivo_Personajes_Principales();

void historia_principal(Personaje *Personajes);
//todo esto lo copie de lo que mando fedezawa al discord

#endif // HEADER_H_INCLUDED
