#include <QStringList>

#include "esmdataitem.hpp"

#include <components/esm/esm_reader.hpp>
#include <components/esm/records.hpp>

ESMDataItem::ESMDataItem(ESMDataItem *parent)
    : mParentItem(parent)
    , QObject(parent)
{
}

ESMDataItem::~ESMDataItem()
{
    qDeleteAll(mChildItems);
}

void ESMDataItem::appendChild(ESMDataItem *item)
{
    mChildItems.append(item);
}

ESMDataItem *ESMDataItem::child(int row)
{
    return mChildItems.value(row);
}

int ESMDataItem::childCount() const
{
    return mChildItems.count();
}

ESMDataItem *ESMDataItem::parent()
{
    return mParentItem;
}

int ESMDataItem::row() const
{
    if (mParentItem)
        return mParentItem->mChildItems.indexOf(const_cast<ESMDataItem*>(this));

    return 0;
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
