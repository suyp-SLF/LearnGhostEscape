#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "core/scene.h"

#include <glm/glm.hpp>

class UIMouse;
class Player;
class Spawner;
class SceneMain : public Scene
{
private:
    // 世界大小
    Player *_player = nullptr;  // 玩家
    Spawner *_spawner = nullptr;    // 敌人生成器
    UIMouse *_ui_mouse = nullptr;   // 鼠标

public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    virtual void init() override; // 初始化
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override; // 清理
private:
    // 绘制背景图片
    void renderBackground();
};

#endif // SCENE_MAIN_H