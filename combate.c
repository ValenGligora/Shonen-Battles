#include "header.h"


void mostrarEstadoCombatientes(const Personaje* prota,const Enemigo* enemigo)
{
    // Mostrar estado de los combatientes hay que fixear las lineas
    printf("============================================\n");
    printf("| %-20s VS %-20s |\n", prota->nombre, enemigo->Nombre);
    //printf("| Vida: %-4.0f/%-4.0f    Vida: %-4.0f/%-4.0f |\n",prota->vida, prota->vidaMax, enemigo->vida, enemigo->vidaMax);
    printf("| Cosmo: %-3.0f/%-3.0f   Cosmo: %-3.0f/%-3.0f |\n",
            prota->cosmo, prota->cosmoMax, enemigo->cosmo, enemigo->cosmoMax);
    printf("============================================\n\n");

    //Barra de vida protagonista
    int vidapromPersonaje = (prota->vida/prota->vidaMax)*10;
    int vidapromEnemigo = (enemigo->vida/enemigo->vidaMax)*10;

    printf("Vida de %s\t\tVida de %s\n",prota->nombre,enemigo->Nombre);

    if(vidapromPersonaje > 7)    establecer_color_texto(2);
    else if(vidapromPersonaje > 3) establecer_color_texto(6);
    else    establecer_color_texto(4);

    for(int i = 0; i < 10; i++)
    {
        if(i<vidapromPersonaje)  printf("█");
        else    printf(".");
    }

    establecer_color_texto(7); // Restaurar color

    printf(" %.0f/%.0f",prota->vida, prota->vidaMax);
    printf("\t");

    if(vidapromEnemigo > 7)    establecer_color_texto(2);
    else if(vidapromEnemigo > 3) establecer_color_texto(6);
    else    establecer_color_texto(4);

    for(int i = 0; i < 10; i++)
    {
        if(i<vidapromEnemigo)  printf("█");
        else    printf(".");
    }

    establecer_color_texto(7); // Restaurar color

    printf(" %.0f/%.0f",enemigo->vida, enemigo->vidaMax);
    printf("\t");
}
int mostrar_menu_acciones(const Personaje *prota)
{
        // Menú de opciones
        printf("1. Atacar con %s\n", prota->arma.nombre);
        printf("2. Defenderse\n");
        printf("3. Usar tecnica (%d disponibles)\n", prota->cant_tec);
        printf("4. Usar objeto\n");
        printf("5. Huir\n");
        printf("\nElija opcion (1-5): ");
        return validarIntRango(1, 5);
}

int ejecutar_batalla(Personaje *prota, Enemigo *enemigo) {
    int opcion, opt_tec, opt_obj, opt_tec_enemigo, eleccionEnemigo;

    while (1) {
		prota->defensa = 0;
		enemigo->defensa = 0;
        system("cls || clear");

        mostrarEstadoCombatientes(prota,enemigo);
        putchar('\n');
        opcion = mostrar_menu_acciones;

        eleccionEnemigo = EleccionRandomEnemigo(enemigo, &opt_tec_enemigo);
        if(eleccionEnemigo == 2)
            EjecutarAccionEnemiga(enemigo, prota, eleccionEnemigo, opt_tec_enemigo,opcion);

        // Turno del jugador
        switch(opcion) {
            case 1: // Ataque básico
                printf("\n%s ataca con %s!\n", prota->nombre, prota->arma.nombre);
                EjecutarAccion(1, 0, prota, enemigo, 0);
                break;
            case 2: // Defensa
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
                          i + 1, prota->tecnicas[i].nombre,
                          prota->tecnicas[i].ataque_tec,
                          prota->tecnicas[i].cosmo_necesario);
                }

                // Agregar opción para volver
                printf("0. Volver\n");
                printf("\nElija tecnica (0-%d): ", prota->cant_tec);
                opt_tec = validarIntRango(0, prota->cant_tec) - 1;

                // Si eligió volver
                if (opt_tec == -1) {
                    printf("\nVolviendo al menú...\n");
                    system("pause");
                    continue;
                }

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
                    return HUYE;//-1
                }
                printf("\n¡La huida ha fallado!\n");
                break;
        }

        // Verificar si el enemigo fue derrotado
        if (enemigo->vida <= 0) {
            system("cls");
            printf("\n¡%s ha sido derrotado!\n", enemigo->Nombre);
            RecibirRecompensa(prota);
            return GANA;//1
        }

        // Accion enemigo (atacar,tecnica)
        if(opcion!=4 && eleccionEnemigo != 2){

            //eleccionEnemigo = EleccionRandomEnemigo(enemigo, &opt_tec_enemigo); lo saco y lo pongo al inicio del turno por si elige defenderse
            EjecutarAccionEnemiga(enemigo, prota, eleccionEnemigo, opt_tec_enemigo,opcion);
        }

        // Verificar si el jugador fue derrotado
        if (prota->vida <= 0) {
            system("cls");
            printf("\n¡Has sido derrotado!\n");
            Sleep(500);
            return DERROTADO; //0
        }
        system("pause");
    }
}

void UsarObjeto(Personaje *p, int obj_index) {
    if (obj_index < 0 || obj_index >= 3) return;

    printf("\n%s usa %s!\n", p->nombre, p->invent[obj_index].elemento);

    // Efectos según tipo de objeto (debes implementar esta lógica)
    if (strstr(p->invent[obj_index].elemento, "Pocion de vida") != NULL) {
        p->vida += 50;
        if (p->vida > p->vidaMax) p->vida = p->vidaMax;
        printf("¡Restaurados 50 puntos de vida!\n");
    }
    else if (strstr(p->invent[obj_index].elemento, "Pocion de cosmo") != NULL) {
        p->cosmo += 30;
        if (p->cosmo > p->cosmoMax) p->cosmo = p->cosmoMax;
        printf("¡Restaurados 30 puntos de cosmo!\n");
    }

    p->invent[obj_index].usos--;

    if (p->invent[obj_index].usos <= 0) {
        printf("%s se ha agotado.\n", p->invent[obj_index].elemento);
        for (int i = obj_index; i < p->cant_item - 1; i++) {
            p->invent[i] = p->invent[i + 1];
        }
        p->cant_item--;
    }
}

float CalcularDanioTecnica(void *entidad, int num_tec, int tipo_entidad) {
    //la tecnica es flat damage
    Tecnica *tec;
    Personaje* p;
    Enemigo* e;

    float danio_final;
    switch (tipo_entidad)
    {
    case 0: //Personaje
        // Consumir cosmo
        p = (Personaje*)entidad;
        tec = &p->tecnicas[num_tec];
        danio_final = tec->ataque_tec;
        p->cosmo -= tec->cosmo_necesario;

        break;
    case 1: //Enemigo
        // Consumir cosmo
        e = (Enemigo*)entidad;
        tec = &e->tecnicas[num_tec];
        danio_final = tec->ataque_tec;
        e->cosmo -= tec->cosmo_necesario;
        break;
    default:
        break;
    }
    return danio_final;
}

float recibeDanio(float danio, float defensaBase, float armadura,int eleccion)
{
    float defensa;
    if (eleccion == 2)
        defensa = defensaBase;
    else
        defensa = 0;

    float danioInfligido = danio - danio * (armadura/100) - danio * (defensa/100);

    return danioInfligido;
}

void Defender(void* entidad, int tipo_entidad) {
    //Se castea entidad al tipo de dato que es
    float cosmoRegenerado;
    Personaje* p;
    Enemigo* e ;

    switch (tipo_entidad)
    {
    case 0: //personaje
        p = (Personaje *)entidad;
        p->defensa += p->armadura * 0.5f;

        cosmoRegenerado = p->cosmoMax * 0.20f;  // 20% del cosmo máximo

        printf("\n%s aumentó su defensa!\n",p->nombre);


        p->cosmo += cosmoRegenerado;
        if (p->cosmo > p->cosmoMax)
            {
                p->cosmo = p->cosmoMax;
            }
            else    printf("Regeneró %.f cosmo\n",cosmoRegenerado);

        break;
    case 1: //enemigo
        e = (Enemigo *)entidad;
        e->defensa += e->defensa  * 0.5f;

        cosmoRegenerado = e->cosmoMax * 0.1f;  // 10% del cosmo máximo

        printf("\n%s aumentó su defensa!\n",e->Nombre);

        e->cosmo += cosmoRegenerado;
        if (e->cosmo > e->cosmoMax) {
            e->cosmo = e->cosmoMax;
        }
        else    printf("Regeneró %.f cosmo\n",cosmoRegenerado);

        break;
    default:
        break;
    }
    // Aumentar la defensa temporalmente (se resetea al final del turno en ejecutar_batalla)

}

void RecibirRecompensa(Personaje *p){
    int i;
    Inventario invent;


    int tipo = rand() % 2;

    switch(tipo){
        case 0:
            strcpy(invent.elemento,"Pocion de vida");
            break;
        case 1:
            strcpy(invent.elemento,"Pocion de cosmo");
    }
    //ya tiene de ese tipo de objeto, se le adiciona un uso
    for(i=0;i<5;i++){
        if(strcmp(p->invent[i].elemento, invent.elemento) == 0){
            p->invent[i].usos++;
            printf("\n¡Has recibido un objeto! Se agregó una %s a tu inventario.\n", invent.elemento);
            return;
        }
    }

    // Si no existe y hay que agregar
    if (p->cant_item == p->max_item) {
        p->max_item += 2; // aumentar capacidad
        p->invent = realloc(p->invent, sizeof(Inventario) * p->max_item);
        if (!p->invent) {
            printf(" Error de memoria al expandir inventario.\n");
            exit(1);
        }
    }

    invent.usos = 1;
    p->invent[p->cant_item] = invent;
    p->cant_item++;
    printf("\n¡Has recibido un objeto! Se agregó una %s a tu inventario.\n", invent.elemento);
}


void ActualizarInventario(Personaje *perOriginal, Personaje *perBatalla){
    int i;
    if (perBatalla->cant_item > perOriginal->max_item) {
        perOriginal->max_item = perBatalla->cant_item;
        perOriginal->invent = realloc(perOriginal->invent, sizeof(Inventario) * perOriginal->max_item);

        if (!perOriginal->invent) {
            printf("Error de memoria al sincronizar inventario.\n");
            exit(1);
        }
    }

    perOriginal->cant_item = perBatalla->cant_item;
    for (i = 0; i < perOriginal->cant_item; i++) {
        perOriginal->invent[i] = perBatalla->invent[i];
    }
}



