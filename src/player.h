#ifndef PLAYER_H
#define PLAYER_H

#include "core/actor.h"
#include "affiliate/sprite_anim.h"

class Player : public Actor
{
private:
    SpriteAnim *_sprite_idle = nullptr;
    SpriteAnim *_sprite_run = nullptr;
public:
    virtual void init() override;
    virtual void handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    void keyboardControl();
    void syncCamera();
    void checkState();
};
#endif // PLAYER_H