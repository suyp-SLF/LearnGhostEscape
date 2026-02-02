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
    _position = glm::clamp(_position, glm::vec2(0.0f), Game::getInstance().getCurrentScene()->getWorldSize());
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

void Actor::removeMoveControl()
{
    if(_move_control)
    {
        _move_control->setIsDelete(true);
        _move_control = nullptr;
    }
}

void Actor::setMoveControl(MoveControl *move_control)
{
    if(_move_control)
    {
        _move_control = move_control;
    }
    _move_control = move_control;
    _move_control->setParent(this);
    safeAddChild(move_control);
}

void Actor::updateHealthBar()
{
    if(!_stats || !_health_bar) return;
    _health_bar->setPercentage(_stats->getHealth() / _stats->getMaxHealth());
}
