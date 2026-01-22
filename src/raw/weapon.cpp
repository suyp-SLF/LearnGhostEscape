#include "weapon.h"

#include "../core/actor.h"
#include "stats.h"
#include "../world/spell.h"
#include "../core/scene.h"

void Weapon::update(float dt)
{
    Object::update(dt);
}

void Weapon::attack(glm::vec2 position, Spell* spell)
{
    
   _parent->getStats()->useMana(_mana_cost);
   _cool_down_timer = 0;
   spell->setPosition(position);
    _game.getCurrentScene()->safeAddChild(spell);
}
bool Weapon::canAttack()
{
    if(_cool_down_timer < _cool_down) return false;
    if(_parent->getStats()->canUseMana(_mana_cost)) return false;
    return true;
}
