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
    _render_position = _game.getCurrentScene()->worldToScreen(_position);
}

void ObjectWorld::setPosition(glm::vec2 position)
{
    _position = position;
    _render_position = _game.getCurrentScene()->worldToScreen(position);
}

void ObjectWorld::setRenderPosition(const glm::vec2 render_position)
{
    _render_position = render_position;
    _position = _game.getCurrentScene()->screenToWorld(render_position);
}
