#ifndef OBJECT_WORLD_H
#define OBJECT_WORLD_H

#include "object_screen.h"

class ObjectWorld : public ObjectScreen
{
protected:
    glm::vec2 _position = glm::vec2(0, 0); // 世界坐标
public:

    virtual void update(float dt) override;

    // getter and setter
    glm::vec2 getPosition() { return _position; }
    void setPosition(glm::vec2 position);
    virtual void setRenderPosition(const glm::vec2 render_position) override;
};
#endif // OBJECT_WORLD_H