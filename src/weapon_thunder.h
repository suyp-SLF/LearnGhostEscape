#ifndef WEAPON_THUNDER_H
#define WEAPON_THUNDER_H

#include "raw/weapon.h"
#include "screen/hud_skill.h"

class WeaponThunder : public Weapon
{
protected:
    HUDSkill *_hud_skill = nullptr;

public:
    static WeaponThunder *addWeaponThunderChild(Actor *parent, float cool_down, float mana_cost);
    virtual void init() override;
    virtual void update(float dt) override;
    virtual void handleEvents(SDL_Event &event) override;
};
#endif // WEAPON_THUNDER_H