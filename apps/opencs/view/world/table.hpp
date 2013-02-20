/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CSV_WORLD_TABLE_H
#define CSV_WORLD_TABLE_H

#include <vector>
#include <string>

#include <QTableView>

class QUndoStack;
class QAction;

namespace CSMWorld
{
    class Data;
    class UniversalId;
    class IdTableProxyModel;
    class IdTable;
}

namespace CSVWorld
{
    class CommandDelegate;

    ///< Table widget
    class Table : public QTableView
    {
            Q_OBJECT

            std::vector<CommandDelegate *> mDelegates;
            QUndoStack& mUndoStack;
            QAction *mCreateAction;
            QAction *mRevertAction;
            QAction *mDeleteAction;
            CSMWorld::IdTableProxyModel *mProxyModel;
            CSMWorld::IdTable *mModel;
            bool mEditLock;

        private:

            void contextMenuEvent (QContextMenuEvent *event);

            std::vector<std::string> listRevertableSelectedIds() const;

            std::vector<std::string> listDeletableSelectedIds() const;

        public:

            Table (const CSMWorld::UniversalId& id, CSMWorld::Data& data, QUndoStack& undoStack, bool createAndDelete);
            ///< \param createAndDelete Allow creation and deletion of records.

            void setEditLock (bool locked);

            CSMWorld::UniversalId getUniversalId (int row) const;

        private slots:

            void createRecord();

            void revertRecord();

            void deleteRecord();
    };
}

#endif
