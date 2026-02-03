#ifndef BUTTON_STATE_NORMAL_H
#define BUTTON_STATE_NORMAL_H
#include "button_state.h"
class ButtonStateNormal : public ButtonState
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual bool handleEvents(SDL_Event &event);
};
#endif // BUTTON_STATE_NORMAL_H