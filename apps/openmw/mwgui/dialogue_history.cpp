/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "dialogue_history.hpp"

#include "../mwbase/windowmanager.hpp"

#include "widgets.hpp"

#include "../mwworld/esmstore.hpp"

#include <iostream>
#include <iterator>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using namespace MWGui;
using namespace Widgets;

MyGUI::UString DialogueHistory::getColorAtPos(size_t _pos)
{
    MyGUI::UString colour = MyGUI::TextIterator::convertTagColour(getTextColour());
    MyGUI::TextIterator iterator(getCaption());
    while(iterator.moveNext())
    {
        size_t pos = iterator.getPosition();
        iterator.getTagColour(colour);
        if (pos < _pos)
            continue;
        else if (pos == _pos)
            break;
    }
    return colour;
}

MyGUI::UString DialogueHistory::getColorTextAt(size_t _pos)
{
    bool breakOnNext = false;
    MyGUI::UString colour = MyGUI::TextIterator::convertTagColour(getTextColour());
    MyGUI::UString colour2 = colour;
    MyGUI::TextIterator iterator(getCaption());
    MyGUI::TextIterator col_start = iterator;
    while(iterator.moveNext())
    {
        size_t pos = iterator.getPosition();
        iterator.getTagColour(colour);
        if(colour != colour2)
        {
            if(breakOnNext)
            {
                return getOnlyText().substr(col_start.getPosition(), iterator.getPosition()-col_start.getPosition());
            }
            col_start = iterator;
            colour2 = colour;
        }
        if (pos < _pos)
            continue;
        else if (pos == _pos)
        {
            breakOnNext = true;
        }
    }
    return "";
}

void DialogueHistory::addDialogHeading(const MyGUI::UString& parText)
{
    MyGUI::UString head("\n#D8C09A");
    head.append(parText);
    head.append("#B29154\n");
    addText(head);
}

void DialogueHistory::addDialogText(const MyGUI::UString& parText)
{
    addText(parText);
    addText("\n");
}
