#include "scene_title.h"
#include "screen/hud_text.h"

#include <cmath>

void SceneTitle::init()
{
    Scene::init();
    auto screen_size = _game.getScreenSize();
    auto size = glm::vec2(screen_size.x / 2.f, screen_size.y / 3.f);
    HUDText::addHUDTextChild(
        this,
        "幽 灵 逃 生",
        screen_size / 2.f - glm::vec2(0, 100),
        size,
        "assets/font/VonwaonBitmap-16px.ttf",
        64);
    auto _score_text = "最高分：" + std::to_string(_game.getHighscore());
    HUDText::addHUDTextChild(
        this,
        _score_text,
        screen_size / 2.f + glm::vec2(0, 100),
        glm::vec2(200, 50),
        "assets/font/VonwaonBitmap-16px.ttf",
        32);
}

void SceneTitle::render()
{
    renderBackground();
    Scene::render();
}

void SceneTitle::handleEvents(SDL_Event &event)
{
    Scene::handleEvents(event);
}

void SceneTitle::update(float dt)
{
    _boundary_color_timer += dt;
    Scene::update(dt);
    updateColor();
}

void SceneTitle::renderBackground()
{
    auto screen_size = _game.getScreenSize();
    _game.drawBoundary(
        glm::vec2(30, 30),
        screen_size - glm::vec2(30, 30),
        8.f,
        _boundary_color);
}

void SceneTitle::updateColor()
{
    _boundary_color.r = 0.5f + 0.5f * sinf(_boundary_color_timer * .8f);
    _boundary_color.g = 0.5f + 0.5f * sinf(_boundary_color_timer * .9f);
    _boundary_color.b = 0.5f + 0.5f * sinf(_boundary_color_timer * .7f);
}
