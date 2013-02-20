/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "lineedit.hpp"
#include <QToolButton>
#include <QStyle>

LineEdit::LineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    mClearButton = new QToolButton(this);
    QPixmap pixmap(":images/clear.png");
    mClearButton->setIcon(QIcon(pixmap));
    mClearButton->setIconSize(pixmap.size());
    mClearButton->setCursor(Qt::ArrowCursor);
    mClearButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");
    mClearButton->hide();
    connect(mClearButton, SIGNAL(clicked()), this, SLOT(clear()));
    connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(updateCloseButton(const QString&)));
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    setStyleSheet(QString("QLineEdit { padding-right: %1px; } ").arg(mClearButton->sizeHint().width() + frameWidth + 1));
    QSize msz = minimumSizeHint();
    setMinimumSize(qMax(msz.width(), mClearButton->sizeHint().height() + frameWidth * 2 + 2),
                   qMax(msz.height(), mClearButton->sizeHint().height() + frameWidth * 2 + 2));
}

void LineEdit::resizeEvent(QResizeEvent *)
{
    QSize sz = mClearButton->sizeHint();
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    mClearButton->move(rect().right() - frameWidth - sz.width(),
                      (rect().bottom() + 1 - sz.height())/2);
}

void LineEdit::updateCloseButton(const QString& text)
{
    mClearButton->setVisible(!text.isEmpty());
}


