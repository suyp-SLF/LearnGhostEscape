#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "core/scene.h"
/**
 * @brief SceneTitle类，继承自Scene类
 *
 * 这个类表示游戏的标题场景，用于显示游戏标题和开始选项等
 */
// 前向声明HUDButton类，这是一个用于用户界面按钮的类
// 前向声明允许我们在不完全定义类的情况下引用它
// 这种声明方式可以减少编译依赖，提高编译效率
// HUDButton类的声明
// 这是一个用于游戏界面中按钮功能的类
class HUDText;
class HUDButton;
class SceneTitle : public Scene // 继承自Scene基类
{
protected:
    glm::vec4 _boundary_color = glm::vec4(1, 0.5, 0.5, 1.0);
    float _boundary_color_timer = 0.0f;
    HUDButton *_start_button = nullptr;
    HUDButton *_quit_button = nullptr;
    HUDButton *_credits_button = nullptr;
    HUDText *_credits_text = nullptr;

public:
    SceneTitle() = default;
    virtual ~SceneTitle() = default;
    virtual void init() override;
    virtual void render() override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;

private:
    void renderBackground();
    void updateColor();
    void checkButtonQuit();
    void checkButtonStart();
    void checkButtonCredits();
};
#endif // SCENE_TITLE_H