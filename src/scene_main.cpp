#include "scene_main.h"
#include "player.h"

void SceneMain::init()
{
    _world_size = _game.getScreenSize() * 3.0f; // 3 倍于屏幕大小
    _camera_position = _world_size / 2.0f - _game.getScreenSize() / 2.0f;
    _player = new Player();
    _player->init();
    _player->setPosition(_world_size / 2.0f);
}

void SceneMain::handleEvents(SDL_Event &event)
{
}

void SceneMain::update(float dt)
{
    _camera_position += glm::vec2(1, 1) * dt * 100.0f;
    _player->update(dt);
}

void SceneMain::render()
{
    renderBackground();
    _player->render();
}

void SceneMain::clean()
{
    _player->clean();
    delete _player;
}

void SceneMain::renderBackground()
{
    auto start = -_camera_position;
    auto end = _world_size - _camera_position;
    _game.drawGrid(start, end, 80.0f, glm::vec2(0), {0.5, 0.5, 0.5, 1.0});
    _game.drawBoundary(start, end, 4.0, {1.0, 1.0, 1.0, 1.0});
    _game.drawFPS({100.0f, 100.0f}, {1.0f, 1.0f, 1.0f, 1.0f});
}
