/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_LIST_HPP
#define MWGUI_LIST_HPP

#include <MyGUI.h>

namespace MWGui
{
    namespace Widgets
    {
        /**
         * \brief a very simple list widget that supports word-wrapping entries
         * \note if the width or height of the list changes, you must call adjustSize() method
         */
        class MWList : public MyGUI::Widget
        {
            MYGUI_RTTI_DERIVED(MWList)
        public:
            MWList();

            typedef MyGUI::delegates::CMultiDelegate1<std::string> EventHandle_String;
            typedef MyGUI::delegates::CMultiDelegate1<MyGUI::Widget*> EventHandle_Widget;

            /**
             * Event: Item selected with the mouse.
             * signature: void method(std::string itemName)
             */
            EventHandle_String eventItemSelected;

            /**
             * Event: Item selected with the mouse.
             * signature: void method(MyGUI::Widget* sender)
             */
            EventHandle_Widget eventWidgetSelected;


            /**
             * Call after the size of the list changed, or items were inserted/removed
             */
            void adjustSize();

            void addItem(const std::string& name);
            void addSeparator(); ///< add a seperator between the current and the next item.
            void removeItem(const std::string& name);
            bool hasItem(const std::string& name);
            unsigned int getItemCount();
            std::string getItemNameAt(unsigned int at); ///< \attention if there are separators, this method will return "" at the place where the separator is
            void clear();

            MyGUI::Widget* getItemWidget(const std::string& name);
            ///< get widget for an item name, useful to set up tooltip

        protected:
            void initialiseOverride();

            void redraw(bool scrollbarShown = false);

            void onMouseWheel(MyGUI::Widget* _sender, int _rel);
            void onItemSelected(MyGUI::Widget* _sender);

        private:
            MyGUI::ScrollView* mScrollView;
            MyGUI::Widget* mClient;

            std::vector<std::string> mItems;

            int mItemHeight; // height of all items
        };
    }
}

#endif
