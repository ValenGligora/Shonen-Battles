#include "header.h"

void InicializarPersonajeVector(Personaje *p_guardado)
{
    FILE* fPersonaje = fopen("Datos_iniciales/personajes.dat","rb");
    if(!fPersonaje)
    {
        printf("\nNo se pudo abrir el archivo de personajes");
        return;
    }

    fread(p_guardado,sizeof(Personaje),5,fPersonaje);
    fclose(fPersonaje);

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

void EjecutarAccion(int opt, int opt_tec, Personaje *emisor, Personaje *receptor, int eleccionOponente)
{
    float danio;
    switch (opt)
    {
    case 1:
        danio = CalcularAtaque(emisor);
        recibeDanio(danio, receptor, eleccionOponente);
        break;
    case 2:
        printf("\n%s está a la defensiva", emisor->nombre);

        break;
    case 3:

        danio = CalcularDanioTecnica(emisor,opt_tec);
        recibeDanio(danio, receptor, eleccionOponente);
        break;
    }
}
