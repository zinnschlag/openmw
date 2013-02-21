/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FILEDIALOG_HPP
#define FILEDIALOG_HPP

#include <QFileDialog>

class QPushButton;

class FileDialog : public QFileDialog
{
    Q_OBJECT

public:
    FileDialog(QWidget *parent = 0);

    static QString getExistingDirectory(QWidget *parent = 0,
                                            const QString &caption = QString(),
                                            const QString &dir = QString(),
                                            Options options = ShowDirsOnly);

private slots:
    void updateChooseButton(const QString &directory);

private:
    QPushButton *mChooseButton;
};


#endif // FILEDIALOG_HPP
