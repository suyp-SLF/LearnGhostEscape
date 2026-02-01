#include "spell.h"
#include "../core/scene.h"
#include "../enemy.h"
#include "../affiliate/sprite_anim.h"
#include "../affiliate/collider.h"

void Spell::update(float dt)
{
    ObjectWorld::update(dt);
    if (_anim->getIsFinish())
    {
        setDelete(true);
    }
    attack();
}

Spell *Spell::addSpellChild(Object *parent, const std::string &texture_path, glm::vec2 position, float damage, float scale, Anchor anchor)
{
    auto spell = new Spell();
    spell->init();
    spell->setDamage(damage);
    spell->_anim = SpriteAnim::addSpriteAnimChild(spell, texture_path, anchor, scale);
    spell->_anim->setActive(true);
    auto size = spell->_anim->getSize();
    spell->_collider = Collider::addColliderChild(spell, size, Anchor::CENTER, Collider::Shape::CIRCLE);
    spell->_anim->setIsLoop(false);
    spell->setPosition(position);
    if (parent) parent->safeAddChild(spell);
    return spell;
}

void Spell::attack()
{
    // 1. 如果法术自己已经标记删除，直接跳过逻辑
    if (this->getIsDelete()) return;

    auto scene = Game::getInstance().getCurrentScene();
    if (!scene) return;

    auto& objects = scene->getChildrenWorld();
    for (auto object : objects)
    {
        // 2. 关键检查：指针不为空 且 对象未被标记删除
        if (object == nullptr || object->getIsDelete()) {
            continue;
        }

        // 3. 确保是敌人且碰撞体有效
        if (object->getObjectType() == ObjectType::ENEMY)
        {
            auto enemyCollider = object->getCollider();
            if (_collider && enemyCollider && _collider->isColliding(enemyCollider))
            {
                auto enemy = dynamic_cast<Enemy *>(object);
                if (enemy) 
                {
                    enemy->takeDamage(_damage);
                }
            }
        }
    }
}
