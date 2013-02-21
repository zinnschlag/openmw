/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PLAYPAGE_H
#define PLAYPAGE_H

#include <QWidget>

class QComboBox;
class QPushButton;

class PlayPage : public QWidget
{
    Q_OBJECT

public:
    PlayPage(QWidget *parent = 0);

    QComboBox *mProfilesComboBox;
    QPushButton *mPlayButton;

};

#endif