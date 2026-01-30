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

void WeaponThunder::init()
{
    Weapon::init();
    auto mainScene = _game.getCurrentScene();
    auto position = glm::vec2(_game.getScreenSize().x - 100.f, 30.f);
    _hud_skill = HUDSkill::addHudSkillChild(mainScene, "assets/UI/Electric-Icon.png", position, .1f, Anchor::CENTER);
}

void WeaponThunder::update(float dt)
{
    Weapon::update(dt);
    if(_hud_skill) _hud_skill->setPercentage(_cool_down_timer / _cool_down);
}

bool WeaponThunder::handleEvents(SDL_Event &event)
{
    if(Weapon::handleEvents(event)) return true;
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            if (canAttack())
            {
                _game.playSoundEffect("assets/sound/big-thunder.mp3");
                Scene *mainScene = _game.getCurrentScene();
                auto pos = mainScene->screenToWorld(_game.getMousePosition());
                auto spell = Spell::addSpellChild(mainScene, "assets/effect/Thunderstrike w blur.png", pos, 40.f, 3.f, Anchor::CENTER);
                attack(pos, spell);
                return true;
            }
        }
    }
    return false;
}


