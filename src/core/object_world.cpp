#include "object_world.h"

#include "scene.h"

void ObjectWorld::init()
{
    ObjectScreen::init();
    _type = ObjectType::OBJECT_WORLD;
}

void ObjectWorld::update(float dt)
{
    ObjectScreen::update(dt);
}

glm::vec2 ObjectWorld::getRenderPosition()
{
    _render_position = Game::getInstance().getCurrentScene()->worldToScreen(_position);
    return _render_position;
}

void ObjectWorld::setPosition(glm::vec2 position)
{
    _position = position;
    _render_position = Game::getInstance().getCurrentScene()->worldToScreen(position);
}

void ObjectWorld::setRenderPosition(const glm::vec2 render_position)
{
    _render_position = render_position;
    _position = Game::getInstance().getCurrentScene()->screenToWorld(render_position);
}
