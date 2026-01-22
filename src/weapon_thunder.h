#ifndef WEAPON_THUNDER_H
#define WEAPON_THUNDER_H

#include "raw/weapon.h"

class WeaponThunder : public Weapon
{
public:
    virtual void handleEvents(SDL_Event &event);
}

#endif // WEAPON_THUNDER_H