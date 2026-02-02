#include "weapon.h"

#include "../core/actor.h"
#include "stats.h"
#include "../world/spell.h"
#include "../core/scene.h"
#include "../screen/hud_skill.h"

Weapon *Weapon::addWeaponChild(Actor *parent, float cool_down, float mana_cost)
{
    auto weapon = new Weapon();
    weapon->init();
    weapon->setParent(parent);
    weapon->setCoolDown(cool_down);
    weapon->setManaCost(mana_cost);
    if (parent)
        parent->addChild(weapon);
    return weapon;
}

bool Weapon::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (event.button.button == _trigger_button)
        {   
            auto mouse_position = Game::getInstance().getCurrentScene()->screenToWorld(Game::getInstance().getMousePosition());
            attack(mouse_position);
        }
    }
    return false;
}

void Weapon::update(float dt)
{
    Object::update(dt);
    _cool_down_timer += dt;
    if (_hud_skill)
        _hud_skill->setPercentage(_cool_down_timer / _cool_down);
}

void Weapon::attack(glm::vec2 position)
{
    if (!_spell_prototype || !canAttack())
        return;
    Game::getInstance().playSoundEffect(_sound_effect);
    _parent->getStats()->useMana(_mana_cost);
    _cool_down_timer = 0;
    auto spell = _spell_prototype->clone();
    spell->setPosition(position);
}
bool Weapon::canAttack()
{
    if (_cool_down_timer < _cool_down)
        return false;
    if (!_parent->getStats()->canUseMana(_mana_cost))
        return false;
    return true;
}
