#include "weapon_thunder.h"
#include "core/scene.h"
#include "world/spell.h"
#include "core/actor.h"

WeaponThunder *WeaponThunder::addWeaponThunderChild(Actor *parent, float cool_down, float mana_cost)
{
    auto weapon = new WeaponThunder();
    weapon->init();
    weapon->setParent(parent);
    weapon->setCoolDown(cool_down);
    weapon->setManaCost(mana_cost);
    if (parent)
        parent->addChild(weapon);
    return weapon;
}

void WeaponThunder::handleEvents(SDL_Event &event)
{
    Weapon::handleEvents(event);
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            if (canAttack())
            {
                Scene *scene = _game.getCurrentScene();
                auto spell = Spell::addSpellChild(scene, "assets/effect/Thunderstrike w blur.png", scene->screenToWorld(_game.getMousePosition()), 90.f, 3.f, Anchor::CENTER);
            }
        }
    }
}