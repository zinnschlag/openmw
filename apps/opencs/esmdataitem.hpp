#ifndef ESMDATAITEM_HPP
#define ESMDATAITEM_HPP

#include <QList>
#include <QVariant>

#include <components/esm/esm_reader.hpp>
#include <components/esm/records.hpp>

class ESMDataItem
{
public:
    ESMDataItem(ESMDataItem *parent = 0);
    ~ESMDataItem();

    void appendChild(ESMDataItem *child);

    ESMDataItem *child(int row);
    int childCount() const;
    int row() const;
    ESMDataItem *parent();

    virtual int columnCount() const;
    virtual QVariant data(int column) const;

private:
    QList<ESMDataItem*> mChildItems;
    QList<QVariant> mItemData;
    ESMDataItem *mParentItem;
};


class SectionDataItem : public ESMDataItem
{
public:
    SectionDataItem(int32_t esmName, ESMDataItem *parent);

    virtual int columnCount() const;
    virtual QVariant data(int column) const;
private:
    int32_t mEsmName;
    QString mDisplayName;
};

class ActivatorDataItem : public ESMDataItem
{
public:
    ActivatorDataItem(const ESM::Activator activator, ESMDataItem *parent);

    virtual int columnCount() const;
    virtual QVariant data(int column) const;
private:
    ESM::Activator mActivator;
};

class PotionDataItem : public ESMDataItem
{
public:
    PotionDataItem(const ESM::Potion potion, PotionDataItem::ESMDataItem *parent);

    virtual int columnCount() const;
    virtual QVariant data(int column) const;
private:
    ESM::Potion mPotion;
};

#endif // ESMDATAITEM_HPP
