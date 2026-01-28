#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "core/scene.h"
/**
 * @brief SceneTitle类，继承自Scene类
 *
 * 这个类表示游戏的标题场景，用于显示游戏标题和开始选项等
 */
class SceneTitle : public Scene // 继承自Scene基类
{
protected:
    glm::vec4 _boundary_color = glm::vec4(1, 0.5, 0.5, 1.0);
    float _boundary_color_timer = 0.0f;

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
};
#endif // SCENE_TITLE_H