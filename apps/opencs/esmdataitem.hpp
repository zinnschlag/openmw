#ifndef ESMDATAITEM_HPP
#define ESMDATAITEM_HPP

#include <QList>
#include <QVariant>

#include <components/esm/esm_reader.hpp>
#include <components/esm/records.hpp>


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

class EsmFile : public DataItem
{
    Q_OBJECT
    Q_PROPERTY(QString filename READ filename)

public:
    EsmFile(DataItem *parent = 0) : DataItem(parent) {}
    ~EsmFile() {}

    EsmFile(QString fileName, DataItem *parent);

    QString filename() { return mFileName;}

private:
    QString mFileName;
};

class ESMDataItem : public DataItem
{
    Q_OBJECT
    Q_PROPERTY(QString mwId READ id WRITE setId)

public:
    ESMDataItem(DataItem *parent = 0) : DataItem(parent) {}
    ~ESMDataItem() {}

    //TODO Make this nicer
    virtual void load(ESM::ESMReader &esm){
        esm.skipRecord();
        //std::cout << "skipped record";
    }

    QString id() { return mId;}
    void setId(QString id) {mId = id;}

protected:
    QString mId;

private:
};




#endif // ESMDATAITEM_HPP
