#include "text_label.h"

void TextLabel::setFontPath(const std::string &font_path)
{
}

void TextLabel::setFontSize(int font_size)
{
}

void TextLabel::setText(const std::string &text)
{
    TTF_SetTextString(_ttf_text, text.c_str(), 0);
}

std::string TextLabel::getText() const
{
    return _ttf_text->text;
}
