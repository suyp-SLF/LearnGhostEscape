#ifndef HUD_TEXT_H
#define HUD_TEXT_H
#include "../core/object_screen.h"
#include "../affiliate/text_label.h"
#include "../affiliate/sprite.h"

class HUDText : public ObjectScreen
{
protected:
    TextLabel *_text_label = nullptr;
    Sprite *_sprite_bg = nullptr;
    glm::vec2 _size = glm::vec2(0); //HUD的大小
public:
    static HUDText *addHUDTextChild(
        Object *parent, 
        const std::string& text, 
        glm::vec2 render_position,
        glm::vec2 size,
        const std::string& font_path = "assets/font/VonwaonBitmap-16px.ttf", 
        int font_size = 16, 
        const std::string& bg_path = "assets/UI/Textfield_01.png", 
        Anchor anchor = Anchor::CENTER);
    // GETTER AND SETTER
    TextLabel *getTextLabel() { return _text_label; }
    Sprite *getSpriteBg() { return _sprite_bg; }
    void setTextLabel(TextLabel *text_label) { this->_text_label = text_label; }
    void setSpriteBg(Sprite *sprite_bg) { this->_sprite_bg = sprite_bg; }
    void setText(const std::string& text) { _text_label->setText(text); }
    void setSize(const glm::vec2& size);
    std::string getText() const { return _text_label->getText(); }
    void setBackground(const std::string& path);
};
#endif // HUD_TEXT_H