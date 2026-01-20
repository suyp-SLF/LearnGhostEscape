#include "spell.h"
#include "../core/scene.h"
#include "../enemy.h"
#include "../affiliate/sprite_anim.h"

void Spell::update(float dt)
{
    ObjectWorld::update(dt);
    if (_anim->getIsFinish())
    {
        setDelete(true);
    }
    attack();
}

Spell *Spell::addSpellChild(ObjectWorld *parent, const std::string &texture_path, glm::vec2 position, float scale, Anchor anchor)
{
    auto spell = new Spell();
    spell->init();
    spell->_anim = SpriteAnim::addSpriteAnimChild(spell, texture_path, anchor, scale);
    spell->_anim->setIsLoop(false);
    spell->setPosition(position);
    if (parent) parent->addChild(spell);
    return spell;
}

void Spell::attack()
{
    auto objects = _game.getCurrentScene()->getChildrenWorld();
    for (auto object : objects)
    {
        if (object->getObjectType() == ObjectType::ENEMY && _collider && object->getCollider() && _collider->isColliding(object->getCollider()))
        {
            //  强转object为Enemy
            auto enemy = dynamic_cast<Enemy *>(object);
            enemy->takeDamage(_damage);
        }
    }
}
