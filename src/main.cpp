#include "core/game.h"
#include <fstream>

int main(int, char **)
{
   Game &game = Game::GetInstance();
   game.init("LearnGhostEscape", 1280, 720);
   game.run();
   return 0;
}