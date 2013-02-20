/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DATAFILESLIST_H
#define DATAFILESLIST_H

#include <QWidget>
#include <QModelIndex>
#include <components/files/collections.hpp>


class QTableView;
class QSortFilterProxyModel;
class QSettings;
class QAction;
class QToolBar;
class QMenu;
class ProfilesComboBox;
class DataFilesModel;

class TextInputDialog;

namespace Files { struct ConfigurationManager; }

class DataFilesList : public QWidget
{
    Q_OBJECT

public:
    DataFilesList(Files::ConfigurationManager& cfg, QWidget *parent = 0);

    bool setupDataFiles(Files::PathContainer dataDirs, const QString encoding);
    void selectedFiles(std::vector<boost::filesystem::path>& paths);
    void uncheckAll();
    QStringList checkedFiles();
    void setCheckState(const QString& element, Qt::CheckState);
    

public slots:
    void setCheckState(QModelIndex index);

    void filterChanged(const QString filter);
    void showContextMenu(const QPoint &point);

    // Action slots
//    void moveUp();
//    void moveDown();
//    void moveTop();
//    void moveBottom();
    void check();
    void uncheck();
    void refresh();

private:
    DataFilesModel *mMastersModel;
    DataFilesModel *mPluginsModel;

    QSortFilterProxyModel *mPluginsProxyModel;

    QTableView *mMastersTable;
    QTableView *mPluginsTable;

    QMenu *mContextMenu;

//    QAction *mMoveUpAction;
//    QAction *mMoveDownAction;
//    QAction *mMoveTopAction;
//    QAction *mMoveBottomAction;
    QAction *mCheckAction;
    QAction *mUncheckAction;

    Files::ConfigurationManager &mCfgMgr;

//    const QStringList checkedPlugins();
//    const QStringList selectedMasters();

    void createActions();
};

#endif
