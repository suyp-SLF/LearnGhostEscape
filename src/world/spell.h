#ifndef SPELL_H
#define SPELL_H

#include "../core/object_world.h"
#include "../affiliate/sprite_anim.h"

class Spell : public ObjectWorld
{
protected:
    SpriteAnim *_anim = nullptr;
    float _damage = 50.f;

    std::string _texture_path;
    float _scale;
public:
    static Spell *addSpellChild(Object *parent, const std::string& texture_path, glm::vec2 position, float damage, float scale = 1.f, Anchor anchor = Anchor::CENTER);
    virtual void update(float dt) override;
    Spell* clone();

    // GETTER AND SETTER
    void setAnim(SpriteAnim *anim) { _anim = anim; };
    SpriteAnim *getAnim() { return _anim; };
    void setDamage(float damage) { _damage = damage; };
    float getDamage() { return _damage; };
private:
    void attack();
};
#endif // SPELL_H