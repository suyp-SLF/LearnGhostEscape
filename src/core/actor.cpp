#include "actor.h"
#include "scene.h"

#include "../raw/stats.h"

void Actor::move(float dt)
{
    setPosition(_position + _velocity * dt);
    _position = glm::clamp(_position, glm::vec2(0.0f), _game.getCurrentScene()->getWorldSize());
}

void Actor::isAlive()
{
    _stats->isAlive();
}

void Actor::isInvisible()
{
    _stats->isInvincible();
}

void Actor::takeDamage(int damage)
{
    _stats->takeDamage(damage); 
}
