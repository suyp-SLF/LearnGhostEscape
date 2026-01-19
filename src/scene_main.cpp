#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "world/effect.h"

void SceneMain::init()
{
    _world_size = _game.getScreenSize() * 3.0f; // 3 倍于屏幕大小
    _camera_position = _world_size / 2.0f - _game.getScreenSize() / 2.0f;
    _player = new Player();
    _player->init();
    _player->setPosition(_world_size / 2.0f);
    addChild(_player);

    

    auto enemy = new Enemy();
    enemy->init();
    enemy->set_target(_player);
    enemy->setPosition(_world_size / 2.0f + glm::vec2(100.0f, 0.0f));

    Effect::addEffectChild(this, "assets/effect/184_3_.png", _world_size / 2.0f + glm::vec2(100.0f, 0.0f), 2.f, enemy); // 添加特效
}

void SceneMain::handleEvents(SDL_Event &event)
{
    Scene::handleEvents(event); //父类update
}

void SceneMain::update(float dt)
{
    Scene::update(dt);  //父类update
}

void SceneMain::render()
{
    renderBackground();
    Scene::render();    //父类render
}

void SceneMain::clean()
{
    Scene::clean(); //父类clean
}

void SceneMain::renderBackground()
{
    auto start = -_camera_position;
    auto end = _world_size - _camera_position;
    _game.drawGrid(start, end, 80.0f, glm::vec2(0), {0.5, 0.5, 0.5, 1.0});
    _game.drawBoundary(start, end, 4.0, {1.0, 1.0, 1.0, 1.0});
    _game.drawFPS({100.0f, 100.0f}, {1.0f, 1.0f, 1.0f, 1.0f});
}
