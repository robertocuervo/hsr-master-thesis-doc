#include "stdafx.h"
#include "../Viewer/GameController.h"
#include <iostream>

int main(int argc, char* argv[])
{
	char * config = "";
	if (argc > 1)
	{
		config = argv[1];
	}

	GameController gameController{};
	gameController.init(config);
	gameController.gameLoop();
	gameController.finish();
}
