#ifndef SPAWNER_H
#define SPAWNER_H

#include "core/object.h"
class Player;
class Spawner : public Object
{
protected:
    Player* _target = nullptr;

    float _spawn_timer = 0.0f;
    float _spawn_time = 8.f;

    int _spawn_count = 5;

public:
    virtual void update(float dt) override;

    // GETTER AND SETTER
    void setTarget(Player* target) {_target = target;}
    Player* getTarget() {return _target;}

};
#endif // SPAWNER_H