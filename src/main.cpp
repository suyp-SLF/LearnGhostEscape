#include "core/game.h"
#include <fstream>

int main(int, char **)
{
   std::ifstream f("assets/font/VonwaonBitmap-16px.ttf");
   if (!f.good())
   {
      SDL_Log("文件系统检查：无法访问字体文件！请检查 assets 文件夹位置。");
   }
   else
   {
      SDL_Log("文件系统检查：找到字体文件了。");
   }

   Game &game = Game::GetInstance();
   game.init("LearnGhostEscape", 1280, 720);
   game.run();
   return 0;
}