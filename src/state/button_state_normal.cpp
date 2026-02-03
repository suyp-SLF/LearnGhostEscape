#include "button_state_normal.h"
#include "button_state_hover.h"

void ButtonStateNormal::onEnter()
{
    _parent->getNormalSprite()->setActive(true);
}

void ButtonStateNormal::onExit()
{
    _parent->getNormalSprite()->setActive(false);
}

bool ButtonStateNormal::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_MOTION)
    {
        RectData rect;
        rect.position = _parent->getRenderPosition() + _parent->getPressSprite()->getOffset();
        rect.size = _parent->getPressSprite()->getSize();
        if (Game::getInstance().isMouseInRect(rect))
        {
            _parent->changeState(new ButtonStateHover());
            return true;
        }
    }
    return false;
}
