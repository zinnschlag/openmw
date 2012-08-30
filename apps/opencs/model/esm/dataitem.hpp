#ifndef DATAITEM_HPP
#define DATAITEM_HPP

#include <QObject>
#include <QList>

class DataItem : public QObject
{
    Q_OBJECT

public:
    DataItem(DataItem *parent = 0);
    ~DataItem();

    DataItem *parent();
    int row() const;

    int childCount() const;
    DataItem *child(int row);

    void appendChild(DataItem *child);

private:
    DataItem *mParentItem;
    QList<DataItem*> mChildItems;
};

#endif
