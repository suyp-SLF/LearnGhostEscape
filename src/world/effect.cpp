#include "effect.h"
#include "../core/scene.h"
#include "../core/scene.h"

Effect *Effect::addEffectChild(Object *parent, const std::string &file_path, glm::vec2 position, float scale, ObjectWorld *next_object)
{
    auto effect = new Effect();
    effect->init();
    effect->setAnim(SpriteAnim::addSpriteAnimChild(effect, file_path, Anchor::CENTER, scale));
    effect->_anim->setIsLoop(false);
    effect->_anim->setActive(true);
    effect->setPosition(position);
    effect->setNextObject(next_object);
    if (parent) parent->safeAddChild(effect);
    return effect;
}

void Effect::update(float dt)
{
    ObjectWorld::update(dt);
    checkFinish();
}

void Effect::clean()
{
    ObjectWorld::clean();
    if(_next_object)
    {
        _next_object->clean();
        delete _next_object;
        _next_object = nullptr;
    }
}

void Effect::checkFinish()
{
    if (_anim->getIsFinish())
    {
        _is_delete = true;
        if (_next_object != nullptr)
        {
            Game::getInstance().getCurrentScene()->safeAddChild(_next_object);
            _next_object = nullptr;
        }
    }
}