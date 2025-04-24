#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct{
    char elemento[5][30];
    int ce;
} Inventario;

typedef struct{
    char nombre[30];
    float danio_porcentual;
} Arma;

typedef struct
{
	char nombre[30];
	float ataque_tec;
	int cosmo_necesario;

} Tecnica; // estaría interesante hacer un tda que reserve espacio según la cantidad de habilidad que tenga el personaje, sino pongo como maximo 3 tecnicas

typedef struct
{
    char Nombre[20];
    float Vida;
    float ataque;
    float Cosmo;
    float Armadura;
    float defensa;
    Arma arma;
    Tecnica tecnicas[5];
    int cant_tec;
    //Inventario invent;
} Personaje;

void InicializarPersonaje(Personaje *); // el siguiente parametro seria el nombre del archivo con los atributos del personaje
void InicializarPersonaje2(Personaje *);
int TurnosBatalla(Personaje *prota,Personaje *enemigo,int *resultado);

int ValidarEleccion(int,int,int,int *,Tecnica tecnicas[],float cosmo);
int validarIntRango(int,int);
int EleccionRandomEnemigo(Personaje* enemigo,int *opt_tec_enemigo);

void EjecutarAccion(int ,int,Personaje *,Personaje *,int );
float CalcularAtaque(Personaje *prota);
float CalcularAtaqueTecnica(Personaje *p,int num_tec);
void recibeDanio(float danio,Personaje *p,int eleccion);


int main()
{
	Personaje prota;
	Personaje enemigo;


	InicializarPersonaje(&prota); // Esto leeria de mi archivo binario con los atributos de mi personaje y despues para los atributos del enemigo
	InicializarPersonaje2(&enemigo);

	int continua =1;
	int resultado;// resultado vendria como parametro de la funcion iniciarPelea()

	resultado = TurnosBatalla(&prota,&enemigo,&resultado);
	//return resultado;  entonces este main formaria parte de la funcion ComenzarBatalla() y devoleria el resultado
						//En el main del proyecto es donde se decide que hacer con el resultado, comenzar de nuevo, finalizar ,etc, (conforma parte de la interfaz de juego y estructura general del proyecto)
}

void InicializarPersonaje(Personaje *p)
{
	char nombre[]="Seiya";
	float healt =100;
	float attack =15;
	float cosmo =150;
	float arm =0.3;
	float defense = 0.2;

	char name_weapon[] = "Tridente de poseidon";
	float damage_weapon= 0.4;

	char nombre_tec[] = "Estrella de la muerte";
	float danio_tec = 30;
	int cosmo_nec = 60;
	int cant_tec = 1;



	strcpy(p->Nombre,nombre);
	p->Vida = healt;
	p->ataque = attack;
	p->Cosmo = cosmo;
	p->Armadura = arm;
	p->defensa = defense;
	strcpy(p->arma.nombre,name_weapon);
	p->arma.danio_porcentual = damage_weapon;

	strcpy(p->tecnicas[0].nombre,nombre_tec);
	p->tecnicas[0].ataque_tec = danio_tec;
	p->tecnicas[0].cosmo_necesario = cosmo_nec;
}
void InicializarPersonaje2(Personaje *p)
{
	char nombre[]="Enemy";
	float healt =70;
	float attack =10;
	float cosmo =100;
	float arm =0.2;
	float defense = 0.1;

	char name_weapon[] = "Matacrakens";
	float damage_weapon= 0.25;

	char nombre_tec[] = "Invocacion de la parca";
	float danio_tec = 60;
	int cosmo_nec = 100;
	int cant_tec = 1;



	strcpy(p->Nombre,nombre);
	p->Vida = healt;
	p->ataque = attack;
	p->Cosmo = cosmo;
	p->Armadura = arm;
	p->defensa = defense;
	strcpy(p->arma.nombre,name_weapon);
	p->arma.danio_porcentual = damage_weapon;

	strcpy(p->tecnicas[0].nombre,nombre_tec);
	p->tecnicas[0].ataque_tec = danio_tec;
	p->tecnicas[0].cosmo_necesario = cosmo_nec;
}

int TurnosBatalla(Personaje *prota,Personaje *enemigo,int *resultado)
{
	int opcion;
	int opt_tec;
	int opt_tec_enemigo;
	int eleccionEnemigo;
	int danio;
	float valor_defensa;
	// aca va la parte del menu

	printf("Elija opcion: 1-atacar , 2-defenderse, 3-habilidad");
	opcion = ValidarEleccion(1,3,prota->cant_tec,&opt_tec,prota->tecnicas,prota->Cosmo);

	eleccionEnemigo = EleccionRandomEnemigo(enemigo,&opt_tec_enemigo);


	while(opcion !=4) // la opcion 4 seria salir de la batalla, escapar
	{
		EjecutarAccion(opcion,opt_tec,prota,enemigo,eleccionEnemigo);
		if(enemigo->Vida <= 0)
		{
			*resultado = 1;
			return 0;
		}


		EjecutarAccion(opcion,opt_tec,enemigo,prota,eleccionEnemigo);
		if(prota->Vida <= 0)
		{
			*resultado = 0;
			return 0;
		}

	}
	*resultado =-1;
	return 0;
}
int ValidarEleccion(int min ,int max,int cantTec,int *opt_tec, Tecnica tecnicas[],float cosmo)
{
	int n=-1;

	while(n == -1)
	{
		n = validarIntRango(min,max);

		//if (n == 2)
			// opt_tec = seleccionarTecnica(&tecnicas,cant_tec,cosmo);
				//menu que muestre la tecnicas disponibles
				//debe validar que alcance el cosmo para poder realizarla
				//si el usuario se arreepiente de elegir esta opcion , el valor de n pasa a ser -1

		//en este caso voy a elegir siempre la [0], pero lo debe hacer la funcion selecccionarTecnica();
		if (n == 2)
			*opt_tec = 0; //elijo la primer tecnica
	}


}
int validarIntRango(int min,int max)
{
	int num;
	int error=0;
	do
	{
		scanf("%d",&num);
		error=1;
		if (error)
			printf("\n Elija una opcion valida");
	}while(num<min || num>max);
	return num;
}
int EleccionRandomEnemigo(Personaje* enemigo, int *opt_tec_enemigo)
{
	srand(time(NULL));
	int numAccion = -1;

	while (numAccion == -1)
	{
		int numAccion = rand()%3+1;

		//if (numAccion == 2)
			// opt_tec = seleccionarTecnica(&tecnicas,cant_tec,cosmo);
				//menu que muestre la tecnicas disponibles
				//debe validar que alcance el cosmo para poder realizarla
				//si el usuario se arreepiente de elegir esta opcion , el valor de n pasa a ser -1

		//en este caso voy a elegir siempre la [0], pero lo debe hacer la funcion selecccionarTecnica();
		if (numAccion == 2)
			*opt_tec_enemigo = 0; //elijo la primer tecnica
	}

	return numAccion;
}

void EjecutarAccion(int opt,int opt_tec,Personaje *emisor,Personaje *receptor,int eleccionOponente)
{
	float danio;
	switch(opt)
	{
	case 1:
		danio = CalcularAtaque(emisor);
		recibeDanio(danio,receptor,eleccionOponente);
		break;
	case 2:
		printf("\n%s está a la defensiva",emisor->Nombre);
		break;
	case 3:

		danio = CalcularAtaqueTecnica(emisor,0); //el segundo parametro es opt_tec
		recibeDanio(danio,receptor,eleccionOponente);
		break;
	}
}
float CalcularAtaque(Personaje *p)
{
	float ataqueCalculado ;

 	ataqueCalculado = p->ataque + p->ataque*p->arma.danio_porcentual;
	return ataqueCalculado;
}
float CalcularAtaqueTecnica(Personaje *p,int num_tec) // hacemos una funcion nueva por que capaz tiene otros efectos las tecnica, ademas consume cosmo
{
	float ataqueCalculado ;

 	ataqueCalculado = p->tecnicas[num_tec].ataque_tec + p->ataque*p->arma.danio_porcentual;
 	p->Cosmo -= p->tecnicas[num_tec].cosmo_necesario;

	return ataqueCalculado;
}
void recibeDanio(float danio,Personaje *p,int eleccion)
{
	float defensa;
	if(eleccion == 2)
		defensa = p->defensa;
	else
		defensa = 0;

	float danioInfligido = danio - danio*p->Armadura - danio*defensa;

	p->Vida -= danioInfligido;
}
