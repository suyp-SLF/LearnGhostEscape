#include "button_state_hover.h"
#include "button_state_normal.h"
#include "button_state_press.h"

void ButtonStateHover::onEnter()
{
    _parent->getHoverSprite()->setActive(true);
}

void ButtonStateHover::onExit()
{
    _parent->getHoverSprite()->setActive(false);
}

bool ButtonStateHover::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_MOTION)
    {
        RectData rect;
        rect.position = _parent->getRenderPosition() + _parent->getHoverSprite()->getOffset();
        rect.size = _parent->getHoverSprite()->getSize();
        if (!Game::getInstance().isMouseInRect(rect)) 
        {
            _parent->changeState(new ButtonStateNormal());
            return true;
        }
    }
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            _parent->changeState(new ButtonStatePress());
            return true;
        }
    }
    return false;
}
