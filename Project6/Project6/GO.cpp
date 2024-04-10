#include "Game.h"

//Implemente una aplicación similar al juego del cañón.
//La idea es que desde el extremo izquierdo de la pantalla puedan disparar un objeto hacia el lado derecho, 
//variando la dirección del mismo.

int main()
{

	Game* GO;
	GO = new Game(800, 600);
	GO->Loop();

	return 0;
}