#ifndef HUD_STATS_H
#define HUD_STATS_H

#include "../core/object_screen.h"
class Sprite;
class Actor;
class HUDStats : public ObjectScreen
{
protected:
    Actor *_target = nullptr;
    Sprite *_health_bar = nullptr;
    Sprite *_health_bar_bg = nullptr;
    Sprite *_health_bar_icon = nullptr;

    Sprite *_mana_bar = nullptr;
    Sprite *_mana_bar_bg = nullptr;
    Sprite *_mana_bar_icon = nullptr;

    float _health_percentage = 1.f;
    float _mana_percentage = 1.f;

public:
    virtual void init() override;
    virtual void update(float dt) override;
    //
    static HUDStats* addHudStatsChild(Object *parent, Actor *target, glm::vec2 render_position);
    void updateHealthBar();
    void updateManaBar();
    // Setter AND GETTER
    Sprite *getHealthBar() const { return _health_bar; }
    void setHealthBar(Sprite *health_bar) { _health_bar = health_bar; }
    Sprite *getManaBar() const { return _mana_bar; }
    void setManaBar(Sprite *mana_bar) { _mana_bar = mana_bar; }
    Sprite *getHealthBarBG() const { return _health_bar_bg; }
    void setHealthBarBG(Sprite *health_bar_bg) { _health_bar_bg = health_bar_bg; }
    Sprite *getManaBarBG() const { return _mana_bar_bg; }
    void setManaBarBG(Sprite *mana_bar_bg) { _mana_bar_bg = mana_bar_bg; }
    Sprite *getHealthBarIcon() const { return _health_bar_icon; }
    void setHealthBarIcon(Sprite *health_bar_icon) { _health_bar_icon = health_bar_icon; }
    Sprite *getManaBarIcon() const { return _mana_bar_icon; }
    void setManaBarIcon(Sprite *mana_bar_icon) { _mana_bar_icon = mana_bar_icon; }
    Actor *getTarget() const { return _target; }
    void setTarget(Actor *target) { _target = target; }
    float getHealthPercentage() const { return _health_percentage; }
    void setHealthPercentage(float health_percentage) { _health_percentage = health_percentage; }
    float getManaPercentage() const { return _mana_percentage; }
    void setManaPercentage(float mana_percentage) { _mana_percentage = mana_percentage; }
};
#endif // HUD_STATS_H