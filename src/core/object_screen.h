#ifndef OBJECT_SCREEN_H
#define OBJECT_SCREEN_H

#include "object.h"

class ObjectScreen : public Object
{
protected:
    glm::vec2 _render_position = glm::vec2(0, 0); // 屏幕坐标
    virtual void init() override { _type = ObjectType::OBJECT_SCREEN; };

public:
    // GETTER AND SETTER
    virtual glm::vec2 getPosition() { glm::vec2(0, 0); }
    glm::vec2 getRenderPosition() { return _render_position; }
    virtual void setRenderPosition(const glm::vec2 render_position) { _render_position = render_position; }
    
};
#endif // OBJECT_SCREEN_H