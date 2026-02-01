#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "core/scene.h"
#include <glm/glm.hpp>

class HUDStats;
class UIMouse;
class Player;
class Spawner;
class HUDText;
class HUDButton;
class BGStar;
class Timer;
class SceneMain : public Scene
{
private:
    // 世界大小
    Player *_player = nullptr;  // 玩家
    Spawner *_spawner = nullptr;    // 敌人生成器
    UIMouse *_ui_mouse = nullptr;   // 鼠标
    HUDStats *_hud_stats = nullptr; // 状态栏
    BGStar *_bg_star = nullptr; // 背景星星

    HUDButton *_pause_button = nullptr; // 暂停按钮
    HUDButton *_back_button = nullptr; // 恢复按钮
    HUDButton *_restart_button = nullptr; // 退出按钮

    HUDText *_hud_text_score = nullptr; // 得分

    Timer * _end_timer = nullptr; // 游戏结束计时器
public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    virtual void init() override; // 初始化
    virtual bool handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override; // 清理

    virtual void saveData(const std::string &file_path) override;
private:
    // 绘制背景图片
    void renderBackground();
    void updateScore(); // 更新得分

    void checkPauseButton(); // 检查暂停按钮
    void checkBackButton(); // 检查恢复按钮
    void checkRestartButton(); // 检查重新开始按钮
    void checkEndTimer(); // 检查游戏结束计时器

    void checkSlowDown(float &dt); // 检查减速
};

#endif // SCENE_MAIN_H