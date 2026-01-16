#ifndef OBJECT_SCREEN_H
#define OBJECT_SCREEN_H

#include "object.h"

class ObjectScreen : public Object
{
protected:
    glm::vec2 _render_position = glm::vec2(0, 0);   //屏幕坐标

public:
    // getter and setter
    glm::vec2 getRenderPosition() { return _render_position; }
    virtual void setRenderPosition(const glm::vec2 render_position) { _render_position = render_position; }
};
#endif // OBJECT_SCREEN_H