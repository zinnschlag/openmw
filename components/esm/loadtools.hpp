#ifndef OPENMW_ESM_TOOLS_H
#define OPENMW_ESM_TOOLS_H

#include <string>

namespace ESM
{

class ESMReader;
class ESMWriter;

/*
 * This file covers lockpicks (LOCK), probes (PROB) and armor repair
 * items (REPA). These have nearly identical data structures.
 */

struct Tool
{
    enum Type
    {
        Type_Pick,
        Type_Probe,
        Type_Repair
    };

    struct Data
    {
        float mWeight;
        int mValue;

        // And when I say nearly identical structure, I mean perfectly
        // identical except that these two variables are swapped
        // for repair items. Don't ask me why.
        union { float mQuality; int mUses; } mQU1;
        union { int mUses; float mQuality; } mQU2;
    }; // Size = 16

    Data mData;
    Type mType;
    std::string mId, mName, mModel, mIcon, mScript;

    float getQuality() const
    {
        if (mType == Type_Repair)
            return mData.mQU2.mQuality;
        else
            return mData.mQU1.mQuality;
    }

    int getUses() const
    {
        if (mType == Type_Repair)
            return mData.mQU1.mUses;
        else
            return mData.mQU2.mUses;
    }

    void load(ESMReader &esm);
    void save(ESMWriter &esm);
};

struct Lockpick: Tool
{
    Lockpick() { mType = Type_Pick; }
};

struct Probe: Tool
{
    Probe() { mType = Type_Probe; }
};

struct Repair: Tool
{
    Repair() { mType = Type_Repair; }
};

}
#endif
