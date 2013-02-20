/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_ARMO_H
#define OPENMW_ESM_ARMO_H

#include <vector>
#include <string>

namespace ESM
{

class ESMReader;
class ESMWriter;

enum PartReferenceType
{
    PRT_Head = 0,
    PRT_Hair = 1,
    PRT_Neck = 2,
    PRT_Cuirass = 3,
    PRT_Groin = 4,
    PRT_Skirt = 5,
    PRT_RHand = 6,
    PRT_LHand = 7,
    PRT_RWrist = 8,
    PRT_LWrist = 9,
    PRT_Shield = 10,
    PRT_RForearm = 11,
    PRT_LForearm = 12,
    PRT_RUpperarm = 13,
    PRT_LUpperarm = 14,
    PRT_RFoot = 15,
    PRT_LFoot = 16,
    PRT_RAnkle = 17,
    PRT_LAnkle = 18,
    PRT_RKnee = 19,
    PRT_LKnee = 20,
    PRT_RLeg = 21,
    PRT_LLeg = 22,
    PRT_RPauldron = 23,
    PRT_LPauldron = 24,
    PRT_Weapon = 25,
    PRT_Tail = 26
};

// Reference to body parts
struct PartReference
{
    char mPart;
    std::string mMale, mFemale;
};

// A list of references to body parts
struct PartReferenceList
{
    std::vector<PartReference> mParts;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};

struct Armor
{
    enum Type
    {
        Helmet = 0,
        Cuirass = 1,
        LPauldron = 2,
        RPauldron = 3,
        Greaves = 4,
        Boots = 5,
        LGauntlet = 6,
        RGauntlet = 7,
        Shield = 8,
        LBracer = 9,
        RBracer = 10
    };

    struct AODTstruct
    {
        int mType;
        float mWeight;
        int mValue, mHealth, mEnchant, mArmor;
    };

    AODTstruct mData;
    PartReferenceList mParts;

    std::string mId, mName, mModel, mIcon, mScript, mEnchant;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};
}
#endif
