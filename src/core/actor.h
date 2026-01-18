#ifndef ACTOR_H
#define ACTOR_H

#include "object_world.h"

class Actor : public ObjectWorld
{

protected:
    glm::vec2 _velocity = glm::vec2(0);
    float _max_speed = 100;
    
public:
    void move(float dt);

    // getter and setter
    void setVelocity(glm::vec2 velocity) { _velocity = velocity; };
    glm::vec2 getVelocity() { return _velocity; };

    void setMaxSpeed(float max_speed) { _max_speed = max_speed; };
    float getMaxSpeed() { return _max_speed; };
};
#endif // ACTOR_H