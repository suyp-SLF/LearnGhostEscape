#include "hud_stats.h"
#include "../core/actor.h"
#include "../raw/stats.h"
#include "../affiliate/sprite.h"

void HUDStats::init()
{
    ObjectScreen::init();
    _health_bar_bg = Sprite::addSpriteChild(this, "assets/UI/bar_bg.png", 3.f, Anchor::TOP_LEFT);
    _health_bar_bg->setOffset(_health_bar_bg->getOffset() + glm::vec2(30, 0));
    _health_bar = Sprite::addSpriteChild(this, "assets/UI/bar_red.png", 3.f, Anchor::TOP_LEFT);
    _health_bar->setOffset(_health_bar->getOffset() + glm::vec2(30, 0));
    _health_bar_icon = Sprite::addSpriteChild(this, "assets/UI/Red Potion.png", .5f, Anchor::TOP_LEFT);

    _mana_bar_bg = Sprite::addSpriteChild(this, "assets/UI/bar_bg.png", 3.f, Anchor::TOP_LEFT);
    _mana_bar_bg->setOffset(_mana_bar_bg->getOffset() + glm::vec2(300, 0));
    _mana_bar = Sprite::addSpriteChild(this, "assets/UI/bar_blue.png", 3.f, Anchor::TOP_LEFT);
    _mana_bar->setOffset(_mana_bar->getOffset() + glm::vec2(300, 0));
    _mana_bar_icon = Sprite::addSpriteChild(this, "assets/UI/Blue Potion.png", .5f, Anchor::TOP_LEFT);
    _mana_bar_icon->setOffset(_mana_bar_icon->getOffset() + glm::vec2(270, 0));
}

void HUDStats::update(float dt)
{
    ObjectScreen::update(dt);
    updateHealthBar();
    updateManaBar();
}

HUDStats *HUDStats::addHudStatsChild(Object *parent, Actor *target, glm::vec2 render_position)
{
    HUDStats *hud_stats = new HUDStats();
    hud_stats->init();
    hud_stats->setRenderPosition(render_position);
    hud_stats->setTarget(target);
    if (parent) parent->addChild(hud_stats);
}

void HUDStats::updateHealthBar()
{
    if(!_target || !_target->getStats() || !_health_bar) return;
    _health_bar->setPercentage(glm::vec2(_target->getStats()->getHealth() / _target->getStats()->getMaxHealth(), 1.f));
}

void HUDStats::updateManaBar()
{
     if(!_target || !_target->getStats() || !_mana_bar) return;
      _mana_bar->setPercentage(glm::vec2(_target->getStats()->getMana() / _target->getStats()->getMaxMana(), 1.f));
}
