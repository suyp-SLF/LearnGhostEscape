#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "core/scene.h"

#include <glm/glm.hpp>

class Player;
class SceneMain : public Scene
{
private:
    //世界大小
   Player* _player = nullptr;
    

public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    virtual void init() override; // 初始化
    virtual void handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override; // 清理
private:
 // 绘制背景图片
    void renderBackground();
};

#endif // SCENE_MAIN_H