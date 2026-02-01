#ifndef PLAYER_H
#define PLAYER_H

#include "core/actor.h"
#include "affiliate/sprite_anim.h"
#include "world/effect.h"
#include "weapon_thunder.h"
#include "raw/move_control.h"

class Player : public Actor
{
private:
    MoveControl *_move_control = nullptr;
    SpriteAnim *_sprite_idle = nullptr;
    SpriteAnim *_sprite_run = nullptr;
    Effect *_effect = nullptr;
    WeaponThunder *_weapon_thunder = nullptr;
    int _score = 0;

public:
    virtual void init() override;
    virtual bool handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    virtual int takeDamage(int damage) override;

    void setMoveControl(MoveControl *move_control);

    // GETTER AND SETTER
    int getScore() { return _score; }
    void setScore(int score) { _score = score; }
    //
    void addScore(int score) { _score += score; }

private:
    void moveControl();
    void syncCamera();
    void checkState();
    void checkIsDead();
};
#endif // PLAYER_H