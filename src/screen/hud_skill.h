#ifndef HUD_SKILL_H
#define HUD_SKILL_H

#include "../core/object_screen.h"

#include <string>

class Sprite;
class HUDSkill : public ObjectScreen
{
protected:
    Sprite *_icon = nullptr;
    float _percentage = 1.f;

public:
    static HUDSkill *addHudSkillChild(Object *parent, const std::string &file_path, glm::vec2 position, float scale, Anchor anchor = Anchor::CENTER);
    virtual void render() override;
    // GETTER AND SETTER
    Sprite *getIcon() { return _icon; }
    void setIcon(Sprite *icon) { _icon = icon; }
    float getPercentage() { return _percentage; }
    void setPercentage(float percentage);
};
#endif // HUD_SKILL_H