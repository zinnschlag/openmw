/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWMECHANICS_ALCHEMY_H
#define GAME_MWMECHANICS_ALCHEMY_H

#include <vector>
#include <set>

#include <components/esm/effectlist.hpp>

#include "../mwworld/ptr.hpp"

namespace MWMechanics
{
    struct EffectKey;

    /// \brief Potion creation via alchemy skill
    class Alchemy
    {
        public:
        
            typedef std::vector<MWWorld::Ptr> TToolsContainer;
            typedef TToolsContainer::const_iterator TToolsIterator;
    
            typedef std::vector<MWWorld::Ptr> TIngredientsContainer;
            typedef TIngredientsContainer::const_iterator TIngredientsIterator;

            typedef std::vector<ESM::ENAMstruct> TEffectsContainer;
            typedef TEffectsContainer::const_iterator TEffectsIterator;
    
            enum Result
            {
                Result_Success,
                
                Result_NoMortarAndPestle,
                Result_LessThanTwoIngredients,
                Result_NoName,
                Result_NoEffects,
                Result_RandomFailure
            };
    
        private:
    
            MWWorld::Ptr mAlchemist;
            TToolsContainer mTools;
            TIngredientsContainer mIngredients;
            TEffectsContainer mEffects;
            int mValue;

            std::set<EffectKey> listEffects() const;
            ///< List all effects shared by at least two ingredients.

            void applyTools (int flags, float& value) const;

            void updateEffects();
            
            const ESM::Potion *getRecord() const;
            ///< Return existing recrod for created potion (may return 0)
            
            void removeIngredients();
            ///< Remove selected ingredients from alchemist's inventory, cleanup selected ingredients and
            /// update effect list accordingly.

            void addPotion (const std::string& name);
            ///< Add a potion to the alchemist's inventory.
            
            void increaseSkill();
            ///< Increase alchemist's skill.
            
            float getChance() const;
            ///< Return chance of success.
            
            int countIngredients() const;
            
        public:
        
            void setAlchemist (const MWWorld::Ptr& npc);
            ///< Set alchemist and configure alchemy setup accordingly. \a npc may be empty to indicate that
            /// there is no alchemist (alchemy session has ended).
            
            TToolsIterator beginTools() const;
            ///< \attention Iterates over tool slots, not over tools. Some of the slots may be empty.
            
            TToolsIterator endTools() const;
            
            TIngredientsIterator beginIngredients() const;
            ///< \attention Iterates over ingredient slots, not over ingredients. Some of the slots may be empty.
            
            TIngredientsIterator endIngredients() const;
            
            void clear();
            ///< Remove alchemist, tools and ingredients.
            
            int addIngredient (const MWWorld::Ptr& ingredient);
            ///< Add ingredient into the next free slot.
            ///
            /// \return Slot index or -1, if adding failed because of no free slot or the ingredient type being
            /// listed already.
            
            void removeIngredient (int index);
            ///< Remove ingredient from slot (calling this function on an empty slot is a no-op).
            
            TEffectsIterator beginEffects() const;
            
            TEffectsIterator endEffects() const;
            
            std::string getPotionName() const;
            ///< Return the name of the potion that would be created when calling create (if a record for such
            /// a potion already exists) or return an empty string.
            
            Result create (const std::string& name);
            ///< Try to create a potion from the ingredients, place it in the inventory of the alchemist and
            /// adjust the skills of the alchemist accordingly.
            /// \param name must not be an empty string, unless there is already a potion record (
            /// getPotionName() does not return an empty string).
    };
}

#endif

