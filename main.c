#include "header.h"
#include <locale.h>
#include <windows.h>
int main()
{
    srand((unsigned int)time(NULL)); // Solo una vez al comienzo del juego

    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "es_ES.UTF-8");

    int selec;
    DatosPartida datos_actuales; //SI HAY PARTIDA SON LOS DATOS DE PROGRESO, SI NO HAY PARTIDA SE TIENEN LOS DATOS INICIALES Y SE GUARDA HASTA DONDE SE LLEGO

    // ----------------------INICIO DE MENU Y CARGA DE JUEGO --------------------//

    selec = menu_principal(); // mostrar opciones en pantalla tales como cargar partida, nueva partida, salir del juego, (opciones?: posibilidad de poner juego en ingles? ; guardar mas de un archivo de partida algo más?)
    if (selec == 3)
        return 0;

    cargar_partida(selec, &datos_actuales, "Guardado/Partida.dat");
    if(selec == 2)
    {
        datos_actuales.posicion_historia=0;
        datos_actuales.num_batalla=0;
        //reiniciar momento de la historia y la batalla
        InicializarPersonajeVector(datos_actuales.pj_guardado);
    }

    // -------------------------INICIO DE MENU DE JUEGO -----------------------//

    //puts("antes de entrar a jugar");
    jugar_historia("Texto historia/historia.txt",&datos_actuales,"Datos_iniciales/enemigos.dat");

    //liberar memoria dinamica
    for (int i = 0; i < 5; i++) {
    free(datos_actuales.pj_guardado[i].invent);
}

    // fclose(historia);
    return 0;
}
