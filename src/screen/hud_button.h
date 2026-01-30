#ifndef HUD_BUTTON_H
#define HUD_BUTTON_H

#include "../core/object_screen.h"
#include "../affiliate/sprite.h"
class HUDButton : public ObjectScreen
{
enum class State
{
    NORMAL,
    HOVER,
    PRESS
};
protected:
    Sprite *_normal_sprite = nullptr;
    Sprite *_hover_sprite = nullptr;
    Sprite *_press_sprite = nullptr;
    Sprite *_current_sprite = nullptr;

    State _current_state = State::NORMAL;

    RectData _rect;

    bool _is_hover = false;
    bool _is_press = false;
    bool _is_trigger = false;

public:
    static HUDButton *addHUDButtonChild(
        Object *parent,
        const glm::vec2 &pos,
        const std::string &path_normal,
        const std::string &path_hover,
        const std::string &path_press,
        float scale = 1.f,
        Anchor anchor = Anchor::CENTER);

    virtual void init() override;
    virtual void update(float dt) override;
    virtual bool handleEvents(SDL_Event &event) override; // HANDLE EVENT
    void checkState();
    void checkHover();
    // GETTER AND SETTER
    Sprite *getNormalSprite() const { return _normal_sprite; }
    Sprite *getHoverSprite() const { return _hover_sprite; }
    Sprite *getPressSprite() const { return _press_sprite; }
    bool getIsHover() const { return _is_hover; }
    bool getIsPress() const { return _is_press; }
    bool getIsTrigger();
    void setIsHover(bool is_hover) { _is_hover = is_hover; }
    void setIsPress(bool is_press) { _is_press = is_press; }
    void setIsTrigger(bool is_trigger) { _is_trigger = is_trigger; }
};
#endif // HUD_BUTTON_H