#ifndef ESMDATAITEM_HPP
#define ESMDATAITEM_HPP

#include "dataitem.hpp"

#include <components/esm/esm_reader.hpp>
#include <components/esm/records.hpp>

class ESMDataItem : public DataItem
{
    Q_OBJECT
    Q_PROPERTY(QString mwType READ type)
    Q_PROPERTY(QString mwId READ id WRITE setId)

public:
    ESMDataItem(DataItem *parent = 0) : DataItem(parent) {}
    ~ESMDataItem()
    {
    }

    //TODO Make this nicer
    virtual void load(ESM::ESMReader &esm)
    {
        esm.skipRecord();
        //std::cout << "skipped record";
    }

    QString recordType()
    {
        return mRecordType;
    }

    void setRecordType(QString recordType)
    {
        mRecordType = recordType;
    }

    virtual QString type()
    {
        return mRecordType;
    }

    QString id()
    {
        return mId;
    }

    void setId(QString id)
    {
        mId = id;
    }

protected:
    QString mRecordType;
    QString mId;

private:
};




#endif // ESMDATAITEM_HPP
