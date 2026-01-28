#include "spawner.h"
#include "core/scene.h"
#include "enemy.h"

void Spawner::update(float dt)
{
    Object::update(dt);
    _spawn_timer += dt;
    if (_spawn_timer >= _spawn_time)
    {
        _spawn_timer = 0.0f;
        SDL_Log("Spawner: spawn enemies");
        _game.playSoundEffect("assets/sound/silly-ghost-sound-242342.mp3");
        for (int i = 0; i < _spawn_count; i++)
        {
            auto position = _game.randomVec2(
                _game.getCurrentScene()->getCameraPosition(),
                _game.getCurrentScene()->getCameraPosition() + _game.getScreenSize());
            Enemy *enemy = Enemy::addEnemyChild(nullptr, position, _target);

            Effect::addEffectChild(_game.getCurrentScene(), "assets/effect/184_3_.png", position, 1.f, enemy); // 添加特效
        }
    }
}