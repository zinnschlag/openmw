/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QMainWindow>

#include <components/files/configurationmanager.hpp>
#include <components/settings/settings.hpp>

class QListWidget;
class QListWidgetItem;
class QStackedWidget;
class QStringList;
class QStringListModel;
class QString;

class PlayPage;
class GraphicsPage;
class DataFilesPage;

class MainDialog : public QMainWindow
{
    Q_OBJECT

public:
    MainDialog();

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void play();
    bool setup();

private:
    void createIcons();
    void createPages();
    void closeEvent(QCloseEvent *event);

    QListWidget *mIconWidget;
    QStackedWidget *mPagesWidget;

    PlayPage *mPlayPage;
    GraphicsPage *mGraphicsPage;
    DataFilesPage *mDataFilesPage;

    Files::ConfigurationManager mCfgMgr;
    Settings::Manager mSettings;
};

#endif
