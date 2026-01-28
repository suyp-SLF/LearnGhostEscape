#ifndef STATS_H
#define STATS_H

#include "../core/object.h"
#include "../core/actor.h"

class Stats : public Object
{
protected:
    Actor *_parent = nullptr;
    float _health = 100.f;
    float _max_health = 100.f;
    float _mana = 100.f;
    float _max_mana = 100.f;
    float _damage = 40.f;
    float _mana_regen = 10.f;

    float _invincible_timer = 0.f;
    float _invincible_time = 1.f;
    bool _is_alive = true;
    bool _is_invincible = false;
 
public:
    static Stats *addStatsChild(Actor *parent, float health = 100.f, float max_health = 100.f, float mana = 100.f, float max_mana = 100.f, float damage = 40.f, float mana_regen = 10.f);
    virtual void update(float dt) override;

    bool canUseMana(float mana_cost);
    void useMana(float mana_cost);
    void regenMana(float dt);
    int takeDamage(float damage);

    // GETTER AND SETTER
    float getHealth() { return _health; }
    float getMaxHealth() { return _max_health; }
    float getMana() { return _mana; }
    float getMaxMana() { return _max_mana; }
    float getDamage() { return _damage; }
    float getManaRegen() { return _mana_regen; }
    bool getIsAlive() { return _is_alive; }
    Actor *getParent() { return _parent; }
    bool isInvincible() { return _is_invincible; }

    void setHealth(float health) { _health = health; }
    void setMaxHealth(float max_health) { _max_health = max_health; }
    void setMana(float mana) { _mana = mana; }
    void setMaxMana(float max_mana) { _max_mana = max_mana; }
    void setDamage(float damage) { _damage = damage; }
    void setManaRegen(float mana_regen) { _mana_regen = mana_regen; }
    void setAlive(bool is_alive) { _is_alive = is_alive; }
    void setParent(Actor *parent) { _parent = parent; }
    void setInvincible(bool is_invincible) { _is_invincible = is_invincible; }
};
#endif // STATS_H