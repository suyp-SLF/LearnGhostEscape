#include "scene.h"
#include "object_world.h"
#include "object_screen.h"

void Scene::handleEvents(SDL_Event &event)
{
    if (!_is_active)
        return;
    Object::handleEvents(event);
    for (auto &child : _children_screen)
    {
        if (!child->getIsActive())
            continue;
        child->handleEvents(event);
    }
    for (auto &child : _children_world)
    {
        child->handleEvents(event);
    }
}

void Scene::update(float dt)
{
    if (!_is_active)
        return;
    Object::update(dt);
    for (auto it = _children_world.begin(); it != _children_world.end();)
    {
        auto child = *it;
        if (child->getIsDelete())
        {
            it = _children_world.erase(it);
            child->clean();
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
    for (auto it = _children_screen.begin(); it != _children_screen.end();)
    {
        auto child = *it;
        if (child->getIsDelete())
        {
            it = _children_screen.erase(it);
            child->clean();
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
}

void Scene::render()
{
    if (!_is_active)
        return;
    Object::render();
    for (auto &child : _children_world)
    {
        if (!child->getIsActive())
            continue;
        child->render();
    }
    for (auto &child : _children_screen)
    {
        if (!child->getIsActive())
            continue;
        child->render();
    }
}

void Scene::clean()
{
    Object::clean();
    for (auto &child : _children_world)
    {
        child->clean();
    }
    _children_world.clear();
    for (auto &child : _children_screen)
    {
        child->clean();
    }
    _children_screen.clear();
}

void Scene::addChild(Object *child)
{
    switch (child->getType())
    {
    case ObjectType::OBJECT_WORLD:
    case ObjectType::ENEMY:
        _children_world.push_back(static_cast<ObjectWorld *>(child));
        break;
    case ObjectType::OBJECT_SCREEN:
        _children_screen.push_back(static_cast<ObjectScreen *>(child));
    default:
        _children.push_back(child);
        break;
    }
}

void Scene::removeChild(Object *child)
{
    switch (child->getType())
    {
    case ObjectType::OBJECT_WORLD:
    case ObjectType::ENEMY:
        _children_world.erase(std::remove(_children_world.begin(), _children_world.end(), static_cast<ObjectWorld *>(child)), _children_world.end());
        break;
    case ObjectType::OBJECT_SCREEN:
        _children_screen.erase(std::remove(_children_screen.begin(), _children_screen.end(), static_cast<ObjectScreen *>(child)), _children_screen.end());

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