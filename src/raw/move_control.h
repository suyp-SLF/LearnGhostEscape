#ifndef MOVE_CONTROL_H
#define MOVE_CONTROL_H

#include "../core/object.h"
class MoveControl : public Object
{
protected:
    bool _is_up = false;
    bool _is_down = false;
    bool _is_left = false;
    bool _is_right = false;

public:
    // GETTER
    bool isUp() { return _is_up; }
    bool isDown() { return _is_down; }
    bool isLeft() { return _is_left; }
    bool isRight() { return _is_right; }
};
#endif // MOVE_CONTROL_H