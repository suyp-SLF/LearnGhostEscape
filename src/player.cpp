#include "player.h"
#include "core/scene.h"
#include "affiliate/sprite_anim.h"
#include "raw/stats.h"

#include <SDL3/SDL.h>

void Player::init()
{
    Actor::init();
    _max_speed = 500;
    _sprite_idle = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-idle.png", Anchor::CENTER, 2.f);
    _sprite_run = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-move.png", Anchor::CENTER, 2.1f);
    _sprite_run->setActive(true);

    _collider = Collider::addColliderChild(this, _sprite_idle->getSize() / 2.f, Anchor::CENTER);
    _stats = Stats::addStatsChild(this);
    _effect = Effect::addEffectChild(nullptr, "assets/effect/1764.png", glm::vec2(0), 1.0f);
    _weapon_thunder = WeaponThunder::addWeaponThunderChild(this, 2.f, 40.f);
}

void Player::handleEvents(SDL_Event &event)
{
    Actor::handleEvents(event);
}

void Player::update(float dt)
{
    Actor::update(dt);
    _velocity *= 0.9f;
    keyboardControl();
    move(dt);
    syncCamera();
    checkState();
    checkIsDead();
}

void Player::render()
{
    Actor::render();
    _game.drawBoundary(_render_position, _render_position, 5.0f, {1.0, 0.0, 0.0, 1.0});
}

void Player::clean()
{
    Actor::clean();
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

    if (currentKeyStates[SDL_SCANCODE_A])
    {
        _velocity.x = -_max_speed;
    }
    else if (currentKeyStates[SDL_SCANCODE_D])
    {
        _velocity.x = _max_speed;
    }
}

void Player::syncCamera()
{
    _game.getCurrentScene()->setCameraPosition(_position - _game.getScreenSize() / 2.0f);
}

void Player::checkState()
{
    // 翻转以及是否移动
    if (glm::length(_velocity) > 0.1)
    {
        _sprite_run->setActive(true);
        _sprite_idle->setActive(false);
    }
    else
    {
        _sprite_run->setActive(false);
        _sprite_idle->setActive(true);
    }
    if (_velocity.x > 0)
    {
        _sprite_run->setFlip(SDL_FLIP_NONE);
        _sprite_idle->setFlip(SDL_FLIP_NONE);
    }
    else
    {
        _sprite_run->setFlip(SDL_FLIP_HORIZONTAL);
        _sprite_idle->setFlip(SDL_FLIP_HORIZONTAL);
    }
}

void Player::checkIsDead()
{
    if (!_stats->getIsAlive())
    {
        _game.getCurrentScene()->safeAddChild(_effect);
        _effect->setPosition(_position);
        setActive(false);
    }
}
