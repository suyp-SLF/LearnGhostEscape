#include "hud_button.h"

HUDButton *HUDButton::addHUDButtonChild(Object *parent, const glm::vec2 &pos, const std::string &path_normal, const std::string &path_hover, const std::string &path_press, float scale, Anchor anchor)
{
    HUDButton *button = new HUDButton();
    button->setRenderPosition(pos);
    button->_normal_sprite = Sprite::addSpriteChild(button, path_normal, scale, anchor);
    button->_hover_sprite = Sprite::addSpriteChild(button, path_hover, scale, anchor);
    button->_press_sprite = Sprite::addSpriteChild(button, path_press, scale, anchor);
    button->_hover_sprite->setActive(false);
    button->_press_sprite->setActive(false);
    button->init();
    if (parent) parent->addChild(button);
    return button;
}

void HUDButton::init()
{
    ObjectScreen::init();
    _rect.position = getRenderPosition() + _normal_sprite->getOffset();;
    _rect.size = _normal_sprite->getSize();
}

void HUDButton::update(float dt)
{
    ObjectScreen::update(dt);
    checkHover();
    checkState();
}

bool HUDButton::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_LEFT && _is_hover) {
            _is_press = true;
            return true;
        }
    }
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            // 只有按下和松开都在按钮内，才算一次完整触发
            _is_press = false;
            if (_is_hover) {
                _is_trigger = true;
                return true;
            }
        }
    }
    if(ObjectScreen::handleEvents(event)) return true;
    return false;
}

void HUDButton::checkState()
{
    // 1. 确定当前应该处于什么状态
    State next_state = State::NORMAL;
    if (_is_hover) {
        next_state = _is_press ? State::PRESS : State::HOVER;
    }

    // 2. 只有当状态发生【改变】时才执行逻辑
    if (next_state != _current_state) {
        
        // --- 核心逻辑：触发悬停音效 ---
        if (next_state == State::HOVER && _current_state == State::NORMAL) {
            // 当从 NORMAL 变成 HOVER 的瞬间播放
            _game.playSoundEffect("assets/sound/UI_button12.wav"); 
        }
        if( next_state == State::PRESS && _current_state == State::HOVER) {
            // 当从 HOVER 变成 PRESS 的瞬间播放
            _game.playSoundEffect("assets/sound/UI_button08.wav");
        }
        // ---------------------------

        _current_state = next_state;

        // 更新显示
        _normal_sprite->setActive(_current_state == State::NORMAL);
        _hover_sprite->setActive(_current_state == State::HOVER);
        _press_sprite->setActive(_current_state == State::PRESS);
    }
}

void HUDButton::checkHover()
{
    // 如果按钮会移动，必须每帧更新检测矩形的位置
    //_rect.position = getRenderPosition() + _normal_sprite->getOffset();
    //_rect.size = _normal_sprite->getSize();

    // 更新布尔值，供 checkState 使用
    _is_hover = _game.isMouseInRect(_rect);
    //SDL_Log(_is_hover ? "hover" : "not hover");
}

bool HUDButton::getIsTrigger()
{
    if (_is_trigger) {
        _is_trigger = false; // 消费掉这个触发信号
        return true;
    }
    return false; // 必须明确返回 false
}
