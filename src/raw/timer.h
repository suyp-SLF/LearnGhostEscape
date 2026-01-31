#ifndef TIMER_H
#define TIMER_H

#include "../core/object.h"
class Timer : Object
{
protected:
    float _timer = .0f;
    float _interval = 3.0f;
    bool _is_timeout = false;

public:
    static Timer *addTimerChild(Object *parent, float interval = 3.f);

    virtual void update(float dt) override;
    void start() { _is_active = true; }
    void stop() { _is_active = false; }
    bool timerOut();

    // GETTER AND SETTER
    float getTimer() { return _timer; }
    void setTimer(float timer) { _timer = timer; }
    float getInterval() { return _interval; }
    void setInterval(float interval) { _interval = interval; }
};
#endif // TIMER_H