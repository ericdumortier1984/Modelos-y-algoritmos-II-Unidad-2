#include "Game.h"

//Implemente una aplicaci�n similar al juego del ca��n.
//La idea es que desde el extremo izquierdo de la pantalla puedan disparar un objeto hacia el lado derecho, 
//variando la direcci�n del mismo.

int main()
{

	Game* GO;
	GO = new Game(800, 600);
	GO->Loop();

	return 0;
}