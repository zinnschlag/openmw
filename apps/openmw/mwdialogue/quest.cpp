/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "quest.hpp"

#include "../mwworld/esmstore.hpp"

#include "../mwbase/environment.hpp"
#include "../mwbase/world.hpp"

namespace MWDialogue
{
    Quest::Quest()
    : Topic(), mIndex (0), mFinished (false)
    {}

    Quest::Quest (const std::string& topic)
    : Topic (topic), mIndex (0), mFinished (false)
    {}

    const std::string Quest::getName() const
    {
        const ESM::Dialogue *dialogue =
            MWBase::Environment::get().getWorld()->getStore().get<ESM::Dialogue>().find (mTopic);

        for (std::vector<ESM::DialInfo>::const_iterator iter (dialogue->mInfo.begin());
            iter!=dialogue->mInfo.end(); ++iter)
            if (iter->mQuestStatus==ESM::DialInfo::QS_Name)
                return iter->mResponse;

        return "";
    }

    int Quest::getIndex() const
    {
        return mIndex;
    }

    void Quest::setIndex (int index)
    {
        const ESM::Dialogue *dialogue =
            MWBase::Environment::get().getWorld()->getStore().get<ESM::Dialogue>().find (mTopic);

        for (std::vector<ESM::DialInfo>::const_iterator iter (dialogue->mInfo.begin());
            iter!=dialogue->mInfo.end(); ++iter)
            if (iter->mData.mDisposition==index && iter->mQuestStatus!=ESM::DialInfo::QS_Name)
            {
                mIndex = index;

                if (iter->mQuestStatus==ESM::DialInfo::QS_Finished)
                    mFinished = true;
                else if (iter->mQuestStatus==ESM::DialInfo::QS_Restart)
                    mFinished = false;

                return;
            }

        throw std::runtime_error ("unknown journal index for topic " + mTopic);
    }

    bool Quest::isFinished() const
    {
        return mFinished;
    }

    void Quest::addEntry (const JournalEntry& entry)
    {
        int index = -1;

        const ESM::Dialogue *dialogue =
            MWBase::Environment::get().getWorld()->getStore().get<ESM::Dialogue>().find (entry.mTopic);

        for (std::vector<ESM::DialInfo>::const_iterator iter (dialogue->mInfo.begin());
            iter!=dialogue->mInfo.end(); ++iter)
            if (iter->mId == entry.mInfoId)
            {
                index = iter->mData.mDisposition; /// \todo cleanup info structure
                break;
            }

        if (index==-1)
            throw std::runtime_error ("unknown journal entry for topic " + mTopic);

        setIndex (index);

        for (TEntryIter iter (mEntries.begin()); iter!=mEntries.end(); ++iter)
            if (*iter==entry.mInfoId)
                return;

        mEntries.push_back (entry.mInfoId);
    }
}
