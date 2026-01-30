#include "ui_mouse.h"

void UIMouse::update(float dt)
{
    // ... 原有逻辑 ...
    //glm::vec2 pos = getRenderPosition();
    //SDL_Log("Mouse Pos: %f, %f", pos.x, pos.y); // 取消注释查看坐标是否正常
    //setRenderPosition(pos);
    _timer += dt;
    if (_timer < 0.5f)
    {
        _normal1->setActive(true);
        _normal2->setActive(false);
    }
    else if (_timer < 1.0f)
    {
        _normal1->setActive(false);
        _normal2->setActive(true);
    }
    else
    {
        _timer = 0.0f;
    }
    setRenderPosition(_game.getMousePosition()); // update position
}

void UIMouse::render()
{
    ObjectScreen::render();
    //SDL_Log("Mouse Pos: %f, %f", getRenderPosition().x, getRenderPosition().y); // 取消注释查看坐标是否正常
    _game.drawBoundary(getRenderPosition(), getRenderPosition(), 5.0f, {1.0, 0.0, 0.0, 1.0});
}

UIMouse *UIMouse::addUIMouseChild(Object *parent, const std::string &normal1, const std::string &normal2, float scale, Anchor anchor)
{
    auto ui_mouse = new UIMouse();
    ui_mouse->init();
    ui_mouse->_normal1 = Sprite::addSpriteChild(ui_mouse, normal1, scale, anchor);
    ui_mouse->_normal2 = Sprite::addSpriteChild(ui_mouse, normal2, scale, anchor);
    // 强制初始化状态，防止第一帧两个都消失
    ui_mouse->_normal1->setActive(true);
    ui_mouse->_normal2->setActive(false);
    ui_mouse->_timer = 0.0f;
    if (parent) parent->safeAddChild(ui_mouse);
    return ui_mouse;
}
