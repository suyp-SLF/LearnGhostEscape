#ifndef ACTOR_H
#define ACTOR_H

#include "object_world.h"

class Stats;
class Actor : public ObjectWorld
{

protected:
    Stats* _stats = nullptr;
    glm::vec2 _velocity = glm::vec2(0);
    float _max_speed = 100;

    bool _is_alive = true;
    bool _is_invisible = false;
    
public:
    void move(float dt);

    // getter and setter
    void setVelocity(glm::vec2 velocity) { _velocity = velocity; };
    glm::vec2 getVelocity() { return _velocity; };

    void setMaxSpeed(float max_speed) { _max_speed = max_speed; };
    float getMaxSpeed() { return _max_speed; };

    void setStats(Stats* stats) { _stats = stats; };
    Stats* getStats() { return _stats; };

    void getIsAlive();
    void isInvisible();
    void takeDamage(int damage);
};
#endif // ACTOR_H