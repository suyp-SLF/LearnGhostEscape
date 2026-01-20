#ifndef SPELL_H
#define SPELL_H

#include "../core/object_world.h"
#include "../affiliate/sprite_anim.h"

class Spell : public ObjectWorld
{
protected:
    SpriteAnim *_anim = nullptr;
    float _damage = 50.f;

public:
    virtual void update(float dt) override;
    void setAnim(SpriteAnim *anim) { _anim = anim; };
private:
    void attack();
};
#endif // SPELL_H