

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

// Elige acción aleatoria válida para el enemigo
int EleccionRandomEnemigo(Enemigo *enemigo, int *opt_tec_enemigo)
{
    int accion_valida = 0;
    int intento = 0;

    while (!accion_valida && intento < 10)
    {
        int numAccion = rand() % 3 + 1; // 1 = ataque, 2 = defensa, 3 = técnica
        intento++;

        if (numAccion == 3)
        {
            // Verificar si alguna técnica es utilizable
            for (int i = 0; i < 2; i++)
            {
                if (strlen(enemigo->tecnicas[i].nombre) > 0 &&
                    enemigo->cosmo >= enemigo->tecnicas[i].cosmo_necesario)
                {
                    *opt_tec_enemigo = i;
                    return 3;
                }
            }
            // No tiene cosmo suficiente para ninguna técnica, reintenta
        }
        else
        {
            return numAccion; // 1 o 2
        }
    }

    // Si no se encontró ninguna acción válida después de varios intentos, se defiende por defecto
    return 2;
}

void EjecutarAccionEnemiga(Enemigo *enemigo, Personaje *prota, int accion, int opt_tec, int opt_oponente)
{
    switch (accion)
    {
    case 1: // Ataque básico
        printf("\n%s ataca con un golpe básico!\n", enemigo->Nombre);
        EjecutarAccion(1, 0, enemigo, prota, opt_oponente);
        break;

    case 2: // Defensa
        printf("\n%s se defiende!\n", enemigo->Nombre);
        Defender(enemigo);
        break;

    case 3: {
        if (enemigo->cosmo >= enemigo->tecnicas[opt_tec].cosmo_necesario)
        {
            printf("\n%s usa %s!\n", enemigo->Nombre, enemigo->tecnicas[opt_tec].nombre);
            float danio = CalcularDanioTecnicaEnemigo(enemigo, opt_tec);
            recibeDanio(danio, prota, opt_oponente);
        }
        else
        {
            printf("\n%s intentó usar una técnica pero no tenía suficiente cosmo.\n", enemigo->Nombre);
            printf("%s se pone a la defensiva.\n", enemigo->Nombre);
            Defender(enemigo);
        }
        break;
            }
    }



}
