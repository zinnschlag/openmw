/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWDIALOGUE_JOURNALENTRY_H
#define GAME_MWDIALOGUE_JOURNALENTRY_H

#include <string>

namespace MWWorld 
{
    struct ESMStore;
}

namespace MWDialogue
{
    /// \brief A quest or dialogue entry
    struct JournalEntry
    {
        std::string mTopic;
        std::string mInfoId;

        JournalEntry();

        JournalEntry (const std::string& topic, const std::string& infoId);

        std::string getText (const MWWorld::ESMStore& store) const;

        static JournalEntry makeFromQuest (const std::string& topic, int index);

        static std::string idFromIndex (const std::string& topic, int index);
    };

    /// \biref A quest entry with a timestamp.
    struct StampedJournalEntry : public JournalEntry
    {
        int mDay;
        int mMonth;
        int mDayOfMonth;

        StampedJournalEntry();

        StampedJournalEntry (const std::string& topic, const std::string& infoId,
            int day, int month, int dayOfMonth);

        static StampedJournalEntry makeFromQuest (const std::string& topic, int index);
    };
}

#endif
