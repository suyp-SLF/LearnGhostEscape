#ifndef OBJECT_H
#define OBJECT_H

#include "game.h"
#include "defs.h"

#include <glm/glm.hpp>
#include <vector>
class Object
{
protected:
    std::string _name;
    std::string _source_path;
    ObjectType _type = ObjectType::NONE;
    std::vector<Object *> _children_wait_to_add; // 子对象
    std::vector<Object *> _children; // 子对象
    bool _is_active = true; // 是否激活
    bool _is_delete =  false; // 是否需要删除
    bool _is_pause = false; // 是否暂停
public:
    Object() = default;
    virtual ~Object() = default; // 所有的类，不在构造函数和析构函数里面做任何事。

    virtual void init(); // 需要初始化的事物，在init()函数里面做。
    virtual bool handleEvents(SDL_Event &event);    // 返回true代表事件已被处理
    virtual void update(float dt);
    virtual void render();
    virtual void clean(); // 需要清理的资源，在clean()函数里面做。

    // 子对象管理
    void safeAddChild(Object *child) { _children_wait_to_add.push_back(child); }
    virtual void addChild(Object *child);
    virtual void removeChild(Object *child) { _children.erase(std::remove(_children.begin(), _children.end(), child), _children.end()); }

    // --GETTER AND SETTER
    std::string getName() { return _name; }
    void setName(std::string name) { _name = name; }
    ObjectType getObjectType() { return _type; }
    void setObjectType(ObjectType type) { _type = type; }
    void setActive(bool active) { _is_active = active; }
    bool getIsActive() { return _is_active; }
    void setIsDelete(bool delete_flag) { _is_delete = delete_flag; }
    bool getIsDelete() { return _is_delete; }
};
#endif // OBJECT_H