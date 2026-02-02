#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "spawner.h"
#include "screen/ui_mouse.h"
#include "world/spell.h"
#include "screen/hud_stats.h"
#include "affiliate/text_label.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"
#include "screen/hud_skill.h"
#include "scene_title.h"
#include "raw/timer.h"
#include "raw/bg_star.h"

#include <fstream>

void SceneMain::init()
{
    Scene::init();
    SDL_HideCursor();

    _end_timer = Timer::addTimerChild(this, 3.0f);
    // BGM
    Game::getInstance().playMusic("assets/bgm/OhMyGhost.ogg");
    _world_size = Game::getInstance().getScreenSize() * 3.0f; // 3 倍于屏幕大小
    _camera_position = _world_size / 2.0f - Game::getInstance().getScreenSize() / 2.0f;

    _player = new Player();
    _player->init();
    _player->setPosition(_world_size / 2.0f);
    addChild(_player);

    _bg_star = BGStar::addBgStarChild(this, 2000, 0.2, 0.5, 0.7); // 添加背景星星
    
    _spawner = new Spawner();
    _spawner->init();
    _spawner->setTarget(_player);
    addChild(_spawner);
    _hud_text_score = HUDText::addHUDTextChild(this,
                                               "得分: 0",
                                               glm::vec2(Game::getInstance().getScreenSize().x - 250.f, 30.f),
                                               glm::vec2(100, 50)); // 添加得分文本

    _restart_button = HUDButton::addHUDButtonChild(this,
                                                   Game::getInstance().getScreenSize() - glm::vec2(230, 30),
                                                   "assets/UI/A_Restart1.png",
                                                   "assets/UI/A_Restart2.png",
                                                   "assets/UI/A_Restart3.png",
                                                   1.f,
                                                   Anchor::CENTER);

    _back_button = HUDButton::addHUDButtonChild(this,
                                                Game::getInstance().getScreenSize() - glm::vec2(140, 30),
                                                "assets/UI/A_Back1.png",
                                                "assets/UI/A_Back2.png",
                                                "assets/UI/A_Back3.png",
                                                1.f,
                                                Anchor::CENTER);
    _pause_button = HUDButton::addHUDButtonChild(this,
                                                 Game::getInstance().getScreenSize() - glm::vec2(50, 30),
                                                 "assets/UI/A_Pause1.png",
                                                 "assets/UI/A_Pause2.png",
                                                 "assets/UI/A_Pause3.png",
                                                 1.f,
                                                 Anchor::CENTER);

    _ui_mouse = UIMouse::addUIMouseChild(this, "assets/UI/29.png", "assets/UI/30.png", 1.f, Anchor::CENTER); // 添加鼠标
    _hud_stats = HUDStats::addHudStatsChild(this, _player, glm::vec2(30.f));                              // 添加血条

    auto mainScene = Game::getInstance().getCurrentScene();
    auto position = glm::vec2(Game::getInstance().getScreenSize().x - 100.f, 30.f);
    auto _hud_skill = HUDSkill::addHudSkillChild(mainScene, "assets/UI/Electric-Icon.png", position, .1f, Anchor::CENTER);
    
    _player->getWeapon()->setHudSkill(_hud_skill);
    
    TextLabel::addTextLabelChild(_player, "您", "assets/font/VonwaonBitmap-16px.ttf", 16, Anchor::CENTER);   // 添加文本
}
bool SceneMain::handleEvents(SDL_Event &event)
{
    if (Scene::handleEvents(event))
        return true; // 父类
    return false;    // 返回false，表示事件未被处理
}

void SceneMain::update(float dt)
{
    checkSlowDown(dt);
    Scene::update(dt); // 父类update
    updateScore();
    checkRestartButton();
    checkBackButton();
    checkPauseButton();
    if (_player && !_player->getIsActive())
    {
        if (_player->getScore() > Game::getInstance().getHighScore())
        {
            Game::getInstance().setHighScore(_player->getScore());
        }
        _end_timer->start();
        saveData("assets/score.dat");
    }
    checkEndTimer();
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

void SceneMain::saveData(const std::string &file_path)
{
    auto score = Game::getInstance().getHighScore();
    std::ofstream file(file_path, std::ios::binary);    //以二进制保存
    if (file.is_open())
    {
        file.write(reinterpret_cast<const char *>(&score), sizeof(score));
        file.close();
    }
}

void SceneMain::renderBackground()
{
    auto start = -_camera_position;
    auto end = _world_size - _camera_position;
    Game::getInstance().drawGrid(start, end, 80.0f, glm::vec2(0), {0.5, 0.5, 0.5, 1.0});
    Game::getInstance().drawBoundary(start, end, 4.0, {1.0, 1.0, 1.0, 1.0});
}

void SceneMain::updateScore()
{
    _hud_text_score->setText("得分: " + std::to_string(_player->getScore()));
}

void SceneMain::checkPauseButton()
{
    if (_pause_button->getIsTrigger())
    {
        if (_is_pause)
        {
            _is_pause = false;
            Game::getInstance().resumeMusic();
            Game::getInstance().resumeAllSoundEffects();
        }
        else
        {
            _is_pause = true;
            Game::getInstance().pauseMusic();
            Game::getInstance().pauseAllSoundEffects();
        }
    }
}

void SceneMain::checkBackButton()
{
    if (_back_button->getIsTrigger())
    {
        if (_player->getScore() > Game::getInstance().getHighScore())
        {
            Game::getInstance().setHighScore(_player->getScore());
        }
        saveData("assets/score.dat");
        _player->setScore(0); // 重置得分
        Game::getInstance().safeChangeScene(new SceneTitle());
    }
}

void SceneMain::checkRestartButton()
{
    if (_restart_button->getIsTrigger())
    {
        if (_player->getScore() > Game::getInstance().getHighScore())
        {
            Game::getInstance().setHighScore(_player->getScore());
        }
        saveData("assets/score.dat");
        _player->setScore(0); // 重置得分
        Game::getInstance().safeChangeScene(new SceneMain());
    }
}

void SceneMain::checkEndTimer()
{
    if (_end_timer->timerOut())
    {
        pause();
        saveData("assets/score.dat");
        auto screen_size = Game::getInstance().getScreenSize();
        _restart_button->setRenderPosition(screen_size / 2.f - glm::vec2(200, 0));
        _restart_button->setScale(4.f);
        _back_button->setRenderPosition(screen_size / 2.f + glm::vec2(200, 0));
        _back_button->setScale(4.f);
        _pause_button->setActive(false);
        _end_timer->stop(); // 停止计时器
    }
}

void SceneMain::checkSlowDown(float &dt)
{
    // 右键鼠标
    if(Game::getInstance().getMouseButtonState() & SDL_BUTTON_RMASK)
    {
        dt *= 0.4f;
    }
}
