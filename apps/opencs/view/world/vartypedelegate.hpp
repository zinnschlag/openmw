/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSV_WORLD_VARTYPEDELEGATE_H
#define CSV_WORLD_VARTYPEDELEGATE_H

#include "enumdelegate.hpp"

namespace CSVWorld
{
    class VarTypeDelegate : public EnumDelegate
    {
        private:

            virtual void addCommands (QAbstractItemModel *model,
                const QModelIndex& index, int type) const;

        public:

            VarTypeDelegate (const std::vector<std::pair<int, QString> >& values,
                QUndoStack& undoStack, QObject *parent);
    };

    class VarTypeDelegateFactory : public CommandDelegateFactory
    {
            std::vector<std::pair<int, QString> > mValues;

        public:

            VarTypeDelegateFactory (ESM::VarType type0 = ESM::VT_Unknown,
                ESM::VarType type1 = ESM::VT_Unknown, ESM::VarType type2 = ESM::VT_Unknown,
                ESM::VarType type3 = ESM::VT_Unknown);

            virtual CommandDelegate *makeDelegate (QUndoStack& undoStack, QObject *parent) const;
            ///< The ownership of the returned CommandDelegate is transferred to the caller.

            void add (ESM::VarType type);
    };
}

#endif
