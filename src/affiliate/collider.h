#ifndef COLLIDER_H
#define COLLIDER_H

#include "../core/object_affiliate.h"

class Collider : public ObjectAffiliate
{
private:
    enum class Shape
    {
        CIRCLE,
        RECTANGLE
    };
    Shape _shape = Shape::CIRCLE;
public:

    virtual void render();

    static Collider* addColliderChild(ObjectScreen* parent, glm::vec2 size, Anchor anchor = Anchor::CENTER, Shape type = Shape::CIRCLE);
    bool isColliding(Collider* other);

    // GETTER AND SETTER
    Shape getShape() const { return _shape; }
    void setShape(Shape shape) { _shape = shape; }
    
};
#endif // COLLIDER_H