#ifndef OBJECT_WORLD_H
#define OBJECT_WORLD_H

#include "object_screen.h"
#include "../affiliate/collider.h"

class ObjectWorld : public ObjectScreen
{
protected:
    glm::vec2 _position = glm::vec2(0, 0); // 世界坐标
    Collider *_collider = nullptr;
public:
    virtual void init() override;
    virtual void update(float dt) override;

    // GETTER
    virtual glm::vec2 getPosition() override { return _position; }
    virtual glm::vec2 getRenderPosition() override;
    virtual Collider *getCollider() { return _collider; }
    // SETTER
    void setPosition(glm::vec2 position);
    virtual void setRenderPosition(const glm::vec2 render_position) override;
    virtual void setCollider(Collider *collider) { _collider = collider; }
};
#endif // OBJECT_WORLD_H