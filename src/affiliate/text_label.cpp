#include "text_label.h"

void TextLabel::init()
{
    ObjectAffiliate::init();
}

void TextLabel::render()
{
    ObjectAffiliate::render();
    auto position = _parent->getRenderPosition() + _offset;
    TTF_DrawRendererText(_ttf_text, position.x, position.y);
}

void TextLabel::clean()
{
    if (!_ttf_text)
        return;
    // 删除TTFText
    TTF_DestroyText(_ttf_text);
}

TextLabel *TextLabel::addTextLabelChild(ObjectScreen *parent, const std::string &text, const std::string &font_path, int font_size, Anchor anchor)
{
    auto text_label = new TextLabel();
    text_label->setFont(font_path, font_size);
    text_label->init();
    text_label->setText(text);
    text_label->setAnchor(anchor);
    text_label->updateSize();
    if (parent)
    {
        parent->safeAddChild(text_label);
        text_label->setParent(parent);
    }
    return text_label;
}

void TextLabel::setFontPath(const std::string &font_path)
{
    _font_path = font_path;
    auto font = _game.getAssetStore()->getFont(_font_path, _font_size);

    TTF_SetTextFont(_ttf_text, font);
}

void TextLabel::setFontSize(int font_size)
{
    _font_size = font_size;
    auto font = _game.getAssetStore()->getFont(_font_path, _font_size);
    TTF_SetTextFont(_ttf_text, font);
}

void TextLabel::setText(const std::string &text)
{
    TTF_SetTextString(_ttf_text, text.c_str(), 0);
}

void TextLabel::setFont(const std::string &font_path, int font_size)
{
    _font_path = font_path;
    _font_size = font_size;
    auto font = _game.getAssetStore()->getFont(font_path, _font_size);
    TTF_SetTextFont(_ttf_text, font);
    _ttf_text = _game.createTTFText("", _font_path, _font_size);
}

std::string TextLabel::getText() const
{
    return _ttf_text->text;
}

void TextLabel::updateSize()
{
    glm::ivec2 size;
    TTF_GetTextSize(_ttf_text, &size.x, &size.y);
    setSize(size);
}