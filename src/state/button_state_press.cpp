#include "button_state_press.h"
#include "button_state_normal.h"

void ButtonStatePress::onEnter()
{
    Game::getInstance().playSoundEffect("assets/sound/UI_button08.wav");
    _parent->getPressSprite()->setActive(true);
}

void ButtonStatePress::onExit()
{
    _parent->getPressSprite()->setActive(false);
}

bool ButtonStatePress::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            RectData rect;
            rect.position = _parent->getRenderPosition() + _parent->getHoverSprite()->getOffset();
            rect.size = _parent->getHoverSprite()->getSize();
            if (Game::getInstance().isMouseInRect(rect))
            {
                _parent->setIsTrigger(true);
                return true;
            }
            _parent->changeState(new ButtonStateNormal());
        }
    }
    return false;
}