#ifndef TEXT_LABEL_H
#define TEXT_LABEL_H

#include <string>
#include "../core/object_affiliate.h"

class TextLabel : public ObjectAffiliate
{
protected:
    TTF_Text* _ttf_text = nullptr;
    std::string _font_path;
    int _font_size;
public:
    // GETTER AND SETTER
    void setFontPath(const std::string& font_path);
    void setFontSize(int font_size);
    void setText(const std::string& text);
    std::string getText() const;
};
#endif // TEXT_LABEL_H
