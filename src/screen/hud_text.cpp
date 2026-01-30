#include "hud_text.h"

HUDText *HUDText::addHUDTextChild(
    Object *parent,
    const std::string &text,
    glm::vec2 render_position,
    glm::vec2 size,
    const std::string &font_path,
    int font_size,
    const std::string &bg_path,
    Anchor anchor)
{
    HUDText *hud_text = new HUDText();
    hud_text->init();
    hud_text->setRenderPosition(render_position);
    hud_text->setSpriteBg(Sprite::addSpriteChild(hud_text, bg_path, 1.f, anchor));
    hud_text->setTextLabel(TextLabel::addTextLabelChild(hud_text, text, font_path, font_size, anchor));
    hud_text->setBgSizeByText(20.f);
    if (parent)
    {
        parent->addChild(hud_text);
    }
    return hud_text;
}

void HUDText::setSize(const glm::vec2 &size)
{
    _size = size;
    _sprite_bg->setSize(size);
}

void HUDText::setBackground(const std::string &path)
{
    if (_sprite_bg)
    {
        _sprite_bg->setTexture(path);
    }
    else
    {
        _sprite_bg = Sprite::addSpriteChild(this, path, 1.f, Anchor::CENTER);
    }
}

void HUDText::setBgSizeByText(float margin)
{
    auto text_size = _text_label->getSize();
    setSize(text_size + glm::vec2(margin * 2));
}
