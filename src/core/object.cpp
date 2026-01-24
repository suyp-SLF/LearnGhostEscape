#include "object.h"

void Object::handleEvents(SDL_Event &event)
{
    if (!_is_active)
        return;
    for (auto &child : _children)
    {
        if (!child->_is_active)
            continue;
        child->handleEvents(event);
    }
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
            it = _children.erase(it);
            child->clean();
            delete child;
            child = nullptr;
        }
        else if (child->_is_active)
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

void Object::render()
{
    if (!_is_active)
        return;
    for (auto &child : _children)
    {
        if (!child->_is_active)
            continue;
        child->render();
    }
}

void Object::clean()
{
    for (auto &child : _children)
    {
        child->clean();
    }
    _children.clear();
}
