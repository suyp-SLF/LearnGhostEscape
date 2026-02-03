#include "player.h"
#include "core/scene.h"
#include "affiliate/sprite_anim.h"
#include "raw/stats.h"
#include "world/spell.h"

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
    _effect = Effect::addEffectChild(Game::getInstance().getCurrentScene(), "assets/effect/1764.png", glm::vec2(0), 1.0f);
    _effect->setActive(false);

    _weapon = Weapon::addWeaponChild(this, 2.f, 40.f);
    auto spell_prototype = Spell::addSpellChild(Game::getInstance().getCurrentScene(), "assets/effect/Thunderstrike w blur.png", glm::vec2(0), 40.f, 3.f, Anchor::CENTER);
    spell_prototype->setActive(false);
    _weapon->setSpellPrototype(spell_prototype);

    setMoveControl(new MoveControl());
}

bool Player::handleEvents(SDL_Event &event)
{
    if (Actor::handleEvents(event))
        return true;
    return false;
}

void Player::update(float dt)
{
    Actor::update(dt);
    move(dt);
    syncCamera();
    checkState();
    checkIsDead();
}

void Player::render()
{
    Actor::render();
    Game::getInstance().drawBoundary(getRenderPosition(), getRenderPosition(), 5.0f, {1.0, 0.0, 0.0, 1.0});
}

void Player::clean()
{
    Actor::clean();
}

int Player::takeDamage(int damage)
{
    int fin_damage = Actor::takeDamage(damage);
    if (fin_damage > 0)
    {
        Game::getInstance().playSoundEffect("assets/sound/hit-flesh-02-266309.mp3");
    }
    return fin_damage;
}

void Player::syncCamera()
{
    Game::getInstance().getCurrentScene()->setCameraPosition(_position - Game::getInstance().getScreenSize() / 2.0f);
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
        _effect->setActive(true);
        _effect->setPosition(_position);
        setActive(false);
        Game::getInstance().playSoundEffect("assets/sound/female-scream-02-89290.mp3");
    }
}
