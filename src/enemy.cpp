#include "enemy.h"
#include "affiliate/sprite_anim.h"
#include "raw/stats.h"

#include <SDL3/SDL.h>

void Enemy::init()
{
    Actor::init();
    _anim_normal = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-Sheet.png", Anchor::CENTER, 2.f);
    _anim_die = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghostDead-Sheet.png", Anchor::CENTER, 2.f);
    _anim_hurt = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghostHurt-Sheet.png", Anchor::CENTER, 2.f);
    _anim_normal->setActive(true);

    _type = ObjectType::ENEMY;
    _current_anim = _anim_normal;
    _collider = Collider::addColliderChild(this, _anim_normal->getSize(), Anchor::CENTER);
    _stats = Stats::addStatsChild(this);
}

void Enemy::handleEvents(SDL_Event &event)
{
    Actor::handleEvents(event);
}

void Enemy::update(float dt)
{
    Actor::update(dt);
    if (_target->getIsActive())
    {
        aim_target(_target);
        move(dt);
        attack();
    }
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
    if (parent) parent->addChild(enemy);
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
        break;
    default:
        break;
    }
    _current_state = new_state;
}
