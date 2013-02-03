#include "loadclas.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

const Class::Specialization Class::sSpecializationIds[3] = {
  Class::Combat,
  Class::Magic,
  Class::Stealth
};

const char *Class::sGmstSpecializationIds[3] = {
  "sSpecializationCombat",
  "sSpecializationMagic",
  "sSpecializationStealth"
};

void Class::load(ESMReader &esm)
{
    mName = esm.getHNString("FNAM");
    esm.getHNT(mData, "CLDT", 60);

    mData.mAttribute[0] = le32toh(mData.mAttribute[0]);
    mData.mAttribute[1] = le32toh(mData.mAttribute[1]);
    mData.mSpecialization = le32toh(mData.mSpecialization);
    for (size_t i = 0; i < 5; i++)
        for (size_t j = 0; j < 2; j++)
            mData.mSkills[i][j] = le32toh(mData.mSkills[i][j]);
    mData.mIsPlayable = le32toh(mData.mIsPlayable);
    mData.mCalc = le32toh(mData.mCalc);

    if (mData.mIsPlayable > 1)
        esm.fail("Unknown bool value");

    mDescription = esm.getHNOString("DESC");
}

void Class::save(ESMWriter &esm)
{
    esm.writeHNCString("FNAM", mName);

    mData.mAttribute[0] = htole32(mData.mAttribute[0]);
    mData.mAttribute[1] = htole32(mData.mAttribute[1]);
    mData.mSpecialization = htole32(mData.mSpecialization);
    for (size_t i = 0; i < 5; i++)
        for (size_t j = 0; j < 2; j++)
            mData.mSkills[i][j] = htole32(mData.mSkills[i][j]);
    mData.mIsPlayable = htole32(mData.mIsPlayable);
    mData.mCalc = htole32(mData.mCalc);
    esm.writeHNT("CLDT", mData, 60);

    esm.writeHNOString("DESC", mDescription);
}

}
