#include "Classes/Game.h"
#include <stdio.h>
using namespace GameEngine;

int main(int argc, char** argv) {
	Game testGame("Test Game", 640, 480);
	testGame.LoadLevel("TestLevel");
	testGame.AddPlayer(new Player(), 315.0, 235.0);
	testGame.Start();

	return 0;
}
