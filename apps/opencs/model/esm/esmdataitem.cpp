#include <QStringList>

#include "esmdataitem.hpp"

#include <components/esm/esm_reader.hpp>
#include <components/esm/records.hpp>

ESMDataItem::ESMDataItem(ModelItem *parent)
 : ModelItem(parent)
{
}

ESMDataItem::~ESMDataItem()
{
}

void ESMDataItem::load(ESM::ESMReader &esm)
{
    esm.skipRecord();
    //std::cout << "skipped record";
}

QString ESMDataItem::recordType()
{
    return mRecordType;
}

void ESMDataItem::setRecordType(QString recordType)
{
    mRecordType = recordType;
}

QString ESMDataItem::type()
{
    return mRecordType;
}

QString ESMDataItem::id()
{
    return mId;
}

void ESMDataItem::setId(QString id)
{
    mId = id;
}




/*
//Section Item

SectionDataItem::SectionDataItem(int32_t esmName, ESMDataItem *parent)
    :mEsmName(esmName)
    ,ESMDataItem(parent)
{
    QHash<int32_t, QString> sectionNames;

    //Ordered after http://www.uesp.net/morrow/tech/mw_esm.txt
    sectionNames[ESM::REC_GMST] = "Game Setting Records";
    sectionNames[ESM::REC_GLOB] = "Global Variables";
    sectionNames[ESM::REC_CLAS] = "Class Definition";
    sectionNames[ESM::REC_FACT] = "Faction Definition";
    sectionNames[ESM::REC_RACE] = "Race Definition";
    sectionNames[ESM::REC_SOUN] = "Sound";
    sectionNames[ESM::REC_SKIL] = "Skill";
    sectionNames[ESM::REC_MGEF] = "Magic Effect";
    sectionNames[ESM::REC_SCPT] = "Script";
    sectionNames[ESM::REC_REGN] = "Region";
    sectionNames[ESM::REC_BSGN] = "Birth Sign";

    sectionNames[ESM::REC_ACTI] = "Activator";
    sectionNames[ESM::REC_ALCH] = "Potion";

    ESM::NAME name;
    name.val = esmName;
    QString sectionName(name.name);

    if(sectionNames.contains(esmName)) {
        mDisplayName = sectionNames[esmName] + " (" + sectionName + ")";
    } else {
        mDisplayName = sectionName;
    }
}
*/



