#ifndef ACTOR_H
#define ACTOR_H

#include "object_world.h"
#include "../affiliate/affiliate_bar.h"

class Stats;
class Actor : public ObjectWorld
{

protected:
    Stats* _stats = nullptr;
    AffiliateBar* _health_bar = nullptr;
    glm::vec2 _velocity = glm::vec2(0);
    float _max_speed = 100;

    bool _is_alive = true;
    bool _is_invisible = false;
    
public:
    virtual void update(float dt) override;

    void move(float dt);
    // getter and setter
    void setVelocity(glm::vec2 velocity) { _velocity = velocity; };
    glm::vec2 getVelocity() { return _velocity; };

    void setMaxSpeed(float max_speed) { _max_speed = max_speed; };
    float getMaxSpeed() { return _max_speed; };

    void setStats(Stats* stats) { _stats = stats; };
    Stats* getStats() { return _stats; };

    void setHealthBar(AffiliateBar* health_bar) { _health_bar = health_bar; };
    AffiliateBar* getHealthBar() { return _health_bar; };

    void getIsAlive();
    void isInvisible();
    void takeDamage(int damage);
private:
    void updateHealthBar();
};
#endif // ACTOR_H