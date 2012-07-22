#ifndef ESMDATAITEM_HPP
#define ESMDATAITEM_HPP

#include <QList>
#include <QVariant>

#include <components/esm/esm_reader.hpp>
#include <components/esm/records.hpp>

class ESMDataItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mwId READ id WRITE setId)

public:
    ESMDataItem(ESMDataItem *parent = 0);
    ~ESMDataItem();

    void appendChild(ESMDataItem *child);

    ESMDataItem *child(int row);
    int childCount() const;
    int row() const;
    ESMDataItem *parent();

    //TODO Make this nicer
    virtual void load(ESM::ESMReader &esm){
        esm.skipRecord();
        std::cout << "skipped record";
    }

    QString id() { return mId;}
    void setId(QString id) {mId = id;}

protected:
    QString mId;

private:
    ESMDataItem *mParentItem;
    QList<ESMDataItem*> mChildItems;
};

#endif // ESMDATAITEM_HPP
