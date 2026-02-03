#include "hud_button.h"
#include "../state/button_state.h"
#include "../state/button_state_normal.h"

HUDButton *HUDButton::addHUDButtonChild(Object *parent, const glm::vec2 &pos, const std::string &path_normal, const std::string &path_hover, const std::string &path_press, float scale, Anchor anchor)
{
    HUDButton *button = new HUDButton();
    button->setRenderPosition(pos);
    button->_normal_sprite = Sprite::addSpriteChild(button, path_normal, scale, anchor);
    button->_hover_sprite = Sprite::addSpriteChild(button, path_hover, scale, anchor);
    button->_press_sprite = Sprite::addSpriteChild(button, path_press, scale, anchor);
    button->_hover_sprite->setActive(false);
    button->_press_sprite->setActive(false);
    button->changeState(new ButtonStateNormal()); // 默认状态
    button->init();
    if (parent)
        parent->addChild(button);
    return button;
}

void HUDButton::init()
{
    ObjectScreen::init();
    _rect.position = getRenderPosition() + _normal_sprite->getOffset();
    ;
    _rect.size = _normal_sprite->getSize();
}

void HUDButton::update(float dt)
{
    ObjectScreen::update(dt);
}

bool HUDButton::handleEvents(SDL_Event &event)
{
    ObjectScreen::handleEvents(event);
    return false;
}
void HUDButton::changeState(ButtonState *state)
{
    if (_state)
    {
        _state->onExit();
        _state->setIsDelete(true);
    }
    if (!state)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "HUDButton::changeState() state is nullptr");
        return;
    }
    _state = state;
    _state->init();
    _state->setParent(this);
    _state->onEnter();
    safeAddChild(_state);
}

bool HUDButton::getIsTrigger()
{
    if (_is_trigger)
    {
        _is_trigger = false; // 消费掉这个触发信号
        return true;
    }
    return false; // 必须明确返回 false
}

void HUDButton::setScale(float scale)
{
    _normal_sprite->setScale(scale);
    _hover_sprite->setScale(scale);
    _press_sprite->setScale(scale);
    _rect.position = getRenderPosition() + _normal_sprite->getOffset();
    ;
    _rect.size = _normal_sprite->getSize();
}
