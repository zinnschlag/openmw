/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_ALCHEMY_H
#define MWGUI_ALCHEMY_H

#include <vector>

#include "../mwmechanics/alchemy.hpp"

#include "window_base.hpp"
#include "container.hpp"
#include "widgets.hpp"

namespace MWGui
{
    class AlchemyWindow : public WindowBase, public ContainerBase
    {
    public:
        AlchemyWindow(MWBase::WindowManager& parWindowManager);

        virtual void open();

    protected:
        MyGUI::Button* mCreateButton;
        MyGUI::Button* mCancelButton;

        MyGUI::Widget* mEffectsBox;

        MyGUI::EditBox* mNameEdit;

        void onCancelButtonClicked(MyGUI::Widget* _sender);
        void onCreateButtonClicked(MyGUI::Widget* _sender);
        void onIngredientSelected(MyGUI::Widget* _sender);

        virtual void onSelectedItemImpl(MWWorld::Ptr item);
        virtual std::vector<MWWorld::Ptr> itemsToIgnore();

        void removeIngredient(MyGUI::Widget* ingredient);

        virtual void onReferenceUnavailable() { ; }

        void update();
        
    private:

        MWMechanics::Alchemy mAlchemy;

        std::vector<MyGUI::ImageBox *> mApparatus;
        std::vector<MyGUI::ImageBox *> mIngredients;
    };
}

#endif
