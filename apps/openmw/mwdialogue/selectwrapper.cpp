
#include "selectwrapper.hpp"

#include <cctype>

#include <stdexcept>
#include <algorithm>
#include <sstream>

namespace
{
    std::string toLower (const std::string& name)
    {
        std::string lowerCase;

        std::transform (name.begin(), name.end(), std::back_inserter (lowerCase),
            (int(*)(int)) std::tolower);

        return lowerCase;
    }

    template<typename T1, typename T2>
    bool selectCompareImp (char comp, T1 value1, T2 value2)
    {
        switch (comp)
        {
            case '0': return value1==value2;
            case '1': return value1!=value2;
            case '2': return value1>value2;
            case '3': return value1>=value2;
            case '4': return value1<value2;
            case '5': return value1<=value2;
        }

        throw std::runtime_error ("unknown compare type in dialogue info select");
    }
    
    template<typename T>
    bool selectCompareImp (const ESM::DialInfo::SelectStruct& select, T value1)
    {
        if (select.mType==ESM::VT_Short || select.mType==ESM::VT_Int ||
            select.mType==ESM::VT_Long)
        {
            return selectCompareImp (select.mSelectRule[4], value1, select.mI);
        }
        else if (select.mType==ESM::VT_Float)
        {
            return selectCompareImp (select.mSelectRule[4], value1, select.mF);
        }
        else
            throw std::runtime_error (
                "unsupported variable type in dialogue info select");        
    }
}

MWDialogue::SelectWrapper::Function MWDialogue::SelectWrapper::decodeFunction() const
{
    int index = 0;
    
    std::istringstream (mSelect.mSelectRule.substr(2,2)) >> index;

    switch (index)
    {
        // 0, 1
        case  2: return Function_RankRequirement;
        // 3
        case  4: return Function_HealthPercent;
        case  5: return Function_PCReputation;
        case  6: return Function_PcLevel;
        case  7: return Function_PcHealthPercent;
        case  8: case  9: return Function_PcDynamicStat;
        case 10: return Function_PcAttribute;
        case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20:
        case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30:
        case 31: case 32: case 33: case 34: case 35: case 36: case 37: return Function_PcSkill;
        case 38: return Function_PcGender;
        case 39: return Function_PcExpelled;
        case 40: return Function_PcCommonDisease;
        case 41: return Function_PcBlightDisease;
        case 42: return Function_PcClothingModifier;
        case 43: return Function_PcCrimeLevel;
        case 44: return Function_SameGender;
        case 45: return Function_SameRace;
        case 46: return Function_SameFaction;
        // 47-49
        case 50: return Function_Choice;
        case 51: case 52: case 53: case 54: case 55: case 56: case 57: return Function_PcAttribute;
        case 58: return Function_PcCorprus;
        // 59
        case 60: return Function_PcVampire;
        case 61: return Function_Level;
        // 62
        case 63: return Function_TalkedToPc;
        case 64: return Function_PcDynamicStat;
        // 65
        case 66: return Function_FriendlyHit;
        case 67: case 68: case 69: case 70: return Function_AiSetting;
        // 71
    }
    
    return Function_False;
}

MWDialogue::SelectWrapper::SelectWrapper (const ESM::DialInfo::SelectStruct& select) : mSelect (select) {}

MWDialogue::SelectWrapper::Function MWDialogue::SelectWrapper::getFunction() const
{
    char type = mSelect.mSelectRule[1];

    switch (type)
    {
        case '1': return decodeFunction();
        case '2': return Function_Global;
        case '3': return Function_Local;
        case '4': return Function_Journal;
        case '5': return Function_Item;
        case '6': return Function_Dead;
        case '7': return Function_Id;
        case '8': return Function_Faction;
        case '9': return Function_Class;
        case 'A': return Function_Race;
        case 'B': return Function_Cell;
        case 'C': return Function_Local;
    }

    return Function_None;
}

int MWDialogue::SelectWrapper::getArgument() const
{
    if (mSelect.mSelectRule[1]!='1')
        return 0;
        
    int index = 0;
    
    std::istringstream (mSelect.mSelectRule.substr(2,2)) >> index;
    
    switch (index)
    {
        // AI settings
        case 67: return 1;
        case 68: return 0;
        case 69: return 3;
        case 70: return 2;
        
        // attributes
        case 10: return 0;
        case 51: return 1;
        case 52: return 2;
        case 53: return 3;
        case 54: return 4;
        case 55: return 5;
        case 56: return 6;
        case 57: return 7;
        
        // skills
        case 11: return 0;
        case 12: return 1;
        case 13: return 2;
        case 14: return 3;
        case 15: return 4;
        case 16: return 5;
        case 17: return 6;
        case 18: return 7;
        case 19: return 8;
        case 20: return 9;
        case 21: return 10;
        case 22: return 11;
        case 23: return 12;
        case 24: return 13;
        case 25: return 14;
        case 26: return 15;
        case 27: return 16;
        case 28: return 17;
        case 29: return 18;
        case 30: return 19;
        case 31: return 20;
        case 32: return 21;
        case 33: return 22;
        case 34: return 23;
        case 35: return 24;
        case 36: return 25;
        case 37: return 26;
        
        // dynamic stats
        case  8: return 1;
        case  9: return 2;
        case 64: return 0;
    }
            
    return 0;
}

MWDialogue::SelectWrapper::Type MWDialogue::SelectWrapper::getType() const
{
    static const Function integerFunctions[] =
    {
        Function_Journal, Function_Item, Function_Dead,
        Function_Choice,
        Function_AiSetting,
        Function_PcAttribute, Function_PcSkill,
        Function_FriendlyHit,
        Function_PcLevel, Function_PcGender, Function_PcClothingModifier,
        Function_PcCrimeLevel,
        Function_RankRequirement,
        Function_Level, Function_PCReputation,
        Function_None // end marker
    };
    
    static const Function numericFunctions[] =
    {
        Function_Global, Function_Local,
        Function_PcDynamicStat, Function_PcHealthPercent,
        Function_HealthPercent,
        Function_None // end marker
    };    
    
    static const Function booleanFunctions[] =
    {
        Function_False,
        Function_Id, Function_Faction, Function_Class, Function_Race, Function_Cell,
        Function_SameGender, Function_SameRace, Function_SameFaction,
        Function_PcCommonDisease, Function_PcBlightDisease, Function_PcCorprus,
        Function_PcExpelled,
        Function_PcVampire, Function_TalkedToPc,
        Function_None // end marker
    };   
    
    Function function = getFunction();

    for (int i=0; integerFunctions[i]!=Function_None; ++i)
        if (integerFunctions[i]==function)
            return Type_Integer;
    
    for (int i=0; numericFunctions[i]!=Function_None; ++i)
        if (numericFunctions[i]==function)
            return Type_Numeric;

    for (int i=0; booleanFunctions[i]!=Function_None; ++i)
        if (booleanFunctions[i]==function)
            return Type_Boolean;
    
    return Type_None;
}

bool MWDialogue::SelectWrapper::isInverted() const
{
    char type = mSelect.mSelectRule[1];

    return type=='7' || type=='8' || type=='9' || type=='A' || type=='B' || type=='C';
}

bool MWDialogue::SelectWrapper::isNpcOnly() const
{
    static const Function functions[] =
    {
        Function_Faction, SelectWrapper::Function_Class, SelectWrapper::Function_Race,
        Function_SameGender, Function_SameRace, Function_SameFaction,
        Function_PcSkill,
        Function_PcExpelled,
        Function_PcVampire,
        Function_PcCrimeLevel,
        Function_RankRequirement,
        Function_None // end marker
    };

    Function function = getFunction();
    
    for (int i=0; functions[i]!=Function_None; ++i)
        if (functions[i]==function)
            return true;
    
    return false;
}

bool MWDialogue::SelectWrapper::selectCompare (int value) const
{
    return selectCompareImp (mSelect, value)!=isInverted(); // logic XOR
}

bool MWDialogue::SelectWrapper::selectCompare (float value) const
{
    return selectCompareImp (mSelect, value)!=isInverted(); // logic XOR
}

bool MWDialogue::SelectWrapper::selectCompare (bool value) const
{
    return selectCompareImp (mSelect, static_cast<int> (value))!=isInverted(); // logic XOR
}

std::string MWDialogue::SelectWrapper::getName() const
{
    return toLower (mSelect.mSelectRule.substr (5));
}
