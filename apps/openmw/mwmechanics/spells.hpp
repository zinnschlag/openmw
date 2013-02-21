/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWMECHANICS_SPELLS_H
#define GAME_MWMECHANICS_SPELLS_H

#include <map>
#include <string>

namespace ESM
{
    struct Spell;
}

namespace MWMechanics
{
    class MagicEffects;

    /// \brief Spell list
    ///
    /// This class manages known spells as well as abilities, powers and permanent negative effects like
    /// diseaes.
    class Spells
    {
        public:

            typedef std::map<std::string, float> TContainer; // ID, normalised magnitude
            typedef TContainer::const_iterator TIterator;

        private:

            TContainer mSpells;
            std::string mSelectedSpell;

        public:

            TIterator begin() const;

            TIterator end() const;

            void add (const std::string& spell);
            ///< Adding a spell that is already listed in *this is a no-op.

            void remove (const std::string& spell);
            ///< If the spell to be removed is the selected spell, the selected spell will be changed to
            /// no spell (empty string).

            MagicEffects getMagicEffects() const;
            ///< Return sum of magic effects resulting from abilities, blights, deseases and curses.

            void clear();
            ///< Remove all spells of al types.

            void setSelectedSpell (const std::string& spellId);
            ///< This function does not verify, if the spell is available.

            const std::string getSelectedSpell() const;
            ///< May return an empty string.

            bool hasCommonDisease() const;

            bool hasBlightDisease() const;
    };
}

#endif
