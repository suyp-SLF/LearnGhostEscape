#ifndef TEXT_LABEL_H
#define TEXT_LABEL_H

#include <string>
#include "../core/object_affiliate.h"

class TextLabel : public ObjectAffiliate
{
protected:
    TTF_Text *_ttf_text = nullptr;
    std::string _font_path;
    int _font_size = 12;

public:
    virtual void init() override; // init ttf_text
    virtual void render() override; // render ttf_text
    virtual void clean() override; // clean ttf_text
    static TextLabel *addTextLabelChild(
        ObjectScreen *parent,
        const std::string &text,
        const std::string &font_path,
        int font_size,
        Anchor anchor = Anchor::CENTER);
    // GETTER AND SETTER
    void setFontPath(const std::string &font_path);
    void setFontSize(int font_size);
    void setText(const std::string &text);
    void setFont(const std::string &font_path, int font_size);
    std::string getText() const;

private:
    void updateSize(); // 根据文字决定大小
};
#endif // TEXT_LABEL_H
