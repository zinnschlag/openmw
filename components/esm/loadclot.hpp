#ifndef _ESM_CLOT_H
#define _ESM_CLOT_H

#include <string>

#include "record.hpp"
#include "loadarmo.hpp"

namespace ESM
{

/*
 * Clothing
 */

struct Clothing : public Record
{
    enum Type
    {
        Pants = 0,
        Shoes = 1,
        Shirt = 2,
        Belt = 3,
        Robe = 4,
        RGlove = 5,
        LGlove = 6,
        Skirt = 7,
        Ring = 8,
        Amulet = 9
    };

    struct CTDTstruct
    {
        int mType;
        float mWeight;
        short mValue;
        short mEnchant;
    };
    CTDTstruct mData;

    PartReferenceList mParts;

    std::string mName, mModel, mIcon, mEnchant, mScript;

    void load(ESMReader &esm);
    void save(ESMWriter &esm);

    int getName() { return REC_CLOT; }
};
}
#endif
