#ifndef MOVE_CONTROL_H
#define MOVE_CONTROL_H

#include "../core/object.h"
class Actor;
class MoveControl : public Object
{
protected:
    bool _is_up = false;
    bool _is_down = false;
    bool _is_left = false;
    bool _is_right = false;

    Actor *_parent = nullptr;
    float _max_speed = 500.0f;

public: 
    virtual void update(float dt) override;
    virtual bool handleEvents(SDL_Event &event) override;

    // GETTER
    bool isUp() { return _is_up; }
    bool isDown() { return _is_down; }
    bool isLeft() { return _is_left; }
    bool isRight() { return _is_right; }
    Actor *getParent() { return _parent; }
    float getMaxSpeed() { return _max_speed; }
    // SETTER
    void setParent(Actor *actor) { _parent = actor; }
    void setMaxSpeed(float speed) { _max_speed = speed; }
};
#endif // MOVE_CONTROL_H