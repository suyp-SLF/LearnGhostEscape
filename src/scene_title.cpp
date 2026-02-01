#include "scene_title.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"
#include "scene_main.h"
#include "screen/ui_mouse.h"

#include <cmath>
#include <fstream>

void SceneTitle::init()
{
    Scene::init();
    loadData("assets/score.dat");
    SDL_ShowCursor();
    // BGM
    _game.playMusic("assets/bgm/Spooky music.mp3");

    auto screen_size = _game.getScreenSize();
    auto size = glm::vec2(screen_size.x / 2.f, screen_size.y / 3.f);
    HUDText::addHUDTextChild(this,
                             "幽 灵 逃 生",
                             screen_size / 2.f - glm::vec2(0, 100),
                             size,
                             "assets/font/VonwaonBitmap-16px.ttf",
                             64);
    auto _score_text = "最高分：" + std::to_string(_game.getHighScore());
    HUDText::addHUDTextChild(this,
                             _score_text,
                             screen_size / 2.f + glm::vec2(0, 100),
                             glm::vec2(200, 50),
                             "assets/font/VonwaonBitmap-16px.ttf",
                             32);
    auto text = _game.loadTextFile("assets/credits.txt");
    _quit_button = HUDButton ::addHUDButtonChild(this,
                                                 glm::vec2(_game.getScreenSize().x * 5 / 6, _game.getScreenSize().y - 100),
                                                 "assets/UI/A_Quit1.png",
                                                 "assets/UI/A_Quit2.png",
                                                 "assets/UI/A_Quit3.png",
                                                 2.f,
                                                 Anchor::CENTER);
    _credits_button = HUDButton ::addHUDButtonChild(this,
                                                    glm::vec2(_game.getScreenSize().x * 3 / 6, _game.getScreenSize().y - 100),
                                                    "assets/UI/A_Credits1.png",
                                                    "assets/UI/A_Credits2.png",
                                                    "assets/UI/A_Credits3.png",
                                                    2.f,
                                                    Anchor::CENTER);
    _start_button = HUDButton ::addHUDButtonChild(this,
                                                  glm::vec2(_game.getScreenSize().x * 1 / 5, _game.getScreenSize().y - 100),
                                                  "assets/UI/A_Start1.png",
                                                  "assets/UI/A_Start2.png",
                                                  "assets/UI/A_Start3.png",
                                                  2.f,
                                                  Anchor::CENTER);

    _credits_text = HUDText::addHUDTextChild(this,
                                             text,
                                             _game.getScreenSize() / 2.f,
                                             glm::vec2(0, 0));
    _credits_text->setActive(false);
    _ui_mouse = UIMouse::addUIMouseChild(this, "assets/UI/pointer_c_shaded.png", "assets/UI/pointer_c_shaded.png", 1.f, Anchor::TOP_LEFT);
}

/**
 * 渲染场景标题界面的函数
 * 该函数负责渲染场景标题界面的所有可见元素
 */
void SceneTitle::render()
{
    renderBackground();
    Scene::render();
}

bool SceneTitle::handleEvents(SDL_Event &event)
{
    if (_credits_text->getIsActive())
    {
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                _credits_text->setActive(false);
                return true;
            }
        }
    }
    if (Scene::handleEvents(event)) return true;
    return false;
}

void SceneTitle::update(float dt)
{
    _boundary_color_timer += dt;
    updateColor();
    if (_credits_text->getIsActive())
    {
        _ui_mouse->update(dt);
        return;
    }
    checkButtonQuit();
    checkButtonStart();
    checkButtonCredits();
    Scene::update(dt);
}

void SceneTitle::loadData(const std::string &file_path)
{
    int score = 0;
    std::ifstream file(file_path);
    if (file.is_open())
    {
        file.read(reinterpret_cast<char *>(&score), sizeof(int));
        file.close();
    }
    _game.setHighScore(score);
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

void SceneTitle::checkButtonQuit()
{
    if (_quit_button->getIsTrigger())
    {
        _game.quit();
    }
}

void SceneTitle::checkButtonStart()
{
    if (_start_button->getIsTrigger())
    {
        _game.safeChangeScene(new SceneMain());
    }
}

void SceneTitle::checkButtonCredits()
{
    if (_credits_button->getIsTrigger())
    {
        _credits_text->setActive(true);
    }
}
