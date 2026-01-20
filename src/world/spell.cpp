#include "spell.h"

void Spell::update(float dt)
{
    ObjectWorld::update(dt);
    if(_anim->getIsFinish()) 
    {
        setDelete(true);
    }
    attack();
}

void Spell::attack()
{

}
