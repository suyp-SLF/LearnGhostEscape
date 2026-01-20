#include "ui_mouse.h"

void UIMouse::update(float dt)
{
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

UIMouse *UIMouse::addUIMouseChild(Object *parent, const std::string &normal1, const std::string &normal2, float scale, Anchor anchor)
{
    auto ui_mouse = new UIMouse();
    ui_mouse->init();
    ui_mouse->_normal1 = Sprite::addSpriteChild(ui_mouse, normal1, 1.f, Anchor::CENTER);
    ui_mouse->_normal2 = Sprite::addSpriteChild(ui_mouse, normal2, 1.f, Anchor::CENTER);
    if (parent) parent->addChild(ui_mouse);
    return ui_mouse;
}
