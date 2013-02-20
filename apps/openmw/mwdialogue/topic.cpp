/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "topic.hpp"

#include "../mwworld/esmstore.hpp"

namespace MWDialogue
{
    Topic::Topic()
    {}

    Topic::Topic (const std::string& topic)
    : mTopic (topic)
    {}

    Topic::~Topic()
    {}

    void Topic::addEntry (const JournalEntry& entry)
    {
        if (entry.mTopic!=mTopic)
            throw std::runtime_error ("topic does not match: " + mTopic);

        for (TEntryIter iter = begin(); iter!=end(); ++iter)
            if (*iter==entry.mInfoId)
                return;

        mEntries.push_back (entry.mInfoId);
    }

    Topic::TEntryIter Topic::begin() const
    {
        return mEntries.begin();
    }

    Topic::TEntryIter Topic::end() const
    {
        return mEntries.end();
    }

    JournalEntry Topic::getEntry (const std::string& infoId) const
    {
        return JournalEntry (mTopic, infoId);
    }
}
