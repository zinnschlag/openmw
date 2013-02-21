/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWDIALOGUE_SELECTWRAPPER_H
#define GAME_MWDIALOGUE_SELECTWRAPPER_H

#include <components/esm/loadinfo.hpp>

namespace MWDialogue
{
    class SelectWrapper
    {
            const ESM::DialInfo::SelectStruct& mSelect;

        public:

            enum Function
            {
                Function_None, Function_False,
                Function_Journal,
                Function_Item,
                Function_Dead,
                Function_Id,
                Function_Faction,
                Function_Class,
                Function_Race,
                Function_Cell,
                Function_Local,
                Function_Global,
                Function_SameGender, Function_SameRace, Function_SameFaction,
                Function_Choice,
                Function_PcCommonDisease, Function_PcBlightDisease, Function_PcCorprus,
                Function_AiSetting,
                Function_PcAttribute, Function_PcSkill,
                Function_PcExpelled,
                Function_PcVampire,
                Function_FriendlyHit,
                Function_TalkedToPc,
                Function_PcLevel, Function_PcHealthPercent, Function_PcDynamicStat,
                Function_PcGender, Function_PcClothingModifier, Function_PcCrimeLevel,
                Function_RankRequirement,
                Function_HealthPercent, Function_Level, Function_PCReputation,
                Function_Weather,
                Function_Reputation, Function_Alarmed, Function_FactionRankDiff, Function_Detected,
                Function_Attacked, Function_ShouldAttack,
                Function_CreatureTargetted,
                Function_PCWerewolf, Function_WerewolfKills,
                Function_RankLow, Function_RankHigh
            };

            enum Type
            {
                Type_None,
                Type_Integer,
                Type_Numeric,
                Type_Boolean
            };

        private:

            Function decodeFunction() const;

        public:

            SelectWrapper (const ESM::DialInfo::SelectStruct& select);

            Function getFunction() const;

            int getArgument() const;

            Type getType() const;

            bool isInverted() const;

            bool isNpcOnly() const;
            ///< \attention Do not call any of the select functions for this select struct!

            bool selectCompare (int value) const;

            bool selectCompare (float value) const;

            bool selectCompare (bool value) const;

            std::string getName() const;
            ///< Return case-smashed name.
    };
}

#endif
