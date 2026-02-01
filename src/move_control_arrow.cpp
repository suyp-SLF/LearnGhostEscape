#include "move_control_arrow.h"

void MoveControlArrow::update(float dt)
{
    MoveControl::update(dt);
    auto keyboard = SDL_GetKeyboardState(NULL);
    _is_up = keyboard[SDL_SCANCODE_UP];
    _is_down = keyboard[SDL_SCANCODE_DOWN];
    _is_left = keyboard[SDL_SCANCODE_LEFT];
    _is_right = keyboard[SDL_SCANCODE_RIGHT];
}
