#ifndef WEAPON_H
#define WEAPON_H

#include "../core/object.h"
class Spell;
class Actor;
class Weapon : public Object
{
protected:
    Actor* _parent = nullptr;
    Spell* _spell = nullptr;
    float _cool_down_timer = 0.f;
    float _cool_down = 1.f;
    float _mana_cost = 0.f;
    
public:
    virtual void update(float dt) override;

    void attack(glm::vec2 position, Spell* spell);
    bool canAttack();
    // GETTER AND SETTER
    Spell* getSpell() const { return _spell;}
    void setSpell(Spell* spell) { _spell = spell;}
    float getCoolDown() const { return _cool_down;}
    void setCoolDown(float coolDown) { _cool_down = coolDown;}
    float getManaCost() const { return _mana_cost;}
    void setManaCost(float manaCost) { _mana_cost = manaCost;}
    float getCoolDownTimer() const { return _cool_down_timer;}
    void setCoolDownTimer(float coolDownTimer) { _cool_down_timer = coolDownTimer;}

    void setParent(Actor* parent) { _parent = parent;}
};
#endif // WEAPON_H