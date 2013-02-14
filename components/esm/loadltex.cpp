#include "loadltex.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void LandTexture::load(ESMReader &esm)
{
    esm.getHNT(mIndex, "INTV");
    mIndex = le32toh(mIndex);
    mTexture = esm.getHNString("DATA");
}
void LandTexture::save(ESMWriter &esm)
{
    mIndex = htole32(mIndex);
    esm.writeHNT("INTV", mIndex);
    esm.writeHNCString("DATA", mTexture);
}

}
