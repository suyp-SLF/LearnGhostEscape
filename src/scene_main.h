#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "core/scene.h"
#include <glm/glm.hpp>

class HUDStats;
class UIMouse;
class Player;
class Spawner;
class HUDText;
class SceneMain : public Scene
{
private:
    // 世界大小
    Player *_player = nullptr;  // 玩家
    Spawner *_spawner = nullptr;    // 敌人生成器
    UIMouse *_ui_mouse = nullptr;   // 鼠标
    HUDStats *_hud_stats = nullptr; // 状态栏

    HUDText *_hud_text_score = nullptr; // 得分
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
    void updateScore(); // 更新得分
};

#endif // SCENE_MAIN_H