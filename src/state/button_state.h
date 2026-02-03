#ifndef BUTTON_STATE_H
#define BUTTON_STATE_H

#include "../core/object.h"
#include "../screen/hud_button.h"
/**
 * State Transition Matrix:
 * --------------------------------------------
 * Current State | Event        | Target State  
 * --------------------------------------------
 * Normal        | MouseHover   | HOVER
 * Hover         | MouseOut     | NORMAL
 * Hover         | MouseDown    | PRESS
 * Press         | MouseUp      | NORMAL
 * --------------------------------------------
 */
class ButtonState : public Object
{
protected:
    HUDButton *_parent = nullptr;

public:
    virtual void onEnter() = 0;
    virtual void onExit() = 0;

    //GETTER
    HUDButton *getParent() { return _parent; }
    //SETTER
    void setParent(HUDButton *parent) { _parent = parent; }
};
#endif // BUTTON_STATE_H