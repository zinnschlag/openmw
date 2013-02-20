/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSM_TOOLS_MANDATORYID_H
#define CSM_TOOLS_MANDATORYID_H

#include <string>
#include <vector>

#include "../world/universalid.hpp"

#include "stage.hpp"

namespace CSMWorld
{
    class IdCollectionBase;
}

namespace CSMTools
{
    /// \brief Verify stage: make sure that records with specific IDs exist.
    class MandatoryIdStage : public Stage
    {
            const CSMWorld::IdCollectionBase& mIdCollection;
            CSMWorld::UniversalId mCollectionId;
            std::vector<std::string> mIds;

        public:

            MandatoryIdStage (const CSMWorld::IdCollectionBase& idCollection, const CSMWorld::UniversalId& collectionId,
                const std::vector<std::string>& ids);

            virtual int setup();
            ///< \return number of steps

            virtual void perform (int stage, std::vector<std::string>& messages);
            ///< Messages resulting from this tage will be appended to \a messages.
    };
}

#endif
