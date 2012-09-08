#ifndef ESMDATAITEM_HPP
#define ESMDATAITEM_HPP

#include "../modelitem.hpp"

#include <components/esm/esm_reader.hpp>
#include <components/esm/records.hpp>

class ESMDataItem : public ModelItem
{
    Q_OBJECT
    Q_PROPERTY(QString mwType READ type)
    Q_PROPERTY(QString mwId READ id WRITE setId)

public:
    ESMDataItem(ModelItem *parent = 0);
    ~ESMDataItem();

    //TODO Make this nicer
    virtual void load(ESM::ESMReader &esm);

    virtual QString type();

    QString recordType();
    void setRecordType(QString recordType);

    QString id();
    void setId(QString id);

protected:
    QString mRecordType;
    QString mId;

private:
};




#endif // ESMDATAITEM_HPP
