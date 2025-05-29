#include "header.h"

int ejecutar_batalla(Personaje *prota, Personaje *enemigo) {
    int opcion, opt_tec, opt_obj, opt_tec_enemigo, eleccionEnemigo;

    while (1) {
		prota->defensa = 0;
		enemigo->defensa = 0;
        system("cls || clear");

        // Mostrar estado de los combatientes hay que fixear las lineas
        printf("============================================\n");
        printf("| %-20s VS %-20s |\n", prota->nombre, enemigo->nombre);
        printf("| Vida: %-4.0f/%-4.0f    Vida: %-4.0f/%-4.0f |\n",
               prota->vida, prota->vidaMax, enemigo->vida, enemigo->vidaMax);
        printf("| Cosmo: %-3.0f/%-3.0f   Cosmo: %-3.0f/%-3.0f |\n",
               prota->cosmo, prota->cosmoMax, enemigo->cosmo, enemigo->cosmoMax);
        printf("============================================\n\n");

        // Menú de opciones
        printf("1. Atacar con %s\n", prota->arma.nombre);
        printf("2. Defenderse\n");
        printf("3. Usar tecnica (%d disponibles)\n", prota->cant_tec);
        printf("4. Usar objeto\n");
        printf("5. Huir\n");
        printf("\nElija opcion (1-5): ");

        opcion = validarIntRango(1, 5);

        // Turno del jugador
        switch(opcion) {
            case 1: // Ataque básico
                printf("\n%s ataca con %s!\n", prota->nombre, prota->arma.nombre);
                EjecutarAccion(1, 0, prota, enemigo, 0);
                break;

            case 2: // Defensa
                printf("\n%s se prepara para defender!\n", prota->nombre);
                EjecutarAccion(2, 0, prota, enemigo, 0);
                break;

            case 3: // Técnicas
                if (prota->cant_tec == 0) {
                    printf("\nNo tienes tecnicas disponibles!\n");
                    system("pause");
                    continue;
                }

                printf("\nTecnicas disponibles:\n");
                for (int i = 0; i < prota->cant_tec; i++) {
                    printf("%d. %s (%.1f ATQ, %d Cosmo)\n",
                          i+1, prota->tecnicas[i].nombre,
                          prota->tecnicas[i].ataque_tec,
                          prota->tecnicas[i].cosmo_necesario);
                }
                printf("\nElija tecnica (1-%d): ", prota->cant_tec);

                opt_tec = validarIntRango(1, prota->cant_tec) - 1;

                if (prota->cosmo < prota->tecnicas[opt_tec].cosmo_necesario) {
                    printf("\n¡Cosmo insuficiente! Necesitas %d\n", prota->tecnicas[opt_tec].cosmo_necesario);
                    system("pause");
                    continue;
                }

                printf("\n%s usa %s!\n", prota->nombre, prota->tecnicas[opt_tec].nombre);
                EjecutarAccion(3, opt_tec, prota, enemigo, 0);
                break;

            case 4: // Objetos
                MostrarInventario(prota);
                if (InventarioVacio(prota)) {
                    system("pause");
                    continue;
                }

                printf("\nElija objeto (1-%d) o 0 para cancelar: ",prota->cant_item);
                opt_obj = validarIntRango(0, prota->cant_item);
                if (opt_obj == 0) continue;

                UsarObjeto(prota, opt_obj - 1);
                break;

            case 5: // Huir
                if (INTENTAR_HUIR()) {
                    printf("\n¡Has escapado de la batalla!\n");
                    return -1;
                }
                printf("\n¡La huida ha fallado!\n");
                break;
        }

        // Verificar si el enemigo fue derrotado
        if (enemigo->vida <= 0) {
            printf("\n¡%s ha sido derrotado!\n", enemigo->nombre);
            return 1;
        }

        // Turno del enemigo
        eleccionEnemigo = EleccionRandomEnemigo(enemigo, &opt_tec_enemigo);
        EjecutarAccionEnemiga(enemigo, prota, eleccionEnemigo, opt_tec_enemigo,opcion);

        // Verificar si el jugador fue derrotado
        if (prota->vida <= 0) {
            printf("\n¡Has sido derrotado!\n");
            return 0;
        }


        system("pause");
    }
}

void UsarObjeto(Personaje *p, int obj_index) {
    if (obj_index < 0 || obj_index >= 3) return;

    printf("\n%s usa %s!\n", p->nombre, p->invent[obj_index].elemento);

    // Efectos según tipo de objeto (debes implementar esta lógica)
    if (strstr(p->invent[obj_index].elemento, "Cura") != NULL) {
        p->vida += 50;
        if (p->vida > p->vidaMax) p->vida = p->vidaMax;
        printf("¡Restauradas 50 puntos de vida!\n");
    }
    else if (strstr(p->invent[obj_index].elemento, "Cosmo") != NULL) {
        p->cosmo += 30;
        if (p->cosmo > p->cosmoMax) p->cosmo = p->cosmoMax;
        printf("¡Restaurados 30 puntos de cosmo!\n");
    }

    p->invent[obj_index].usos--;
    if (p->invent[obj_index].usos <= 0) {
        memset(p->invent[obj_index].elemento, 0, 30); // Eliminar objeto si no quedan usos
    }
}

float CalcularAtaque(Personaje *p)
{
    float ataqueCalculado;

    ataqueCalculado = p->ataque + p->ataque * p->arma.danio_porcentual;
    return ataqueCalculado;
}

float CalcularDanioTecnica(Personaje *p, int num_tec) {
    Tecnica *tec = &p->tecnicas[num_tec];

    // Daño base con arma
    float danio_base = p->ataque + (p->ataque * p->arma.danio_porcentual);

    // Daño final modificado por la técnica (asumimos ataque_tec como multiplicador)
    float danio_final = danio_base * (tec->ataque_tec/100);

    // Consumir cosmo
    p->cosmo -= tec->cosmo_necesario;

    return danio_final;
}

void recibeDanio(float danio, Personaje *p, int eleccion)
{
    float defensa;
    if (eleccion == 2)
        defensa = p->defensa;
    else
        defensa = 0;

    float danioInfligido = danio - danio * (p->armadura/100) - danio * (defensa/100);

    p->vida -= danioInfligido;
}

void Defender(Personaje *p) {
    // Aumentar la defensa temporalmente (se resetea al final del turno en ejecutar_batalla)
    p->defensa = p->armadura * 1.5f;  // Aumento del 50% en la defensa

    // También regenera un pequeño porcentaje de cosmo
    float cosmoRegenerado = p->cosmoMax * 0.1f;  // 10% del cosmo máximo
    p->cosmo += cosmoRegenerado;
    if (p->cosmo > p->cosmoMax) {
        p->cosmo = p->cosmoMax;
    }

    printf("%s adopta una postura defensiva! (+%.f defensa, +%.f cosmo)\n",
           p->nombre, p->armadura * 0.5f, cosmoRegenerado);
}
