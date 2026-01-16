#include "object.h"

void Object::handleEvents(SDL_Event &event)
{
    for (auto &child : _children)
    {
        child->handleEvents(event);
    }
}

void Object::update(float dt)
{
    for (auto &child : _children)
    {
        child->update(dt);
    }
}

void Object::render()
{
    for (auto &child : _children)
    {
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
