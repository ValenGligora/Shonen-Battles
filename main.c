#include "header.h"
#include <locale.h>
#include <windows.h>
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int selec;
    DatosPartida datos_actuales; //SI HAY PARTIDA SON LOS DATOS DE PROGRESO, SI NO HAY PARTIDA SE TIENEN LOS DATOS INICIALES Y SE GUARDA HASTA DONDE SE LLEGO

    setlocale(LC_ALL, "es_ES.UTF-8");

    // ----------------------INICIO DE MENU Y CARGA DE JUEGO --------------------//

    selec = menu_principal(); // mostrar opciones en pantalla tales como cargar partida, nueva partida, salir del juego, (opciones?: posibilidad de poner juego en ingles? algo más?)
    if (selec == 3)
        return 0;

    cargar_partida(selec, &datos_actuales, "Partida.dat");
    if(selec == 2)
    {
        InicializarPersonajeVector(datos_actuales.pj_guardado);
        puts("empezando a mostar");
        for (int i = 0; i < 4; i++) {
        mostrarPersonaje(datos_actuales.pj_guardado[i]);
        }
    }

    // -------------------------INICIO DE MENU DE JUEGO -----------------------//

    puts("antes de entrar a jugar");
    jugar_historia("Texto historia/historia.txt",&datos_actuales,"Datos_iniciales/enemigos.dat");

    // fclose(historia);
    return 0;
}
