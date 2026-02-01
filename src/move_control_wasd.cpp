#include "move_control_wasd.h"

void MoveControlWASD::update(float dt)
{
    MoveControl::update(dt);
    auto keyboard = SDL_GetKeyboardState(NULL);
    _is_up = keyboard[SDL_SCANCODE_W];
    _is_down = keyboard[SDL_SCANCODE_S];
    _is_left = keyboard[SDL_SCANCODE_A];
    _is_right = keyboard[SDL_SCANCODE_D];
}
