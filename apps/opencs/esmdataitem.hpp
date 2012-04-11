#ifndef ESMDATAITEM_HPP
#define ESMDATAITEM_HPP

#include <QList>
#include <QVariant>

class ESMDataItem
{
public:
    ESMDataItem(const QList<QVariant> &data, ESMDataItem *parent = 0);
    ~ESMDataItem();

    void appendChild(ESMDataItem *child);

    ESMDataItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    ESMDataItem *parent();

private:
    QList<ESMDataItem*> mChildItems;
    QList<QVariant> mItemData;
    ESMDataItem *mParentItem;
};

#endif // ESMDATAITEM_HPP
