#include "core/game.h"

int main(int, char**) {
   Game &game = Game::GetInstance();
   game.init("LearnGhostEscape", 800, 600);
   game.run();
   return 0;
}