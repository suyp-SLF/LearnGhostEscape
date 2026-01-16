#include "player.h"
#include "core/scene.h"

#include <SDL3/SDL.h>

void Player::init()
{
}

void Player::handleEvents(SDL_Event &event)
{
}

void Player::update(float dt)
{
    _velocity *= 0.9f;
    keyboardControl();
    move(dt);
    syncCamera();
}

void Player::render()
{
    _game.drawBoundary(_render_position, _render_position, 5.0f, {1.0, 0.0, 0.0, 1.0});
}

void Player::clean()
{
}

void Player::keyboardControl()
{
    auto currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_W])
    {
        _velocity.y = -_max_speed;
    }
    else if (currentKeyStates[SDL_SCANCODE_S])
    {
        _velocity.y = _max_speed;
    }
    else
    {
        _velocity.y = 0;
    }

    if (currentKeyStates[SDL_SCANCODE_A])
    {
        _velocity.x = -_max_speed;
    }
    else if (currentKeyStates[SDL_SCANCODE_D])
    {
        _velocity.x = _max_speed;
    }
    else
    {
        _velocity.x = 0;
    }
}

void Player::move(float dt)
{
    setPosition(_position + _velocity * dt);
    _position = glm::clamp(_position, glm::vec2(0.0f), _game.getCurrentScene()->getWorldSize());
}

void Player::syncCamera()
{
    _game.getCurrentScene()->setCameraPosition(_position - _game.getScreenSize() / 2.0f);
}
