#include "loadlevlist.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void LeveledListBase::load(ESMReader &esm)
{
    esm.getHNT(mFlags, "DATA");
    mFlags = le32toh(mFlags);

    esm.getHNT(mChanceNone, "NNAM");

    if (esm.isNextSub("INDX"))
    {
        int len;
        esm.getHT(len);
        len = le32toh(len);
        mList.resize(len);
    }
    else
        return;

    // TODO: Merge with an existing lists here. This can be done
    // simply by adding the lists together, making sure that they are
    // sorted by level. A better way might be to exclude repeated
    // items. Also, some times we don't want to merge lists, just
    // overwrite. Figure out a way to give the user this option.

    for (size_t i = 0; i < mList.size(); i++)
    {
        LevelItem &li = mList[i];
        li.mId = esm.getHNString(mRecName);
        esm.getHNT(li.mLevel, "INTV");
        li.mLevel = le16toh(li.mLevel);
    }
}

void LeveledListBase::save(ESMWriter &esm)
{
    mFlags = htole32(mFlags);
    esm.writeHNT("DATA", mFlags);

    esm.writeHNT("NNAM", mChanceNone);

    int len = mList.size();
    len = htole32(len);
    esm.writeHNT<int>("INDX", len);

    for (std::vector<LevelItem>::iterator it = mList.begin(); it != mList.end(); ++it)
    {
        esm.writeHNCString(mRecName, it->mId);
        it->mLevel = htole16(it->mLevel);
        esm.writeHNT("INTV", it->mLevel);
    }
}

}
