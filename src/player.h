#ifndef PLAYER_H
#define PLAYER_H

#include "core/actor.h"
#include "affiliate/sprite_anim.h"
#include "world/effect.h"
#include "weapon_thunder.h"

class Player : public Actor 
{
private:
    SpriteAnim *_sprite_idle = nullptr;
    SpriteAnim *_sprite_run = nullptr;
    Effect *_effect = nullptr;
    WeaponThunder *_weapon_thunder = nullptr;
public:
    virtual void init() override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    void keyboardControl();
    void syncCamera();
    void checkState();
    void checkIsDead();
};
#endif // PLAYER_H