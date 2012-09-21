#ifndef _ESM_LEVLISTS_H
#define _ESM_LEVLISTS_H

#include <string>
#include <vector>

#include "record.hpp"

namespace ESM
{

/*
 * Leveled lists. Since these have identical layout, I only bothered
 * to implement it once.
 *
 * We should later implement the ability to merge leveled lists from
 * several files. 
 */

struct LeveledListBase : public Record
{
    enum Flags
    {
        AllLevels = 0x01, // Calculate from all levels <= player
                          // level, not just the closest below
                          // player.
        Each = 0x02       // Select a new item each time this
                          // list is instantiated, instead of
                          // giving several identical items
    };                    // (used when a container has more
                          // than one instance of one leveled
                          // list.)
    int mFlags;
    unsigned char mChanceNone; // Chance that none are selected (0-255?)

    // Record name used to read references. Must be set before load() is
    // called.
    const char *mRecName;

    struct LevelItem
    {
        std::string mId;
        short mLevel;
    };

    std::vector<LevelItem> mList;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);

    int getName()
    {
        if (mRecName[0] == 'C')
            return REC_LEVC;
        
        return REC_LEVI;
    }
};

struct CreatureLevList: LeveledListBase
{
    CreatureLevList()
    {
        mRecName = "CNAM";
    }
};

struct ItemLevList: LeveledListBase
{
    ItemLevList()
    {
        mRecName = "INAM";
    }
};

}
#endif
