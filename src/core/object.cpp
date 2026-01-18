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
