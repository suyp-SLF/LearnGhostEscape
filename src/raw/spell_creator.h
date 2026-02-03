#ifndef SPELL_CREATOR_H
#define SPELL_CREATOR_H

#include "../core/object.h"
#include "../world/spell.h"

class SpellCreator : public Object
{
    virtual Spell* create() = 0;
};
#endif // SPELL_CREATOR_H