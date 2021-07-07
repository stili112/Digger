#include"Game.h"

#include <iostream>

int main()
{
	try
	{
		Game& game = Game::getInstance();
		game.run();		
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
   

    return 0;
}

