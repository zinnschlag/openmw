/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TEXTINPUTDIALOG_HPP
#define TEXTINPUTDIALOG_HPP

#include <QDialog>
//#include "lineedit.hpp"

class QDialogButtonBox;
class LineEdit;

class TextInputDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextInputDialog(const QString& title, const QString &text, QWidget *parent = 0);
    inline LineEdit *lineEdit() { return mLineEdit; }
    void setOkButtonEnabled(bool enabled);

    LineEdit *mLineEdit;

    int exec();

private:
    QDialogButtonBox *mButtonBox;

    
};

#endif // TEXTINPUTDIALOG_HPP
