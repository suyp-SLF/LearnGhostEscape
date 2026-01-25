#include "hud_skill.h"
#include "../affiliate/sprite.h"

HUDSkill *HUDSkill::addHudSkillChild(Object *parent, const std::string &file_path, glm::vec2 position, float scale, Anchor anchor)
{
    auto hud_skill = new HUDSkill();
    hud_skill->init();
    hud_skill->_icon = Sprite::addSpriteChild(hud_skill, file_path, scale, anchor, glm::vec3(.3f));
    hud_skill->setRenderPosition(position);
    if(parent) parent->safeAddChild(hud_skill);
    return hud_skill;
}

void HUDSkill::render()
{
    _game.drawImage(_icon->getTexture(),getRenderPosition() + _icon->getOffset(), _icon->getSize(), glm::vec2(1.f, 1.f), 1.f);
    ObjectScreen::render();
}

void HUDSkill::setPercentage(float percentage)
{
    percentage = glm::clamp(percentage, 0.f, 1.f);
    _percentage = percentage;
    if(_icon){
        _icon->setPercentage(glm::vec2(1.f, 1 - _percentage));
    }
}
