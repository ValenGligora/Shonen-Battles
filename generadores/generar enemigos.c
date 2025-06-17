#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[30];
    float ataque_tec;
    int cosmo_necesario;
} Tecnica;

typedef struct {
    char Nombre[20];
    float vida;
    float vidaMax;
    float ataque;
    float cosmo;
    float cosmoMax;
    float defensa;
    Tecnica tecnicas[2];
    char Inicio_Batalla[250];
} Enemigo;

void crear_archivo_enemigos() {
    FILE *f = fopen("enemigos.dat", "wb");
    if (!f) {
        perror("Error al crear archivo enemigos.dat");
        return;
    }

    Enemigo enemigos[13];

    // 1. Aries
    strcpy(enemigos[0].Nombre, "Mu de Aries");
    enemigos[0].vida = enemigos[0].vidaMax = 100;
    enemigos[0].ataque = 18;
    enemigos[0].cosmo = enemigos[0].cosmoMax = 50;
    enemigos[0].defensa = 6;
    enemigos[0].tecnicas[0] = (Tecnica){"Muro_Cristal", 30.0f, 20};
    enemigos[0].tecnicas[1] = (Tecnica){"Extincion_Starlight", 50.0f, 40};
    strcpy(enemigos[0].Inicio_Batalla, "Mu se interpone en tu camino, su mirada es tranquila, pero poderosa...");

    // 2. Tauro
    strcpy(enemigos[1].Nombre, "Aldebarán");
    enemigos[1].vida = enemigos[1].vidaMax = 120;
    enemigos[1].ataque = 22;
    enemigos[1].cosmo = enemigos[1].cosmoMax = 40;
    enemigos[1].defensa = 10;
    enemigos[1].tecnicas[0] = (Tecnica){"Gran_Cuerno", 45.0f, 25};
    enemigos[1].tecnicas[1] = (Tecnica){"Carga_Bestial", 60.0f, 35};
    strcpy(enemigos[1].Inicio_Batalla, "¡Aldebarán ruge como un toro furioso y se lanza hacia ti!");

    // 3. Géminis
    strcpy(enemigos[2].Nombre, "Saga de Géminis");
    enemigos[2].vida = enemigos[2].vidaMax = 130;
    enemigos[2].ataque = 24;
    enemigos[2].cosmo = enemigos[2].cosmoMax = 60;
    enemigos[2].defensa = 9;
    enemigos[2].tecnicas[0] = (Tecnica){"Another_Dimension", 50.0f, 30};
    enemigos[2].tecnicas[1] = (Tecnica){"Explosión_Galaxia", 65.0f, 45};
    strcpy(enemigos[2].Inicio_Batalla, "Una energía confusa te envuelve... ¡Saga aparece con doble personalidad!");

    // 4. Cáncer
    strcpy(enemigos[3].Nombre, "Deathmask");
    enemigos[3].vida = enemigos[3].vidaMax = 110;
    enemigos[3].ataque = 21;
    enemigos[3].cosmo = enemigos[3].cosmoMax = 55;
    enemigos[3].defensa = 8;
    enemigos[3].tecnicas[0] = (Tecnica){"Ondas_Infernales", 40.0f, 25};
    enemigos[3].tecnicas[1] = (Tecnica){"Dimensión_Inframundo", 60.0f, 35};
    strcpy(enemigos[3].Inicio_Batalla, "Desde la casa de Cáncer, Deathmask sonríe con desprecio...");

    // 5. Leo
    strcpy(enemigos[4].Nombre, "Aioria");
    enemigos[4].vida = enemigos[4].vidaMax = 115;
    enemigos[4].ataque = 26;
    enemigos[4].cosmo = enemigos[4].cosmoMax = 50;
    enemigos[4].defensa = 7;
    enemigos[4].tecnicas[0] = (Tecnica){"Rayo_Plasma", 45.0f, 30};
    enemigos[4].tecnicas[1] = (Tecnica){"Relámpago_Luz", 55.0f, 40};
    strcpy(enemigos[4].Inicio_Batalla, "Aioria te desafía con honor. El león dorado no se contendrá.");

    // 6. Virgo
    strcpy(enemigos[5].Nombre, "Shaka");
    enemigos[5].vida = enemigos[5].vidaMax = 125;
    enemigos[5].ataque = 20;
    enemigos[5].cosmo = enemigos[5].cosmoMax = 70;
    enemigos[5].defensa = 10;
    enemigos[5].tecnicas[0] = (Tecnica){"Tesoro_Cielo", 55.0f, 35};
    enemigos[5].tecnicas[1] = (Tecnica){"Círculo_Seis_Sentidos", 65.0f, 45};
    strcpy(enemigos[5].Inicio_Batalla, "El caballero más cercano a los dioses abre sus ojos... ¡Shaka de Virgo!");

    // 7. Libra
    strcpy(enemigos[6].Nombre, "Dohko");
    enemigos[6].vida = enemigos[6].vidaMax = 130;
    enemigos[6].ataque = 23;
    enemigos[6].cosmo = enemigos[6].cosmoMax = 60;
    enemigos[6].defensa = 9;
    enemigos[6].tecnicas[0] = (Tecnica){"Armas_Libra", 50.0f, 30};
    enemigos[6].tecnicas[1] = (Tecnica){"Explosión_Dragon", 60.0f, 40};
    strcpy(enemigos[6].Inicio_Batalla, "El maestro de Shiryu toma su postura... ¡Dohko de Libra ataca!");

    // 8. Escorpio
    strcpy(enemigos[7].Nombre, "Milo");
    enemigos[7].vida = enemigos[7].vidaMax = 115;
    enemigos[7].ataque = 25;
    enemigos[7].cosmo = enemigos[7].cosmoMax = 55;
    enemigos[7].defensa = 7;
    enemigos[7].tecnicas[0] = (Tecnica){"Aguja_Escarlata", 45.0f, 30};
    enemigos[7].tecnicas[1] = (Tecnica){"Antares", 60.0f, 45};
    strcpy(enemigos[7].Inicio_Batalla, "Con una sonrisa letal, Milo te marca con su aguja...");

    // 9. Sagitario
    strcpy(enemigos[8].Nombre, "Aioros");
    enemigos[8].vida = enemigos[8].vidaMax = 110;
    enemigos[8].ataque = 20;
    enemigos[8].cosmo = enemigos[8].cosmoMax = 60;
    enemigos[8].defensa = 8;
    enemigos[8].tecnicas[0] = (Tecnica){"Flecha_Luz", 40.0f, 25};
    enemigos[8].tecnicas[1] = (Tecnica){"Tiro_Galáctico", 55.0f, 35};
    strcpy(enemigos[8].Inicio_Batalla, "El espíritu de Aioros aparece y prueba tu coraje...");

    // 10. Capricornio
    strcpy(enemigos[9].Nombre, "Shura");
    enemigos[9].vida = enemigos[9].vidaMax = 120;
    enemigos[9].ataque = 24;
    enemigos[9].cosmo = enemigos[9].cosmoMax = 50;
    enemigos[9].defensa = 8;
    enemigos[9].tecnicas[0] = (Tecnica){"Excalibur", 50.0f, 30};
    enemigos[9].tecnicas[1] = (Tecnica){"Corte_Divino", 60.0f, 40};
    strcpy(enemigos[9].Inicio_Batalla, "La espada de Capricornio brilla en tu contra...");

    // 11. Acuario
    strcpy(enemigos[10].Nombre, "Camus");
    enemigos[10].vida = enemigos[10].vidaMax = 120;
    enemigos[10].ataque = 22;
    enemigos[10].cosmo = enemigos[10].cosmoMax = 65;
    enemigos[10].defensa = 9;
    enemigos[10].tecnicas[0] = (Tecnica){"Polvo_Diamante", 40.0f, 25};
    enemigos[10].tecnicas[1] = (Tecnica){"Ejecución_Aurora", 65.0f, 45};
    strcpy(enemigos[10].Inicio_Batalla, "Una ola gélida invade el lugar... Camus te congela con la mirada.");

    // 12. Piscis
    strcpy(enemigos[11].Nombre, "Afrodita");
    enemigos[11].vida = enemigos[11].vidaMax = 115;
    enemigos[11].ataque = 21;
    enemigos[11].cosmo = enemigos[11].cosmoMax = 55;
    enemigos[11].defensa = 7;
    enemigos[11].tecnicas[0] = (Tecnica){"Rosa_Piraña", 45.0f, 30};
    enemigos[11].tecnicas[1] = (Tecnica){"Rosa_Sangrienta", 60.0f, 40};
    strcpy(enemigos[11].Inicio_Batalla, "Afrodita lanza una rosa venenosa con elegante crueldad...");

    // 13. Enemigo final: El Patriarca
    strcpy(enemigos[12].Nombre, "Patriarca");
    enemigos[12].vida = enemigos[12].vidaMax = 250;
    enemigos[12].ataque = 28;
    enemigos[12].cosmo = enemigos[12].cosmoMax = 100;
    enemigos[12].defensa = 12;
    enemigos[12].tecnicas[0] = (Tecnica){"Golpe_Temporal", 50.0f, 35};
    enemigos[12].tecnicas[1] = (Tecnica){"Explosión_Sagrada", 80.0f, 50};
    strcpy(enemigos[12].Inicio_Batalla,
           "La figura del Patriarca se revela en lo alto del santuario... Su poder es abrumador. ¡Es la batalla final!");


    int cantidad_enemigos = 13;
    fwrite(enemigos, sizeof(Enemigo), cantidad_enemigos, f);
    fclose(f);

    printf("✅ Archivo enemigos.dat generado correctamente con %d enemigos.\n", cantidad_enemigos);
}

int main() {
    crear_archivo_enemigos();
    return 0;
}
