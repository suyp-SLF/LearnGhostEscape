#ifndef OBJECT_H
#define OBJECT_H

#include "game.h"
#include "defs.h"

#include <glm/glm.hpp>
#include <vector>
class Object
{
protected:
    ObjectType _type = ObjectType::NONE;
    Game &_game = Game::GetInstance();
    std::vector<Object *> _children_wait_to_add; // 子对象
    std::vector<Object *> _children; // 子对象
    bool _is_active = true; // 是否激活
    bool _is_delete =  false; // 是否需要删除
public:
    Object() = default;
    virtual ~Object() = default; // 所有的类，不在构造函数和析构函数里面做任何事。

    virtual void init() {} // 需要初始化的事物，在init()函数里面做。
    virtual void handleEvents(SDL_Event &event);
    virtual void update(float dt);
    virtual void render();
    virtual void clean(); // 需要清理的资源，在clean()函数里面做。

    // 子对象管理
    void safeAddChild(Object *child) { _children_wait_to_add.push_back(child); }
    virtual void addChild(Object *child) { _children.push_back(child); }
    virtual void removeChild(Object *child) { _children.erase(std::remove(_children.begin(), _children.end(), child), _children.end()); }

    // --GETTER AND SETTER
    ObjectType getType() { return _type; }
    void setType(ObjectType type) { _type = type; }
    void setActive(bool active) { _is_active = active; }
    bool isActive() { return _is_active; }
    void setDelete(bool delete_flag) { _is_delete = delete_flag; }
    bool isDelete() { return _is_delete; }
};
#endif // OBJECT_H