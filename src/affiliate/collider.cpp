#include "collider.h"
#include "sprite.h"

void Collider::render()
{
    ObjectAffiliate::render();
    #ifdef DEBUG_MDOE
    //输出_parent->getRenderPosition()
    // 调试模式，渲染碰撞箱
    auto texture = Texture("assets/UI/circle.png");
    _game.drawImage(texture, _parent->getRenderPosition() + _offset, _size, .3f);
    #endif
}

Collider *Collider::addColliderChild(ObjectScreen *parent, glm::vec2 size, Anchor anchor, Shape shape)
{
    Collider *collider = new Collider();
    collider->init();
    collider->setAnchor(anchor);
    collider->setParent(parent);
    collider->setSize(size);
    collider->setShape(shape);
    parent->safeAddChild(collider);
    return collider;
}

bool Collider::isColliding(Collider *other)
{
    if (!other) return false;
    if (_shape == Shape::CIRCLE && other->_shape == Shape::CIRCLE)
    {
        auto point1 = _parent->getPosition() + _offset + _size / 2.f;
        auto point2 = other->_parent->getPosition() + other->_offset + other->_size / 2.f;
        return glm::length(point1 - point2) < (_size.x + other->_size.x) / 2.f;
    }
    return false;
}
