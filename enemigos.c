#include "header.h"

Enemigo cargar_enemigo_n(int n, const char *archivo)
{
    Enemigo enem;
    FILE *f = fopen(archivo, "rb");
    if (!f)
    {
        perror("No se pudo abrir archivo de enemigos");
        exit(1);
    }

    fseek(f, sizeof(Enemigo) * n, SEEK_SET); // saltar a enemigo n
    fread(&enem, sizeof(Enemigo), 1, f);
    fclose(f);
    return enem;
}

int EleccionRandomEnemigo(Enemigo *enemigo, int *opt_tec_enemigo)
{
    srand(time(NULL));
    int numAccion = -1;

    while (numAccion == -1)
    {
        numAccion = rand() % 3 + 1;

        // if (numAccion == 2)
        //  opt_tec = seleccionarTecnica(&tecnicas,cant_tec,cosmo);
        // menu que muestre la tecnicas disponibles
        // debe validar que alcance el cosmo para poder realizarla
        // si el usuario se arreepiente de elegir esta opcion , el valor de n pasa a ser -1

        // en este caso voy a elegir siempre la [0], pero lo debe hacer la funcion selecccionarTecnica();
        if (numAccion == 2)
            *opt_tec_enemigo = 0; // elijo la primer tecnica
    }

    return numAccion;
}

void EjecutarAccionEnemiga(Enemigo *enemigo, Personaje *prota, int accion, int opt_tec,int opt_oponente) {
    switch(accion) {
        case 1: // Ataque básico
            printf("\n%s ataca con un golpe basico!\n", enemigo->Nombre);
            EjecutarAccion(accion,opt_tec,enemigo, prota, opt_oponente);
            break;
        case 2: // Defensa
            printf("\n%s se defiende!\n", enemigo->Nombre);
            Defender(enemigo);
            break;
        case 3: // Técnica
            printf("\n%s usa %s!\n", enemigo->Nombre, enemigo->tecnicas[opt_tec].nombre);
            float danio = CalcularDanioTecnica(enemigo, opt_tec);
			recibeDanio(danio, prota, opt_oponente);
            break;
    }
}

