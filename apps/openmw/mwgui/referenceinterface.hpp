/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_REFERENCEINTERFACE_H
#define MWGUI_REFERENCEINTERFACE_H

#include "../mwworld/ptr.hpp"

namespace MWGui
{
    /// \brief this class is intended for GUI interfaces that access an MW-Reference
    /// for example dialogue window accesses an NPC, or Container window accesses a Container
    /// these classes have to be automatically closed if the reference becomes unavailable
    /// make sure that checkReferenceAvailable() is called every frame and that onReferenceUnavailable() has been overridden
    class ReferenceInterface
    {
    public:
        ReferenceInterface();
        virtual ~ReferenceInterface();

        void checkReferenceAvailable(); ///< closes the window, if the MW-reference has become unavailable

    protected:
        virtual void onReferenceUnavailable() = 0; ///< called when reference has become unavailable

        MWWorld::Ptr mPtr;

    private:
        MWWorld::CellStore* mCurrentPlayerCell;
    };
}

#endif
