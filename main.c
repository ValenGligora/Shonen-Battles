#include "header.h"
int main()
{

    FILE *partida;
    int selec;
    DatosPartida datos;
    Personaje personaje;
    // crear_archivo_historia();                 // Archivo de prueba de historia
    // crear_archivo_Personajes_Principales()    // Archivo de prueba de personaje

    // ----------------------INICIO DE MENU Y CARGA DE JUEGO --------------------//

    selec = menu_principal(); // mostrar opciones en pantalla tales como cargar partida, nueva partida, salir del juego, (opciones?: posibilidad de poner juego en ingles? algo más?)
    if (selec == 3)
        return 0; // opcion numero 2 (Salir)

    partida = cargar_partida(selec, &datos, "Partida.dat");
    InicializarPersonaje(&personaje, &datos.pj_guardado);

    // -------------------------INICIO DE MENU DE JUEGO -----------------------//

    jugar_historia("Historia.txt", &datos, &personaje);

    // batalla(capituloN.batalla,personajes,opcion);

    // fclose(historia);
    return 0;
}
