#include "scene.h"
#include "object_world.h"
#include "object_screen.h"

bool Scene::handleEvents(SDL_Event &event)
{
    if (!_is_active)
    {
        return false;
    }
    for (auto &child : _children_world)
    {
        if (!child->getIsActive())
        {
            continue;
        }
        if (!_is_pause)
        {
            if (child->handleEvents(event))
                return true;
        }
    }
    for (auto &child : _children_screen)
    {
        if (!child->getIsActive())
        {
            continue;
        }
        if (child->handleEvents(event))
            return true;
    }
    if (Object::handleEvents(event))
        return true;
    return false;
}

void Scene::update(float dt)
{
    // 1. 同步待添加列表
    for (auto &child : _children_wait_to_add)
    {
        addChild(child);
    }
    _children_wait_to_add.clear();

    if (!_is_active)
        return;

    for (auto it = _children_world.begin(); it != _children_world.end();)
    {
        auto child = *it;
        if (child->getIsDelete())
        {
            child->clean();
            it = _children_world.erase(it);
            SDL_Log("删除子节点：%s", _name.c_str());
            delete child;
            child = nullptr;
        }
        else if (child->getIsActive())
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
    for (auto it = _children_screen.begin(); it != _children_screen.end();)
    {
        auto child = *it;
        if (child->getIsDelete())
        {
            child->clean();
            it = _children_screen.erase(it);
            SDL_Log("删除子节点：%s", _name.c_str());
            delete child;
            child = nullptr;
        }
        else if (child->getIsActive())
        {
            (*it)->update(dt);
            ++it;
        }
        else
        {
            ++it;
        }
    }
    Object::update(dt);
}

void Scene::render()
{
    // 打印调试信息
    if (!_is_active)
        return;
    std::string renderOrder = this->_name + " Order: ";
    for (auto &child : _children_world)
    {
        renderOrder += child->getName() + " ";
        if (!child->getIsActive())
            continue;
        child->render();
    }
    for (auto &child : _children_screen)
    {
        renderOrder += child->getName() + " ";
        if (!child->getIsActive())
            continue;
        child->render();
    }
    Object::render();
    _game.drawText("Children:" + std::to_string(_children.size()) +
                       " World:" + std::to_string(_children_world.size()) +
                       " Screen:" + std::to_string(_children_screen.size()),
                   glm::vec2(10.0f, 40.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
}

void Scene::clean()
{
    Object::clean(); // 这里已经删除了所有子节点内存！

    // 下面这些循环会访问已经被 delete 的内存！
    for (auto &child : _children_world)
    {
        child->clean(); // ❌ 报错：child 已经是野指针
    }
    _children_world.clear();

    for (auto &child : _children_screen)
    {
        child->clean(); // ❌ 报错：child 已经是野指针
    }
    _children_screen.clear();
}

void Scene::pause()
{
    _is_pause = true;
    _game.pauseMusic();
}

void Scene::resume()
{
    _is_pause = false;
    _game.resumeMusic();
}

void Scene::addChild(Object *child)
{
    if (!child)
        return;

    // --- 关键修改：所有对象必须进入基类列表 ---
    // 这样 Object::handleEvents(event) 才能递归找到它们
    // _children.push_back(child);

    switch (child->getObjectType())
    {
    case ObjectType::NONE:
        _children.push_back(child);
    case ObjectType::OBJECT_WORLD:
    case ObjectType::ENEMY:
        _children_world.push_back(static_cast<ObjectWorld *>(child));
        break;
    case ObjectType::OBJECT_SCREEN:
        _children_screen.push_back(static_cast<ObjectScreen *>(child));
        break;
    }
}
void Scene::removeChild(Object *child)
{
    switch (child->getObjectType())
    {
    case ObjectType::OBJECT_WORLD:
    case ObjectType::ENEMY:
        _children_world.erase(std::remove(_children_world.begin(), _children_world.end(), static_cast<ObjectWorld *>(child)), _children_world.end());
        break;
    case ObjectType::OBJECT_SCREEN:
        _children_screen.erase(std::remove(_children_screen.begin(), _children_screen.end(), static_cast<ObjectScreen *>(child)), _children_screen.end());
        break;
    default:
        _children.erase(std::remove(_children.begin(), _children.end(), child), _children.end());
        break;
    }
}
glm::vec2 Scene::worldToScreen(const glm::vec2 world_position) const
{
    return world_position - _camera_position;
}
glm::vec2 Scene::screenToWorld(const glm::vec2 screen_position) const
{
    return screen_position + _camera_position;
}
// 屏幕组件，因为分为屏幕以及世界坐标，所以需要两个
void Scene::setCameraPosition(const glm::vec2 camera_position)
{
    _camera_position = camera_position;
    // 限制摄像头的位置
    _camera_position = glm::clamp(
        _camera_position,
        glm::vec2(-30),
        _world_size - _game.getScreenSize() + glm::vec2(30));
}