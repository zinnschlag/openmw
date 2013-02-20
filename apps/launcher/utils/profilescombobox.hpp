/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PROFILESCOMBOBOX_HPP
#define PROFILESCOMBOBOX_HPP

#include <QComboBox>

class QString;

class QRegExpValidator;

class ProfilesComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit ProfilesComboBox(QWidget *parent = 0);
    void setEditEnabled(bool editable);
    
signals:
    void profileChanged(const QString &previous, const QString &current);
    void profileRenamed(const QString &oldName, const QString &newName);
    
private slots:
    void slotReturnPressed();
    void slotIndexChanged(int index);

private:
    QString mOldProfile;
    QRegExpValidator *mValidator;
};

#endif // PROFILESCOMBOBOX_HPP
