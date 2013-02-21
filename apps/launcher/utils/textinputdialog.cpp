/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include <QDialogButtonBox>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QValidator>

#include <components/fileorderlist/utils/lineedit.hpp>

#include "textinputdialog.hpp"

TextInputDialog::TextInputDialog(const QString& title, const QString &text, QWidget *parent) :
    QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    mButtonBox = new QDialogButtonBox(this);
    mButtonBox->addButton(QDialogButtonBox::Ok);
    mButtonBox->addButton(QDialogButtonBox::Cancel);

    setMaximumHeight(height());
    setOkButtonEnabled(false);
    setModal(true);

    // Messageboxes on mac have no title
#ifndef Q_OS_MAC
    setWindowTitle(title);
#else
    Q_UNUSED(title);
#endif

    QLabel *label = new QLabel(this);
    label->setText(text);

    // Line edit
    QValidator *validator = new QRegExpValidator(QRegExp("^[a-zA-Z0-9_]*$"), this); // Alpha-numeric + underscore
    mLineEdit = new LineEdit(this);
    mLineEdit->setValidator(validator);
    mLineEdit->setCompleter(0);

    QVBoxLayout *dialogLayout = new QVBoxLayout(this);
    dialogLayout->addWidget(label);
    dialogLayout->addWidget(mLineEdit);
    dialogLayout->addWidget(mButtonBox);

    connect(mButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(mButtonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

int TextInputDialog::exec()
{
    mLineEdit->clear();
    mLineEdit->setFocus();
    return QDialog::exec();
}

void TextInputDialog::setOkButtonEnabled(bool enabled)
{

    QPushButton *okButton = mButtonBox->button(QDialogButtonBox::Ok);
    okButton->setEnabled(enabled);
}
