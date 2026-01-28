#include "actor.h"
#include "scene.h"

#include "../raw/stats.h"
#include "../affiliate/affiliate_bar.h"
#include "../raw/stats.h"
#include "../core/game.h"

void Actor::update(float dt)
{
    ObjectWorld::update(dt);
    updateHealthBar();
}

void Actor::move(float dt)
{
    setPosition(_position + _velocity * dt);
    _position = glm::clamp(_position, glm::vec2(0.0f), _game.getCurrentScene()->getWorldSize());
}

void Actor::getIsAlive()
{
    _stats->getIsAlive();
}

void Actor::isInvisible()
{
    _stats->isInvincible();
}

int Actor::takeDamage(int damage)
{
    if (_stats)
    {
       return _stats->takeDamage(damage); 
    }else
    {
        return 0;
    }
}

void Actor::updateHealthBar()
{
    if(!_stats || !_health_bar) return;
    _health_bar->setPercentage(_stats->getHealth() / _stats->getMaxHealth());
}
