#include "header.h"
#include "funciones.c"

int main(){

    FILE* juego;
    int selec;

    //crear_archivo_historia();                 // Archivo de prueba de historia
    //crear_archivo_Personajes_Principales()    // Archivo de prueba de personaje

    // ----------------------INICIO DE MENU Y CARGA DE JUEGO --------------------//

    selec = menu_principal();//mostrar opciones en pantalla tales como cargar partida, nueva partida, salir del juego, (opciones?: posibilidad de poner juego en ingles? algo más?)
    if(selec == 3) 
        return 0; // opcion numero 2 (Salir)
    
    juego = cargar_partida(selec);

    // -------------------------INICIO DE MENU DE JUEGO -----------------------//
    
    historia_principal(juego);
    

    return 0;
}


