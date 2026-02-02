#include "move_control.h"
#include "../core/actor.h"

void MoveControl::update(float dt)
{
    if (_parent == nullptr)
        return;
    Object::update(dt);
    _parent->setVelocity(_parent->getVelocity() * 0.9f);
    auto direction = glm::vec2(_is_right - _is_left, _is_down - _is_up);
    if (glm::length(direction) > 0.1f)
    {
        direction = glm::normalize(direction);
        _parent->setVelocity(direction * _max_speed);
    }
}

bool MoveControl::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        if(event.key.scancode == SDL_SCANCODE_W)
        {
            _is_up = true;
            return true;
        }
        if(event.key.scancode == SDL_SCANCODE_S)
        {
            _is_down = true;
            return true;
        }
        if(event.key.scancode == SDL_SCANCODE_A)
        {
            _is_left = true;
            return true;
        }
        if(event.key.scancode == SDL_SCANCODE_D)
        {
            _is_right = true;
            return true;
        }
    }
    if (event.type == SDL_EVENT_KEY_UP)
    {
        if(event.key.scancode == SDL_SCANCODE_W)
        {
            _is_up = false;
            return true;
        }
        if(event.key.scancode == SDL_SCANCODE_S)
        {
            _is_down = false;
            return true;
        }
        if(event.key.scancode == SDL_SCANCODE_A)
        {
            _is_left = false;
            return true;
        }
        if(event.key.scancode == SDL_SCANCODE_D)
        {
            _is_right = false;
            return true;
        }
    }
    return false;
}
