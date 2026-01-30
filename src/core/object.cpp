#include "object.h"
#include "object_screen.h"

#include <cxxabi.h>
void Object::init()
{
    int status;
    // 获取运行时的子类真实类名
    char *demangled = abi::__cxa_demangle(typeid(*this).name(), nullptr, nullptr, &status);

    if (status == 0)
    {
        _name = demangled; // 拿到如 "Game::Player" 这种全名
        std::free(demangled);
    }
    else
    {
        _name = typeid(*this).name();
    }
}
bool Object::handleEvents(SDL_Event &event)
{
    if (!_is_active){
        return false;
    }
    for (auto &child : _children)
    {
        if (!child->_is_active)
        {
            continue;
        }
        if (!_is_pause || child->getObjectType() == ObjectType::OBJECT_SCREEN)
        {
            if(child->handleEvents(event)) return true;
        }
    }
    return false;
}

void Object::update(float dt)
{
    for (auto &child : _children_wait_to_add)
    {
        _children.push_back(child);
    }
    _children_wait_to_add.clear();

    if (!_is_active)
        return;
    for (auto it = _children.begin(); it != _children.end();)
    {
        auto child = *it;
        if (child->_is_delete)
        {
            child->clean();
            it = _children.erase(it);
            SDL_Log("删除子节点：%s", _name.c_str());
            delete child;
            child = nullptr;
        }
        else if (child->_is_active)
        {
            if (!_is_pause || child->getObjectType() == ObjectType::OBJECT_SCREEN)
            {
                (*it)->update(dt);
            }
            ++it;
        }
        else
        {
            ++it;
        }
    }
}

void Object::render()
{
    // 1. 提取所有子对象的名称并拼接
    std::string renderOrder = this->_name + " Order: ";
    if (!_is_active)
        return;
    for (auto &child : _children)
    {
        renderOrder += child->_name + " ";
        if (!child->_is_active)
            continue;
        child->render();
    }

#ifdef DEBUGMODE
    SDL_Log(renderOrder.c_str());
#endif
}

void Object::clean()
{
    for (auto &child : _children)
    {
        child->clean();
    }
    _children.clear();
}

void Object::addChild(Object *child)
{
    // 注意这里是 *child，获取指针指向的实际对象
    SDL_Log("添加子节点：%s", _name.c_str());
    _children.push_back(child);
}