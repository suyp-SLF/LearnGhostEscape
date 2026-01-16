#ifndef SCENE_H
#define SCENE_H

#include "object.h"

#include "glm/glm.hpp"
#include <vector>

class Scene : public Object
{
protected:
    glm::vec2 _world_size = glm::vec2(0);
    glm::vec2 _camera_position = glm::vec2(0); // 相机位置
    std::vector<Object *> _objects;            // 场景中的物体
public:
    Scene() = default;
    // 必须有定义！
    virtual ~Scene() = default;

    virtual void init() override {}; // 初始化
    virtual void handleEvents(SDL_Event &event) override {};
    virtual void update(float dt) override {};
    virtual void render() override {};
    virtual void clean() override {}; // 清理

    // 世界坐标转屏幕坐标
    glm::vec2 worldToScreen(const glm::vec2 world_position) const
    {
        return world_position - _camera_position;
    };
    // 屏幕坐标转世界坐标
    glm::vec2 screenToWorld(const glm::vec2 screen_position) const
    {
        return screen_position + _camera_position;
    }

    // getter and setter
    // --相机位置--
    glm::vec2 getCameraPosition() const { return _camera_position; }
    void setCameraPosition(const glm::vec2 camera_position);
    // --世界大小--
    glm::vec2 getWorldSize() const { return _world_size; }
    void setWorldSize(const glm::vec2 world_size) { _world_size = world_size; }
};

#endif // SCENE_H