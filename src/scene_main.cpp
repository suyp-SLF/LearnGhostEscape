#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "spawner.h"
#include "screen/ui_mouse.h"
#include "world/spell.h"
#include "screen/hud_stats.h"
#include "affiliate/text_label.h"
#include "screen/hud_text.h"

void SceneMain::init()
{
    Scene::init();
    SDL_HideCursor();
    //
    _game.playMusic("assets/bgm/OhMyGhost.ogg");
    _world_size = _game.getScreenSize() * 3.0f; // 3 倍于屏幕大小
    _camera_position = _world_size / 2.0f - _game.getScreenSize() / 2.0f;
    _player = new Player();
    _player->init();
    _player->setPosition(_world_size / 2.0f);
    addChild(_player);

    _spawner = new Spawner();
    _spawner->init();
    _spawner->setTarget(_player);
    addChild(_spawner);

    _ui_mouse = UIMouse::addUIMouseChild(this, "assets/UI/29.png", "assets/UI/30.png", 1.f, Anchor::CENTER);   // 添加鼠标
    _hud_stats = HUDStats::addHudStatsChild(this, _player, glm::vec2(30.f));                                   // 添加血条
    TextLabel::addTextLabelChild(_player, "您", "assets/font/VonwaonBitmap-16px.ttf", 16, Anchor::CENTER); // 添加文本
    _hud_text_score = HUDText::addHUDTextChild(
        this,
        "得分: 0",
        glm::vec2(_game.getScreenSize().x - 250.f, 30.f),
        glm::vec2(100, 50)
    ); // 添加得分文本
}
void SceneMain::handleEvents(SDL_Event &event)
{
    Scene::handleEvents(event); // 父类
}

void SceneMain::update(float dt)
{
    Scene::update(dt); // 父类update
    updateScore();
}

void SceneMain::render()
{
    renderBackground();
    Scene::render(); // 父类render
}

void SceneMain::clean()
{
    Scene::clean(); // 父类clean
}

void SceneMain::renderBackground()
{
    auto start = -_camera_position;
    auto end = _world_size - _camera_position;
    _game.drawGrid(start, end, 80.0f, glm::vec2(0), {0.5, 0.5, 0.5, 1.0});
    _game.drawBoundary(start, end, 4.0, {1.0, 1.0, 1.0, 1.0});
}

void SceneMain::updateScore()
{
    _hud_text_score->setText("得分: " + std::to_string(_player->getScore()));
}
