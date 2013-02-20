/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWMECHANICS_ACTIVESPELLS_H
#define GAME_MWMECHANICS_ACTIVESPELLS_H

#include <map>
#include <vector>
#include <string>

#include "../mwworld/timestamp.hpp"

#include "magiceffects.hpp"

namespace ESM
{
    struct Spell;
    struct EffectList;
}

namespace MWWorld
{
    class Ptr;
}

namespace MWMechanics
{
    /// \brief Lasting spell effects
    ///
    /// \note The name of this class is slightly misleading, since it also handels lasting potion
    /// effects.
    class ActiveSpells
    {
        public:

            typedef std::map<std::string, std::pair<MWWorld::TimeStamp, float> > TContainer;
            typedef TContainer::const_iterator TIterator;

        private:

            mutable TContainer mSpells; // spellId, (time of casting, relative magnitude)
            mutable MagicEffects mEffects;
            mutable bool mSpellsChanged;
            mutable MWWorld::TimeStamp mLastUpdate;

            void update() const;
            
            void rebuildEffects() const;

            std::pair<ESM::EffectList, bool> getEffectList (const std::string& id) const;

        public:

            ActiveSpells();

            bool addSpell (const std::string& id, const MWWorld::Ptr& actor);
            ///< Overwrites an existing spell with the same ID. If the spell does not have any
            /// non-instant effects, it is ignored.
            ///
            /// \return Has the spell been added?

            void removeSpell (const std::string& id);

            bool isSpellActive (std::string id) const;
            ///< case insensitive

            const MagicEffects& getMagicEffects() const;

            TIterator begin() const;

            TIterator end() const;

            double timeToExpire (const TIterator& iterator) const;
            ///< Returns time (in in-game hours) until the spell pointed to by \a iterator
            /// expires.
    };
}

#endif
