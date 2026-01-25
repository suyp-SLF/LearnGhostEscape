#ifndef UI_MOUSE_H
#define UI_MOUSE_H

#include "../core/object_screen.h"
#include "../affiliate/sprite.h"

#include <string>

class UIMouse : public ObjectScreen
{
protected:
    Sprite *_normal1 = nullptr;
    Sprite *_normal2 = nullptr;
    float _timer = 0.f;

public:
    virtual void update(float dt) override;
    virtual void render() override;
    //
    static UIMouse *addUIMouseChild(Object *parent, const std::string &normal1, const std::string &normal2, float scale = 1.f, Anchor anchor = Anchor::CENTER);

    // GETTER AND SETTER
    Sprite *getNormal1() const { return _normal1; }
    void setNormal1(Sprite *normal1) { _normal1 = normal1; }
    Sprite *getNormal2() const { return _normal2; }
    void setNormal2(Sprite *normal2) { _normal2 = normal2; }
};
#endif // UI_MOUSE_H