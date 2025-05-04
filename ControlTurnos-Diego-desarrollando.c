
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