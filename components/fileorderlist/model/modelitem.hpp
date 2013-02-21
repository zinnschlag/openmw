/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MODELITEM_HPP
#define MODELITEM_HPP

#include <QObject>
#include <QList>

class ModelItem : public QObject
{
    Q_OBJECT

public:
    ModelItem(ModelItem *parent = 0);
    ~ModelItem();

    ModelItem *parent();
    int row() const;

    int childCount() const;
    int childRow(ModelItem *child) const;
    ModelItem *child(int row);

    void appendChild(ModelItem *child);
    void removeChild(int row);

    //virtual bool acceptChild(ModelItem *child);

protected:
    ModelItem *mParentItem;
    QList<ModelItem*> mChildItems;
};

#endif
