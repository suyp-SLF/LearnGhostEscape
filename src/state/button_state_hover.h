#ifndef BUTTON_STATE_HOVER_H
#define BUTTON_STATE_HOVER_H
#include "button_state.h"
class ButtonStateHover : public ButtonState
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual bool handleEvents(SDL_Event& event);
};
#endif // BUTTON_STATE_HOVER_H