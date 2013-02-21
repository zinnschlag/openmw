/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWDIALOG_TOPIC_H
#define GAME_MWDIALOG_TOPIC_H

#include <string>
#include <vector>

#include "journalentry.hpp"

namespace MWDialogue
{
    /// \brief Collection of seen responses for a topic
    class Topic
    {
        public:

            typedef std::vector<std::string> TEntryContainer;
            typedef TEntryContainer::const_iterator TEntryIter;

        protected:

            std::string mTopic;
            TEntryContainer mEntries; // info-IDs

        public:

            Topic();

            Topic (const std::string& topic);

            virtual ~Topic();

            virtual void addEntry (const JournalEntry& entry);
            ///< Add entry
            ///
            /// \note Redundant entries are ignored.

            std::string const & getName () const { return mTopic; }

            TEntryIter begin() const;
            ///< Iterator pointing to the begin of the journal for this topic.

            TEntryIter end() const;
            ///< Iterator pointing past the end of the journal for this topic.

            JournalEntry getEntry (const std::string& infoId) const;
    };
}

#endif
