#include "loadinfo.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

namespace ESM
{

void DialInfo::load(ESMReader &esm)
{
    mId = esm.getHNString("INAM");
    mPrev = esm.getHNString("PNAM");
    mNext = esm.getHNString("NNAM");

    // Not present if deleted
    if (esm.isNextSub("DATA")) {
        esm.getHT(mData, 12);
        mData.mUnknown1 = le32toh(mData.mUnknown1);
        mData.mDisposition = le32toh(mData.mDisposition);
    }

    mQuestStatus = QS_None;

    // What follows is somewhat spaghetti-ish, but it's worth if for
    // an extra speedup. INFO is by far the most common record type.

    // subName is a reference to the original, so it changes whenever
    // a new sub name is read. esm.isEmptyOrGetName() will get the
    // next name for us, or return true if there are no more records.
    esm.getSubName();
    const NAME &subName = esm.retSubName();

    if (subName == REC_ONAM)
    {
        mActor = esm.getHString();
        if (esm.isEmptyOrGetName())
            return;
    }
    if (subName == REC_RNAM)
    {
        mRace = esm.getHString();
        if (esm.isEmptyOrGetName())
            return;
    }
    if (subName == REC_CNAM)
    {
        mClass = esm.getHString();
        if (esm.isEmptyOrGetName())
            return;
    }

    mFactionLess = false;
    if (subName == REC_FNAM)
    {
        mNpcFaction = esm.getHString();
        if (mNpcFaction == "FFFF")
            mFactionLess = true;
        if (esm.isEmptyOrGetName())
            return;
    }
    if (subName == REC_ANAM)
    {
        mCell = esm.getHString();
        if (esm.isEmptyOrGetName())
            return;
    }
    if (subName == REC_DNAM)
    {
        mPcFaction = esm.getHString();
        if (esm.isEmptyOrGetName())
            return;
    }
    if (subName == REC_SNAM)
    {
        mSound = esm.getHString();
        if (esm.isEmptyOrGetName())
            return;
    }
    if (subName == REC_NAME)
    {
        mResponse = esm.getHString();
        if (esm.isEmptyOrGetName())
            return;
    }

    while (subName == REC_SCVR)
    {
        SelectStruct ss;

        ss.mSelectRule = esm.getHString();
        esm.isEmptyOrGetName();

        if (subName == REC_INTV)
        {
            ss.mType = VT_Int;
            esm.getHT(ss.mI);
            ss.mI = le32toh(ss.mI);
        }
        else if (subName == REC_FLTV)
        {
            ss.mType = VT_Float;
            esm.getHT(ss.mF);
            ss.mF = letoh_float(ss.mF);
        }
        else
            esm.fail(
                    "INFO.SCVR must precede INTV or FLTV, not "
                            + subName.toString());

        mSelects.push_back(ss);

        if (esm.isEmptyOrGetName())
            return;
    }

    if (subName == REC_BNAM)
    {
        mResultScript = esm.getHString();
        if (esm.isEmptyOrGetName())
            return;
    }

    if (subName == REC_QSTN)
        mQuestStatus = QS_Name;
    else if (subName == REC_QSTF)
        mQuestStatus = QS_Finished;
    else if (subName == REC_QSTR)
        mQuestStatus = QS_Restart;
    else if (subName == REC_DELE)
        mQuestStatus = QS_Deleted;
    else
        esm.fail(
                "Don't know what to do with " + subName.toString()
                        + " in INFO " + mId);

    if (mQuestStatus != QS_None)
        // Skip rest of record
        esm.skipRecord();
}

void DialInfo::save(ESMWriter &esm)
{
    esm.writeHNCString("INAM", mId);
    esm.writeHNCString("PNAM", mPrev);
    esm.writeHNCString("NNAM", mNext);

    mData.mUnknown1 = htole32(mData.mUnknown1);
    mData.mDisposition = htole32(mData.mDisposition);
    esm.writeHNT("DATA", mData, 12);

    esm.writeHNOCString("ONAM", mActor);
    esm.writeHNOCString("RNAM", mRace);
    esm.writeHNOCString("CNAM", mClass);
    esm.writeHNOCString("FNAM", mNpcFaction);
    esm.writeHNOCString("ANAM", mCell);
    esm.writeHNOCString("DNAM", mPcFaction);
    esm.writeHNOCString("SNAM", mSound);
    esm.writeHNOString("NAME", mResponse);

    for (std::vector<SelectStruct>::iterator it = mSelects.begin(); it != mSelects.end(); ++it)
    {
        esm.writeHNString("SCVR", it->mSelectRule);
        switch(it->mType)
        {
        case VT_Int: it->mI = htole32(it->mI); esm.writeHNT("INTV", it->mI); break;
        case VT_Float: it->mF = htole_float(it->mF); esm.writeHNT("FLTV", it->mF); break;
        default: break;
        }
    }

    esm.writeHNOString("BNAM", mResultScript);

    switch(mQuestStatus)
    {
    case QS_Name: esm.writeHNT("QSTN",'\1'); break;
    case QS_Finished: esm.writeHNT("QSTF", '\1'); break;
    case QS_Restart: esm.writeHNT("QSTR", '\1'); break;
    case QS_Deleted: esm.writeHNT("DELE", '\1'); break;
    default: break;
    }
}

}
