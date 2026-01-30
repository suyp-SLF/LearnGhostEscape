#include "enemy.h"
#include "affiliate/sprite_anim.h"
#include "raw/stats.h"

#include <SDL3/SDL.h>

void Enemy::init()
{
    Actor::init();
    _anim_normal = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-Sheet.png", Anchor::CENTER, 2.f);
    _anim_die = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghostDead-Sheet.png", Anchor::CENTER, 2.f);
    _anim_die->setIsLoop(false);
    _anim_die->setActive(false);
    _anim_hurt = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghostHurt-Sheet.png", Anchor::CENTER, 2.f);
    _anim_hurt->setActive(false);

    _type = ObjectType::ENEMY;
    _current_anim = _anim_normal;
    _collider = Collider::addColliderChild(this, _anim_normal->getSize(), Anchor::CENTER);

    _health_bar = AffiliateBar::addAffiliateBarChild(this, glm::vec2(100.0f, 10.0f), Anchor::BOTTOM_CENTER);
    _stats = Stats::addStatsChild(this);
}

bool Enemy::handleEvents(SDL_Event &event)
{
    if (Actor::handleEvents(event)) return true;
    return false;
}

void Enemy::update(float dt)
{
    Actor::update(dt);
    if (_target->getIsActive() && _current_state != State::DIE)
    {
        aim_target(_target);
        move(dt);
        attack();
    }
    checkState();
    remove();
}

void Enemy::render()
{
    Actor::render();
    _game.drawBoundary(_render_position, _render_position, 5.0f, {1.0, 0.0, 0.0, 1.0});
}

void Enemy::clean()
{
    Actor::clean();
}

Enemy *Enemy::addEnemyChild(Object *parent, glm::vec2 postion, Player *_target)
{
    auto enemy = new Enemy();
    enemy->init();
    enemy->set_target(_target);
    enemy->setPosition(postion);
    if (parent) parent->safeAddChild(enemy);
    return enemy;
}

void Enemy::attack()
{
    if (!_collider || !_target || _target->getCollider() == nullptr)
        return;
    if (_collider->isColliding(_target->getCollider()))
    {
        if (_stats && _target->getStats())
        {
            _target->takeDamage(_stats->getDamage());
        }
    }
}

void Enemy::aim_target(Player *target)
{
    if (target == nullptr)
        return;
    auto direction = target->getPosition() - getPosition();
    direction = glm::normalize(direction);
    _velocity = direction * _max_speed;
}

void Enemy::checkState()
{
    State new_state;
    if (_stats->getHealth() <= 0)
    {
        new_state = State::DIE;
    }
    else if (_stats->getHealth() < _stats->getMaxHealth())
    {
        new_state = State::HURT;
    }
    else
    {
        new_state = State::NORMAL;
    }
    if (new_state != _current_state)
    {
        changeState(new_state);
    }
}

void Enemy::changeState(State new_state)
{
    _current_anim->setActive(false);
    switch (new_state)
    {
    case State::NORMAL:
        _current_anim = _anim_normal;
        _current_anim->setActive(true);
        break;
    case State::HURT:
        _current_anim = _anim_hurt;
        _current_anim->setActive(true);
        break;
    case State::DIE:
        _current_anim = _anim_die;
        _current_anim->setActive(true);
        _target->addScore(_score);
        break;
    default:
        break;
    }
    _current_state = new_state;
}

void Enemy::remove()
{
    if(_anim_die->getIsFinish()){
        _is_delete = true;
    }
}
