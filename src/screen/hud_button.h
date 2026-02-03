#ifndef HUD_BUTTON_H
#define HUD_BUTTON_H

#include "../core/object_screen.h"
#include "../affiliate/sprite.h"

class ButtonState;
class HUDButton : public ObjectScreen
{
protected:
    Sprite *_normal_sprite = nullptr;
    Sprite *_hover_sprite = nullptr;
    Sprite *_press_sprite = nullptr;
    Sprite *_current_sprite = nullptr;

    ButtonState *_state = nullptr;

    RectDataEx _rect;

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
    
    void changeState(ButtonState *state);
    // GETTER
    Sprite *getNormalSprite() const { return _normal_sprite; }
    Sprite *getHoverSprite() const { return _hover_sprite; }
    Sprite *getPressSprite() const { return _press_sprite; }
    bool getIsTrigger();
    // SETTER
    void setIsTrigger(bool is_trigger) { _is_trigger = is_trigger; }
    void setScale(float scale);
};
#endif // HUD_BUTTON_H