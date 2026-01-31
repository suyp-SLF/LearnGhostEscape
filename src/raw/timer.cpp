#include "timer.h"

Timer *Timer::addTimerChild(Object *parent, float interval)
{
    Timer *timer = new Timer();
    timer->setActive(false);
    timer->_interval = interval;
    if(parent) parent->addChild(timer);
    return timer;
}

void Timer::update(float dt)
{
    Object::update(dt);
    _timer += dt;
    if(_timer >= _interval){
        _timer = 0;
        _is_timeout = true;
    }
}

bool Timer::timerOut()
{
    if(_is_timeout){
        _is_timeout = false;
        return true;
    }
    return false;
}
