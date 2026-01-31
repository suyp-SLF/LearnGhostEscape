#ifndef SCENE_H
#define SCENE_H

#include "object_world.h"
#include "object_screen.h"

#include "glm/glm.hpp"
#include <vector>

class Scene : public Object
{
protected:
    glm::vec2 _world_size = glm::vec2(0);
    glm::vec2 _camera_position = glm::vec2(0); // 相机位置
    std::vector<ObjectWorld*> _children_world;            // 世界坐标下的子对象
    std::vector<ObjectScreen*> _children_screen;           // 屏幕坐标下的子对象

public:
    Scene() = default;
    // 必须有定义！
    virtual ~Scene() = default;

    virtual void init() override {}; // 初始化
    virtual bool handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override; // 清理

    // UTILS
    // 
    void pause();
    void resume();
    // --添加,移除对象到场景中--
    virtual void addChild(Object *child) override;
    virtual void removeChild(Object *child) override;
    // 保存与加载数据文件
    virtual void saveData(const std::string &file_path) {};
    virtual void loadData(const std::string &file_path) {};
    // --世界坐标转屏幕坐标,屏幕坐标转世界坐标--
    glm::vec2 worldToScreen(const glm::vec2 world_position) const;
    glm::vec2 screenToWorld(const glm::vec2 screen_position) const;
    
    // GETTER AND SETTER
    // --相机位置--
    glm::vec2 getCameraPosition() const { return _camera_position; }
    void setCameraPosition(const glm::vec2 camera_position);
    // --世界大小--
    glm::vec2 getWorldSize() const { return _world_size; }
    void setWorldSize(const glm::vec2 world_size) { _world_size = world_size; }

    std::vector<ObjectWorld*>& getChildrenWorld() { return _children_world; }
    std::vector<ObjectScreen*>& getChildrenScreen() { return _children_screen; }
};

#endif // SCENE_H