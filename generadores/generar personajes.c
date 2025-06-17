#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char elemento[30];
    int usos;
} Inventario;

typedef struct {
    char nombre[30];
    float danio_porcentual;
} Arma;

typedef struct {
    char nombre[30];
    float ataque_tec;
    int cosmo_necesario;
} Tecnica;

typedef struct {
    char nombre[20];
    float vida;
    float vidaMax;
    float ataque;
    float cosmo;
    float cosmoMax;
    float armadura;
    float defensa;
    Arma arma;
    Tecnica tecnicas[3];
    int cant_tec;
    Inventario *invent;   // ← memoria dinámica
    int cant_item;
    int max_item;
} Personaje;

typedef struct {
    Personaje pj;
    Inventario invent_copia[10]; // ← copia del inventario para serializar
} PersonajeSerializado;

void crear_archivo_personajes() {
    FILE *f = fopen("personajes.dat", "wb");
    if (!f) {
        perror("Error al crear personajes.dat");
        return;
    }

    Personaje personajes[5] = {0};

    // SEIYA
    strcpy(personajes[0].nombre, "Seiya");
    personajes[0].vida = personajes[0].vidaMax = 100;
    personajes[0].cosmo = personajes[0].cosmoMax = 60;
    personajes[0].ataque = 20;
    personajes[0].armadura = 10;
    personajes[0].defensa = 5;
    strcpy(personajes[0].arma.nombre, "Puño Meteoro");
    personajes[0].arma.danio_porcentual = 0.2f;
    personajes[0].cant_tec = 3;
    personajes[0].tecnicas[0] = (Tecnica){"Meteoro_Pegaso", 25.0f, 20};
    personajes[0].tecnicas[1] = (Tecnica){"Cometa_Pegaso", 40.0f, 30};
    personajes[0].tecnicas[2] = (Tecnica){"Voluntad_Atenea", 60.0f, 40};
    personajes[0].cant_item = personajes[0].max_item = 1;
    personajes[0].invent = malloc(sizeof(Inventario));
    personajes[0].invent[0] = (Inventario){"Pocion de vida", 1};

    // SHIRYU
    strcpy(personajes[1].nombre, "Shiryu");
    personajes[1].vida = personajes[1].vidaMax = 120;
    personajes[1].cosmo = personajes[1].cosmoMax = 70;
    personajes[1].ataque = 18;
    personajes[1].armadura = 15;
    personajes[1].defensa = 6;
    strcpy(personajes[1].arma.nombre, "Excalibur");
    personajes[1].arma.danio_porcentual = 0.25f;
    personajes[1].cant_tec = 3;
    personajes[1].tecnicas[0] = (Tecnica){"Colera_Dragon", 35.0f, 30};
    personajes[1].tecnicas[1] = (Tecnica){"Ultimo_Dragon", 50.0f, 40};
    personajes[1].tecnicas[2] = (Tecnica){"Escudo_Libra", 70.0f, 50};
    personajes[1].cant_item = personajes[1].max_item = 1;
    personajes[1].invent = malloc(sizeof(Inventario));
    personajes[1].invent[0] = (Inventario){"Pocion de vida", 1};

    // HYOGA
    strcpy(personajes[2].nombre, "Hyoga");
    personajes[2].vida = personajes[2].vidaMax = 95;
    personajes[2].cosmo = personajes[2].cosmoMax = 65;
    personajes[2].ataque = 22;
    personajes[2].armadura = 8;
    personajes[2].defensa = 5;
    strcpy(personajes[2].arma.nombre, "Polvo Diamante");
    personajes[2].arma.danio_porcentual = 0.2f;
    personajes[2].cant_tec = 3;
    personajes[2].tecnicas[0] = (Tecnica){"Polvo_Diamante", 20.0f, 25};
    personajes[2].tecnicas[1] = (Tecnica){"Ejecucion_Aurora", 60.0f, 50};
    personajes[2].tecnicas[2] = (Tecnica){"Muro_Hielo", 75.0f, 60};
    personajes[2].cant_item = personajes[2].max_item = 1;
    personajes[2].invent = malloc(sizeof(Inventario));
    personajes[2].invent[0] = (Inventario){"Pocion de cosmo", 1};

    // SHUN
    strcpy(personajes[3].nombre, "Shun");
    personajes[3].vida = personajes[3].vidaMax = 90;
    personajes[3].cosmo = personajes[3].cosmoMax = 75;
    personajes[3].ataque = 17;
    personajes[3].armadura = 12;
    personajes[3].defensa = 7;
    strcpy(personajes[3].arma.nombre, "Cadena Andromeda");
    personajes[3].arma.danio_porcentual = 0.18f;
    personajes[3].cant_tec = 3;
    personajes[3].tecnicas[0] = (Tecnica){"Cadena_Nebular", 15.0f, 20};
    personajes[3].tecnicas[1] = (Tecnica){"Tormenta_Nebular", 40.0f, 45};
    personajes[3].tecnicas[2] = (Tecnica){"Defensa_Absoluta", 50.0f, 60};
    personajes[3].cant_item = personajes[3].max_item = 1;
    personajes[3].invent = malloc(sizeof(Inventario));
    personajes[3].invent[0] = (Inventario){"Pocion de vida", 1};

    // IKKI
    strcpy(personajes[4].nombre, "Ikki");
    personajes[4].vida = personajes[4].vidaMax = 110;
    personajes[4].cosmo = personajes[4].cosmoMax = 60;
    personajes[4].ataque = 25;
    personajes[4].armadura = 10;
    personajes[4].defensa = 4;
    strcpy(personajes[4].arma.nombre, "Ave Fenix");
    personajes[4].arma.danio_porcentual = 0.3f;
    personajes[4].cant_tec = 3;
    personajes[4].tecnicas[0] = (Tecnica){"Ilusion_Demoniaca", 40.0f, 30};
    personajes[4].tecnicas[1] = (Tecnica){"Ave_Fenix", 55.0f, 40};
    personajes[4].tecnicas[2] = (Tecnica){"Renacer", 60.0f, 60};
    personajes[4].cant_item = personajes[4].max_item = 1;
    personajes[4].invent = malloc(sizeof(Inventario));
    personajes[4].invent[0] = (Inventario){"Pocion de cosmo", 1};

    // Serializar
    PersonajeSerializado serializados[5];
    for (int i = 0; i < 5; i++) {
        serializados[i].pj = personajes[i];
        for (int j = 0; j < personajes[i].cant_item; j++) {
            serializados[i].invent_copia[j] = personajes[i].invent[j];
        }
        free(personajes[i].invent);
    }

    fwrite(serializados, sizeof(PersonajeSerializado), 5, f);
    fclose(f);
    printf("Archivo personajes.dat creado correctamente.\n");
}

int main() {
    crear_archivo_personajes();

    // Leer desde archivo
    FILE *f = fopen("personajes.dat", "rb");
    if (!f) {
        perror("No se pudo abrir personajes.dat");
        return 1;
    }

    PersonajeSerializado serializados[5];
    fread(serializados, sizeof(PersonajeSerializado), 5, f);
    fclose(f);

    // Restaurar estructura dinámica
    Personaje personajes[5];
    for (int i = 0; i < 5; i++) {
        personajes[i] = serializados[i].pj;
        personajes[i].invent = malloc(sizeof(Inventario) * personajes[i].cant_item);
        for (int j = 0; j < personajes[i].cant_item; j++) {
            personajes[i].invent[j] = serializados[i].invent_copia[j];
        }
    }

    // Mostrar
    printf("\n Personajes cargados:\n");
    for (int i = 0; i < 5; i++) {
        printf("- %s tiene %d item(s). Ej: %s (usos: %d)\n",
               personajes[i].nombre,
               personajes[i].cant_item,
               personajes[i].invent[0].elemento,
               personajes[i].invent[0].usos);
        free(personajes[i].invent);
    }

    return 0;
}

