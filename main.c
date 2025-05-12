#include "header.h"
int main()
{

    FILE *partida;
    int selec;
    DatosPartida datos;
    Personaje personaje;

    // ----------------------INICIO DE MENU Y CARGA DE JUEGO --------------------//

    selec = menu_principal(); // mostrar opciones en pantalla tales como cargar partida, nueva partida, salir del juego, (opciones?: posibilidad de poner juego en ingles? algo más?)
    if (selec == 3)
        return 0;

    partida = cargar_partida(selec, &datos, "Partida.dat");
    printf("\n DEBUG PASO CARGA DE PARTIDA");
    InicializarPersonaje(&personaje, &datos.pj_guardado);
    printf("\n DEBUG PASO INICIALIZAR PERSONAJE");
    // -------------------------INICIO DE MENU DE JUEGO -----------------------//

    jugar_historia("Texto-historia/0_intro_saga_santuario.txt",&datos,"enemigos_santuario.dat");
    printf("\n DEBUG PASO JUGAR HISTORIA");
    // batalla(capituloN.batalla,personajes,opcion);

    // fclose(historia);
    return 0;
}
