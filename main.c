#include "header.h"
#include <locale.h>
#include <windows.h>
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int selec;
    DatosPartida datos;
    Personaje personaje;

    setlocale(LC_ALL, "es_ES.UTF-8");
    // ----------------------INICIO DE MENU Y CARGA DE JUEGO --------------------//

    selec = menu_principal(); // mostrar opciones en pantalla tales como cargar partida, nueva partida, salir del juego, (opciones?: posibilidad de poner juego en ingles? algo más?)
    if (selec == 3)
        return 0;

    cargar_partida(selec, &datos, "Partida.dat");
    InicializarPersonaje(&personaje, &datos.pj_guardado,selec);
    // -------------------------INICIO DE MENU DE JUEGO -----------------------//

    printf("%s,", personaje.nombre);
    printf("%s",personaje.arma.nombre);
    mostrar_personajes_disponibles("protagonistas_saga.dat");

    printf("a");
    Sleep(10000);
    jugar_historia("Texto-historia/0_intro_saga_santuario.txt",&datos,"enemigos_santuario.dat");
    // batalla(capituloN.batalla,personajes,opcion);

    // fclose(historia);
    return 0;
}
