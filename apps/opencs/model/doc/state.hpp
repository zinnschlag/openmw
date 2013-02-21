/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSM_DOC_STATE_H
#define CSM_DOC_STATE_H

namespace CSMDoc
{
        enum State
        {
                State_Modified = 1,
                State_Locked = 2,
                State_Operation = 4,

                State_Saving = 8,
                State_Verifying = 16,
                State_Compiling = 32, // not implemented yet
                State_Searching = 64 // not implemented yet
        };
}

#endif
