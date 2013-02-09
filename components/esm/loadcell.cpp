#include "loadcell.hpp"

#include <string>
#include <sstream>
#include <list>
#include <boost/concept_check.hpp>

#include "esmreader.hpp"
#include "esmwriter.hpp"

#include <apps/openmw/mwworld/store.hpp>
#include <apps/openmw/mwworld/cellstore.hpp>

namespace ESM
{

/// Some overloaded copare operators.
bool operator==(const MovedCellRef& ref, int pRefnum)
{
  return (ref.mRefnum == pRefnum);
}

bool operator==(const CellRef& ref, int pRefnum)
{
  return (ref.mRefnum == pRefnum);
}

void CellRef::save(ESMWriter &esm)
{
    mRefnum = htole32(mRefnum);
    esm.writeHNT("FRMR", mRefnum);

    esm.writeHNCString("NAME", mRefID);

    if (mScale != 1.0) {
        mScale = htole_float(mScale);
        esm.writeHNT("XSCL", mScale);
    }

    esm.writeHNOCString("ANAM", mOwner);
    esm.writeHNOCString("BNAM", mGlob);
    esm.writeHNOCString("XSOL", mSoul);

    esm.writeHNOCString("CNAM", mFaction);
    if (mFactIndex != -2) {
        mFactIndex = htole32(mFactIndex);
        esm.writeHNT("INDX", mFactIndex);
    }

    if (mCharge != -1.0) {
        mCharge = htole_float(mCharge);
        esm.writeHNT("XCHG", mCharge);
    }

    if (mIntv != -1) {
        mIntv = htole32(mIntv);
        esm.writeHNT("INTV", mIntv);
    }
    if (mNam9 != 0) {
        mNam9 = htole32(mNam9);
        esm.writeHNT("NAM9", mNam9);
    }

    if (mTeleport)
    {
        for (size_t i = 0; i < 3; i++)
            mDoorDest.pos[i] = htole_float(mDoorDest.pos[i]);
        for (size_t i = 0; i < 3; i++)
            mDoorDest.rot[i] = htole_float(mDoorDest.rot[i]);
        esm.writeHNT("DODT", mDoorDest);
        esm.writeHNOCString("DNAM", mDestCell);
    }

    if (mLockLevel != -1) {
        mLockLevel = htole32(mLockLevel);
        esm.writeHNT("FLTV", mLockLevel);
    }
    esm.writeHNOCString("KNAM", mKey);
    esm.writeHNOCString("TNAM", mTrap);

    if (mUnam != -1) {
        esm.writeHNT("UNAM", mUnam);
    }
    if (mFltv != 0) {
        mFltv = htole32(mFltv);
        esm.writeHNT("FLTV", mFltv);
    }

    for (size_t i = 0; i < 3; i++)
        mPos.pos[i] = htole_float(mPos.pos[i]);
    for (size_t i = 0; i < 3; i++)
        mPos.rot[i] = htole_float(mPos.rot[i]);
    esm.writeHNT("DATA", mPos, 24);

    if (mNam0 != 0) {
        mNam0 = htole32(mNam0);
        esm.writeHNT("NAM0", mNam0);
    }
}

void Cell::load(ESMReader &esm, MWWorld::ESMStore &store)
{
    // Ignore this for now, it might mean we should delete the entire cell?
    // TODO: treat the special case "another plugin moved this ref, but we want to delete it"!
    if (esm.isNextSub("DELE")) {
        esm.skipHSub();
    }

    esm.getHNT(mData, "DATA", 12);
    mData.mFlags = le32toh(mData.mFlags);
    mData.mX = le32toh(mData.mX);
    mData.mY = le32toh(mData.mY);

    // Water level
    mWater = -1;
    mNAM0 = 0;

    if (mData.mFlags & Interior)
    {
        // Interior cells
        if (esm.isNextSub("INTV"))
        {
            int waterl;
            esm.getHT(waterl);
            waterl = le32toh(waterl);
            mWater = (float) waterl;
            mWaterInt = true;
        }
        else if (esm.isNextSub("WHGT"))
        {
            esm.getHT(mWater);
            mWater = letoh_float(mWater);
        }

        // Quasi-exterior cells have a region (which determines the
        // weather), pure interior cells have ambient lighting
        // instead.
        if (mData.mFlags & QuasiEx)
            mRegion = esm.getHNOString("RGNN");
        else
        {
            esm.getHNT(mAmbi, "AMBI", 16);
            mAmbi.mAmbient = le32toh(mAmbi.mAmbient);
            mAmbi.mSunlight = le32toh(mAmbi.mSunlight);
            mAmbi.mFog = le32toh(mAmbi.mFog);
            mAmbi.mFogDensity = letoh_float(mAmbi.mFogDensity);
        }
    }
    else
    {
        // Exterior cells
        mRegion = esm.getHNOString("RGNN");

        mMapColor = 0;
        if (esm.isNextSub("NAM5"))
        {
            esm.getHT(mMapColor);
            mMapColor = le32toh(mMapColor);
        }
    }
    if (esm.isNextSub("NAM0")) {
        esm.getHT(mNAM0);
        mNAM0 = le32toh(mNAM0);
    }
    
    // preload moved references
    while (esm.isNextSub("MVRF")) {
        CellRef ref;
        MovedCellRef cMRef;
        getNextMVRF(esm, cMRef);

        MWWorld::Store<ESM::Cell> &cStore = const_cast<MWWorld::Store<ESM::Cell>&>(store.get<ESM::Cell>());
        ESM::Cell *cellAlt = const_cast<ESM::Cell*>(cStore.searchOrCreate(cMRef.mTarget[0], cMRef.mTarget[1]));
        
        // Get regular moved reference data. Adapted from CellStore::loadRefs. Maybe we can optimize the following
        //  implementation when the oher implementation works as well.
        getNextRef(esm, ref);
        std::string lowerCase;

        std::transform (ref.mRefID.begin(), ref.mRefID.end(), std::back_inserter (lowerCase),
            (int(*)(int)) std::tolower);
                
        // Add data required to make reference appear in the correct cell.
        // We should not need to test for duplicates, as this part of the code is pre-cell merge.
        mMovedRefs.push_back(cMRef);
        // But there may be duplicates here!
        ESM::CellRefTracker::iterator iter = std::find(cellAlt->mLeasedRefs.begin(), cellAlt->mLeasedRefs.end(), ref.mRefnum);
        if (iter == cellAlt->mLeasedRefs.end())
          cellAlt->mLeasedRefs.push_back(ref);
        else
          *iter = ref;
    }

    // Save position of the cell references and move on
    mContextList.push_back(esm.getContext());
    esm.skipRecord();
}

void Cell::save(ESMWriter &esm)
{
    mData.mFlags = htole32(mData.mFlags);
    mData.mX = htole32(mData.mX);
    mData.mY = htole32(mData.mY);
    esm.writeHNT("DATA", mData, 12);

    if (mData.mFlags & Interior)
    {
        if (mWater != -1) {
            if (mWaterInt) {
                int water =
                    (mWater >= 0) ? (int) (mWater + 0.5) : (int) (mWater - 0.5);
                water = htole32(water);
                esm.writeHNT("INTV", water);
            } else {
                mWater = htole_float(mWater);
                esm.writeHNT("WHGT", mWater);
            }
        }

        if (mData.mFlags & QuasiEx)
            esm.writeHNOCString("RGNN", mRegion);
        else
        {
            mAmbi.mAmbient = htole32(mAmbi.mAmbient);
            mAmbi.mSunlight = htole32(mAmbi.mSunlight);
            mAmbi.mFog = htole32(mAmbi.mFog);
            mAmbi.mFogDensity = htole_float(mAmbi.mFogDensity);
            esm.writeHNT("AMBI", mAmbi, 16);
        }
    }
    else
    {
        esm.writeHNOCString("RGNN", mRegion);
        if (mMapColor != 0)
        {
            mMapColor = htole32(mMapColor);
            esm.writeHNT("NAM5", mMapColor);
        }
    }

    if (mNAM0 != 0)
    {
        mNAM0 = htole32(mNAM0);
        esm.writeHNT("NAM0", mNAM0);
    }
}

void Cell::restore(ESMReader &esm, int iCtx) const
{
    esm.restoreContext(mContextList[iCtx]);
}

std::string Cell::getDescription() const
{
    if (mData.mFlags & Interior)
    {
        return mName;
    }
    else
    {
        std::ostringstream stream;
        stream << mData.mX << ", " << mData.mY;
        return stream.str();
    }
}

bool Cell::getNextRef(ESMReader &esm, CellRef &ref)
{
    // TODO: Try and document reference numbering, I don't think this has been done anywhere else.
    if (!esm.hasMoreSubs())
        return false;

    // NOTE: We should not need this check. It is a safety check until we have checked
    // more plugins, and how they treat these moved references.
    if (esm.isNextSub("MVRF")) {
        esm.skipRecord(); // skip MVRF
        esm.skipRecord(); // skip CNDT
        // That should be it, I haven't seen any other fields yet.
    }

    esm.getHNT(ref.mRefnum, "FRMR");
    ref.mRefnum = le32toh(ref.mRefnum);

    ref.mRefID = esm.getHNString("NAME");
    
    // Identify references belonging to a parent file and adapt the ID accordingly.
    int local = (ref.mRefnum & 0xff000000) >> 24;
    size_t global = esm.getIndex() + 1;
    if (local)
    {
        // If the most significant 8 bits are used, then this reference already exists.
        // In this case, do not spawn a new reference, but overwrite the old one.
        ref.mRefnum &= 0x00ffffff; // delete old plugin ID
        const ESM::ESMReader::MasterList &masters = esm.getMasters();
        global = masters[local-1].index + 1;
        ref.mRefnum |= global << 24; // insert global plugin ID
    }
    else
    {
        // This is an addition by the present plugin. Set the corresponding plugin index.
        ref.mRefnum |= global << 24; // insert global plugin ID
    }

    ref.mScale = 1.0;
    if (esm.isNextSub("XSCL"))
    {
        esm.getHT(ref.mScale);
        ref.mScale = letoh_float(ref.mScale);
    }

    // TODO: support loading references from saves, there are tons of keys not recognized yet.
    // The following is just an incomplete list.
    if (esm.isNextSub("ACTN"))
        esm.skipHSub();
    if (esm.isNextSub("STPR"))
        esm.skipHSub();
    if (esm.isNextSub("ACDT"))
        esm.skipHSub();
    if (esm.isNextSub("ACSC"))
        esm.skipHSub();
    if (esm.isNextSub("ACSL"))
        esm.skipHSub();
    if (esm.isNextSub("CHRD"))
        esm.skipHSub();
    else if (esm.isNextSub("CRED")) // ???
        esm.skipHSub();

    ref.mOwner = esm.getHNOString("ANAM");
    ref.mGlob = esm.getHNOString("BNAM");
    ref.mSoul = esm.getHNOString("XSOL");

    ref.mFaction = esm.getHNOString("CNAM");

    ref.mFactIndex = -2;
    if (esm.isNextSub("INDX"))
    {
        esm.getHT(ref.mFactIndex);
        ref.mFactIndex = le32toh(ref.mFactIndex);
    }

    ref.mCharge = -1.0;
    if (esm.isNextSub("XCHG"))
    {
        esm.getHT(ref.mCharge);
        ref.mCharge = letoh_float(ref.mCharge);
    }

    ref.mIntv = -1;
    if (esm.isNextSub("INTV"))
    {
        esm.getHT(ref.mIntv);
        ref.mIntv = le32toh(ref.mIntv);
    }

    ref.mNam9 = 0;
    if (esm.isNextSub("NAM9"))
    {
        esm.getHT(ref.mNam9);
        ref.mNam9 = le32toh(ref.mNam9);
    }

    // Present for doors that teleport you to another cell.
    if (esm.isNextSub("DODT"))
    {
        ref.mTeleport = true;
        esm.getHT(ref.mDoorDest);
        for (size_t i = 0; i < 3; i++)
            ref.mDoorDest.pos[i] = letoh_float(ref.mDoorDest.pos[i]);
        for (size_t i = 0; i < 3; i++)
            ref.mDoorDest.rot[i] = letoh_float(ref.mDoorDest.rot[i]);
        ref.mDestCell = esm.getHNOString("DNAM");
    } else {
        ref.mTeleport = false;
    }

    // Integer, despite the name suggesting otherwise
    ref.mLockLevel = -1;
    if (esm.isNextSub("FLTV"))
    {
        esm.getHT(ref.mLockLevel);
        ref.mLockLevel = le32toh(ref.mLockLevel);
    }

    ref.mKey = esm.getHNOString("KNAM");
    ref.mTrap = esm.getHNOString("TNAM");

    ref.mUnam = -1;
    if (esm.isNextSub("UNAM"))
    {
        esm.getHT(ref.mUnam);
    }

    // Integer, despite the name suggesting otherwise
    ref.mFltv = 0;
    if (esm.isNextSub("FLTV"))
    {
        esm.getHT(ref.mFltv);
        ref.mFltv = le32toh(ref.mFltv);
    }

    esm.getHNT(ref.mPos, "DATA", 24);
    for (size_t i = 0; i < 3; i++)
        ref.mPos.pos[i] = letoh_float(ref.mPos.pos[i]);
    for (size_t i = 0; i < 3; i++)
        ref.mPos.rot[i] = letoh_float(ref.mPos.rot[i]);

    // Number of references in the cell? Maximum once in each cell,
    // but not always at the beginning, and not always right. In other
    // words, completely useless.
    // Update: Well, maybe not completely useless. This might actually be
    //  number_of_references + number_of_references_moved_here_Across_boundaries,
    //  and could be helpful for collecting these weird moved references.
    ref.mNam0 = 0;
    if (esm.isNextSub("NAM0"))
    {
        esm.getHT(ref.mNam0);
        ref.mNam0 = le32toh(ref.mNam0);
    }
    
    if (esm.isNextSub("DELE")) {
        esm.skipHSub();
        ref.mDeleted = 2; // Deleted, will not respawn.
        // TODO: find out when references do respawn.
    } else
        ref.mDeleted = 0;

    return true;
}

bool Cell::getNextMVRF(ESMReader &esm, MovedCellRef &mref)
{
    esm.getHT(mref.mRefnum);
    mref.mRefnum = le32toh(mref.mRefnum);
    if (esm.isNextSub("DELE")) {
        esm.getHT(mref.mTarget);
        mref.mTarget[0] = le32toh(mref.mTarget[0]);
        mref.mTarget[1] = le32toh(mref.mTarget[1]);
    }

    // Identify references belonging to a parent file and adapt the ID accordingly.
    int local = (mref.mRefnum & 0xff000000) >> 24;
    size_t global = esm.getIndex() + 1;
    mref.mRefnum &= 0x00ffffff; // delete old plugin ID
    const ESM::ESMReader::MasterList &masters = esm.getMasters();
    global = masters[local-1].index + 1;
    mref.mRefnum |= global << 24; // insert global plugin ID

    return true;
}

}
