#include <iostream>
#include "main.h"

using namespace std;

int main(int argc, char **argv)
{
	Snake::Engine Engine;
	
	Engine.Setup();
	
	while(!Engine.gameOver)
		{
			Engine.Draw();
			Engine.Input();
			usleep(50000);
			Engine.Logic();
		}
	
	return 0;
}
