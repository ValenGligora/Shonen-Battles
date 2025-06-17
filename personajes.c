#include "header.h"

void InicializarPersonajeVector(Personaje *p_guardado)
{
    FILE *fPersonaje = fopen("Datos_iniciales/personajes.dat", "rb");
    if (!fPersonaje) {
        printf("\nNo se pudo abrir el archivo de personajes.\n");
        exit(1);
    }

    PersonajeSerializado temp[5];

    // Leer correctamente desde archivo
    if (fread(temp, sizeof(PersonajeSerializado), 5, fPersonaje) != 5) {
        printf("\nError al leer los personajes del archivo.\n");
        fclose(fPersonaje);
        exit(1);
    }

    fclose(fPersonaje);

    for (int i = 0; i < 5; i++) {
        p_guardado[i] = temp[i].pj;

        // Copiar técnicas correctamente
        for (int t = 0; t < temp[i].pj.cant_tec; t++) {
            p_guardado[i].tecnicas[t] = temp[i].tecnicas_copia[t];
        }

        // Asignación segura de inventario
        if (p_guardado[i].cant_item <= 0)
            p_guardado[i].cant_item = 1;

        p_guardado[i].max_item = p_guardado[i].cant_item;
        p_guardado[i].invent = malloc(sizeof(Inventario) * p_guardado[i].max_item);

        if (!p_guardado[i].invent) {
            printf("Error al asignar memoria para inventario del personaje %d\n", i);
            exit(1);
        }

        for (int j = 0; j < p_guardado[i].cant_item; j++) {
            p_guardado[i].invent[j] = temp[i].invent_copia[j];
        }
}



}


void mostrarPersonaje(Personaje p)
{
    printf("\n=== %s ===\n", p.nombre);
    printf("Vida: %.1f/%.1f\n", p.vida, p.vidaMax);
    printf("Cosmo: %.1f/%.1f\n", p.cosmo, p.cosmoMax);
    printf("Ataque: %.1f\n", p.ataque);
    printf("Armadura: %.1f\n", p.armadura);
    printf("Defensa: %.1f\n", p.defensa);

    printf("\nArma: %s (%.2fx daño)\n", p.arma.nombre, p.arma.danio_porcentual);

    printf("\nTécnicas (%d):\n", p.cant_tec);
    for (int i = 0; i < p.cant_tec; i++)
    {
        printf("- %s (Daño: %.1f, Cosmo: %d)\n",
               p.tecnicas[i].nombre,
               p.tecnicas[i].ataque_tec,
               p.tecnicas[i].cosmo_necesario);
    }

    printf("\nInventario:\n");
    for (int i = 0; i < p.cant_item; i++)
    {
        if (strlen(p.invent[i].elemento) > 0)
        {
            printf("- %s (usos: %d)\n", p.invent[i].elemento, p.invent[i].usos);
        }
    }
    printf("========================\n");
}

void EjecutarAccion(int opt, int opt_tec, Personaje *personaje, Enemigo *enemigo, int eleccionOponente)
{
    float danio;
    switch (opt)
    {
    case 1:
        danio = personaje->ataque + personaje->ataque * personaje->arma.danio_porcentual;
        enemigo->vida -= recibeDanio(danio, enemigo->defensa,0,eleccionOponente);//armadura 0 los enemigos no poseen armadura solo defensa
        break;
    case 2:
        Defender(personaje, 0);// 0 es el tipo de entidad personaje
        break;
    case 3:

        danio = CalcularDanioTecnica(personaje,opt_tec,0);
        enemigo->vida -= recibeDanio(danio, enemigo->defensa, 0 , eleccionOponente);
        break;
    }
}
