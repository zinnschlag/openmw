/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/


#include "startup.hpp"

#include <QPushButton>
#include <QHBoxLayout>

CSVDoc::StartupDialogue::StartupDialogue()
{
    QHBoxLayout *layout = new QHBoxLayout (this);

    QPushButton *createDocument = new QPushButton ("new", this);
    connect (createDocument, SIGNAL (clicked()), this, SIGNAL (createDocument()));
    layout->addWidget (createDocument);

    QPushButton *loadDocument = new QPushButton ("load", this);
    connect (loadDocument, SIGNAL (clicked()), this, SIGNAL (loadDocument()));
    layout->addWidget (loadDocument);

    setLayout (layout);
}