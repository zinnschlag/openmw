#include "effectlist.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM {

void EffectList::load(ESMReader &esm)
{
    ENAMstruct s;
    while (esm.isNextSub("ENAM")) {
        esm.getHT(s, 24);
        s.mEffectID = le16toh(s.mEffectID);
        s.mRange = le32toh(s.mRange);
        s.mArea = le32toh(s.mArea);
        s.mDuration = le32toh(s.mDuration);
        s.mMagnMin = le32toh(s.mMagnMin);
        s.mMagnMax = le32toh(s.mMagnMax);
        mList.push_back(s);
    }
}

void EffectList::save(ESMWriter &esm)
{
    for (std::vector<ENAMstruct>::iterator it = mList.begin(); it != mList.end(); ++it) {
        it->mEffectID = le16toh(it->mEffectID);
        it->mRange = le32toh(it->mRange);
        it->mArea = le32toh(it->mArea);
        it->mDuration = le32toh(it->mDuration);
        it->mMagnMin = le32toh(it->mMagnMin);
        it->mMagnMax = le32toh(it->mMagnMax);
        esm.writeHNT<ENAMstruct>("ENAM", *it, 24);
    }
}

} // end namespace
