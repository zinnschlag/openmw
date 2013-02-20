/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "filedialog.hpp"
#include <QDialogButtonBox>
#include <QPushButton>

FileDialog::FileDialog(QWidget *parent)
    : QFileDialog(parent)
{
    // Remove the default Choose button to prevent it being updated elsewhere
    QDialogButtonBox *box = qFindChild<QDialogButtonBox*>(this);
    Q_ASSERT(box);
    box->removeButton(box->button(QDialogButtonBox::Open));

    // Add our own button so we can disable/enable it
    mChooseButton = new QPushButton(tr("&Choose"));
    mChooseButton->setIcon(QIcon::fromTheme("document-open"));
    mChooseButton->setEnabled(false);
    box->addButton(mChooseButton, QDialogButtonBox::AcceptRole);

    connect(this, SIGNAL(directoryEntered(const QString&)), this, SLOT(updateChooseButton(const QString&)));
    emit directoryEntered(QDir::currentPath());
}

QString FileDialog::getExistingDirectory(QWidget *parent,
                                          const QString &caption,
                                          const QString &dir,
                                          Options options)
{
    // create a non-native file dialog
    FileDialog dialog;
    dialog.setFileMode(DirectoryOnly);
    dialog.setOptions(options |= QFileDialog::DontUseNativeDialog | QFileDialog::ShowDirsOnly | QFileDialog::ReadOnly);

    if (!caption.isEmpty())
        dialog.setWindowTitle(caption);

    if (!dir.isEmpty())
        dialog.setDirectory(dir);

    if (dialog.exec() == QDialog::Accepted) {
        return dialog.selectedFiles().value(0);
    }
    return QString();
}

void FileDialog::updateChooseButton(const QString &directory)
{
    QDir currentDir = QDir(directory);
    currentDir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    currentDir.setNameFilters(QStringList() << "*.esm" << "*.esp");

    if (!currentDir.entryList().isEmpty()) {
        // There are data files in the current dir
        mChooseButton->setEnabled(true);
    } else {
        mChooseButton->setEnabled(false);
    }
}
