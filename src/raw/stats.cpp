#include "stats.h"

Stats *Stats::addStatsChild(Actor *parent, float health, float max_health, float mana, float max_mana, float damage, float mana_regen)
{
    Stats *stats = new Stats();
    stats->setParent(parent);
    stats->setHealth(health);
    stats->setMaxHealth(max_health);
    stats->setMana(mana);
    stats->setMaxMana(max_mana);
    stats->setDamage(damage);
    stats->setManaRegen(mana_regen);
    parent->addChild(stats);
    return stats;
}

void Stats::update(float dt)
{
    Object::update(dt);
    regenMana(dt);
    if(_is_invincible){
        _invincible_timer += dt;
        if(_invincible_timer > _invincible_time){
            _is_invincible = false;
            _invincible_timer = 0.f;
        }
    }
}

bool Stats::canUseMana(float mana_cost)
{
    return _mana >= mana_cost;
}

void Stats::useMana(float mana_cost)
{
    _mana -= mana_cost;
}

void Stats::regenMana(float dt)
{
    _mana += _mana_regen * dt;
    if (_mana > _max_mana)
        _mana = _max_mana;
}

int Stats::takeDamage(float damage)
{
    if (_is_invincible) return 0;
    _health -= damage;
    if (_health < 0)
    {
        _health = 0;
        _is_alive = false;
    }
    _is_invincible = true;
    _invincible_timer = 0.f;
    return damage;
}
