/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSM_TOOLS_STAGE_H
#define CSM_TOOLS_STAGE_H

#include <vector>
#include <string>

namespace CSMTools
{
    class Stage
    {
        public:

            virtual ~Stage();

            virtual int setup() = 0;
            ///< \return number of steps

            virtual void perform (int stage, std::vector<std::string>& messages) = 0;
            ///< Messages resulting from this tage will be appended to \a messages.
    };
}

#endif

