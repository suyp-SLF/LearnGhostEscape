#ifndef THUNDER_SPELL_CREATOR_H
#define THUNDER_SPELL_CREATOR_H

#include "spell_creator.h"
class ThunderSpellCreator : SpellCreator
{
    virtual Spell* create() override;
};
#endif // THUNDER_SPELL_CREATOR_H