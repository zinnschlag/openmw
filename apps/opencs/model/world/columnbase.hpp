/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSM_WOLRD_COLUMNBASE_H
#define CSM_WOLRD_COLUMNBASE_H

#include <string>

#include <Qt>
#include <QVariant>

#include "record.hpp"

namespace CSMWorld
{
    struct ColumnBase
    {
        enum Roles
        {
            Role_Flags = Qt::UserRole,
            Role_Display = Qt::UserRole+1
        };

        enum Flags
        {
            Flag_Table = 1, // column should be displayed in table view
            Flag_Dialogue = 2 // column should be displayed in dialogue view
        };

        enum Display
        {
            Display_String,
            Display_Integer,
            Display_Float,
            Display_Var,
            Display_VarType
        };

        std::string mTitle;
        int mFlags;
        Display mDisplayType;

        ColumnBase (const std::string& title, Display displayType, int flag);

        virtual ~ColumnBase();

        virtual bool isEditable() const = 0;

        virtual bool isUserEditable() const;
        ///< Can this column be edited directly by the user?

    };

    template<typename ESXRecordT>
    struct Column : public ColumnBase
    {
        std::string mTitle;
        int mFlags;

        Column (const std::string& title, Display displayType, int flags = Flag_Table | Flag_Dialogue)
        : ColumnBase (title, displayType, flags) {}

        virtual QVariant get (const Record<ESXRecordT>& record) const = 0;

        virtual void set (Record<ESXRecordT>& record, const QVariant& data)
        {
            throw std::logic_error ("Column " + mTitle + " is not editable");
        }
    };
}

#endif
