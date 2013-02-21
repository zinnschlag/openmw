/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWBASE_INPUTMANAGER_H
#define GAME_MWBASE_INPUTMANAGER_H

#include <string>

#include <components/settings/settings.hpp>

namespace MWBase
{
    /// \brief Interface for input manager (implemented in MWInput)
    class InputManager
    {
            InputManager (const InputManager&);
            ///< not implemented

            InputManager& operator= (const InputManager&);
            ///< not implemented

        public:

            InputManager() {}

            virtual ~InputManager() {}

            virtual void update(float dt, bool loading) = 0;

            virtual void changeInputMode(bool guiMode) = 0;

            virtual void processChangedSettings(const Settings::CategorySettingVector& changed) = 0;

            virtual void setDragDrop(bool dragDrop) = 0;

            virtual void toggleControlSwitch (const std::string& sw, bool value) = 0;
            virtual bool getControlSwitch (const std::string& sw) = 0;

            virtual std::string getActionDescription (int action) = 0;
            virtual std::string getActionBindingName (int action) = 0;
            virtual std::vector<int> getActionSorting () = 0;
            virtual int getNumActions() = 0;
            virtual void enableDetectingBindingMode (int action) = 0;
            virtual void resetToDefaultBindings() = 0;
    };
}

#endif
