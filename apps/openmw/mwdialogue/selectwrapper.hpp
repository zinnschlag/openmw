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
                Function_HealthPercent, Function_Level, Function_PCReputation
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
