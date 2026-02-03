#ifndef WEAPON_H
#define WEAPON_H

#include "../core/object.h"
#include "../raw/spell_creator.h"

class Spell;
class Actor;
class HUDSkill;
class Weapon : public Object
{
protected:
    Actor *_parent = nullptr;
    Spell *_spell_prototype = nullptr;
    SDL_MouseButtonFlags _trigger_button = SDL_BUTTON_LEFT;
    HUDSkill* _hud_skill = nullptr;
    std::string _sound_effect = "assets/sound/big-thunder.mp3";
    float _cool_down_timer = 0.f;
    float _cool_down = 1.f;
    float _mana_cost = 0.f;

public:
    static Weapon *addWeaponChild(Actor *parent, float cool_down, float mana_cost);
    virtual bool handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;

    void attack(glm::vec2 position);
    bool canAttack();
    // GETTER
    float getCoolDown() const { return _cool_down; }
    float getManaCost() const { return _mana_cost; }
    float getCoolDownTimer() const { return _cool_down_timer; }

    // SETTER
    void setManaCost(float manaCost) { _mana_cost = manaCost; }
    void setCoolDownTimer(float coolDownTimer) { _cool_down_timer = coolDownTimer; }
    void setCoolDown(float coolDown) { _cool_down = coolDown; }
    void setParent(Actor *parent) { _parent = parent; }
    void setSpellPrototype(Spell *spellPrototype) { _spell_prototype = spellPrototype; }
    void setTriggerButton(SDL_MouseButtonFlags triggerButton) { _trigger_button = triggerButton; }
    void setHudSkill(HUDSkill* hudSkill) { _hud_skill = hudSkill; }
    void setSoundEffect(std::string soundEffect) { _sound_effect = soundEffect; }
};
#endif // WEAPON_H