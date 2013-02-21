/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_BIRTH_H
#define MWGUI_BIRTH_H

#include "window_base.hpp"

/*
  This file contains the dialog for choosing a birth sign.
  Layout is defined by resources/mygui/openmw_chargen_race.layout.
 */

namespace MWGui
{
    class BirthDialog : public WindowBase
    {
    public:
        BirthDialog(MWBase::WindowManager& parWindowManager);

        enum Gender
        {
            GM_Male,
            GM_Female
        };

        const std::string &getBirthId() const { return mCurrentBirthId; }
        void setBirthId(const std::string &raceId);

        void setNextButtonShow(bool shown);
        virtual void open();

        // Events
        typedef MyGUI::delegates::CMultiDelegate0 EventHandle_Void;

        /** Event : Back button clicked.\n
            signature : void method()\n
        */
        EventHandle_Void eventBack;

    protected:
        void onSelectBirth(MyGUI::ListBox* _sender, size_t _index);

        void onOkClicked(MyGUI::Widget* _sender);
        void onBackClicked(MyGUI::Widget* _sender);

    private:
        void updateBirths();
        void updateSpells();

        MyGUI::ListBox* mBirthList;
        MyGUI::WidgetPtr  mSpellArea;
        MyGUI::ImageBox* mBirthImage;
        std::vector<MyGUI::WidgetPtr> mSpellItems;

        std::string mCurrentBirthId;
    };
}
#endif
