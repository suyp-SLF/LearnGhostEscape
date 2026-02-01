#ifndef EFFECT_H
#define EFFECT_H

#include "../core/object_world.h"
#include "../affiliate/sprite_anim.h"

class Effect : public ObjectWorld
{
    SpriteAnim *_anim = nullptr;
    ObjectWorld *_next_object = nullptr;
public:
    static Effect *addEffectChild(Object *parent, const std::string& file_path, glm::vec2 position, float scale = 1.f, ObjectWorld *next_object = nullptr);
    virtual void update(float dt) override;
    virtual void clean() override;
    
    void checkFinish();

    // GETTER AND SETTER
    SpriteAnim *getAnim() const { return _anim; }
    void setAnim(SpriteAnim *anim) { _anim = anim; }
    ObjectWorld *getNextObject() const { return _next_object; }
    void setNextObject(ObjectWorld *next_object) { _next_object = next_object; }
};
#endif // EFFECT_H