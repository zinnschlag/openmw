#include <QStringList>

#include "esmdataitem.hpp"

ESMDataItem::ESMDataItem(ESMDataItem *parent)
    : mParentItem(parent)
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

int ESMDataItem::columnCount() const
{
    return 10;
}

QVariant ESMDataItem::data(int column) const
{
    return QVariant("BaseClass");
    //return mItemData.value(column);
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

//######################################################

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

    if(sectionNames.contains(esmName)) {
        mDisplayName = sectionNames[esmName];
    } else {
        ESM::NAME name;
        name.val = esmName;
        mDisplayName = name.name;
    }
}

int SectionDataItem::columnCount() const
{
    return 10;
}

QVariant SectionDataItem::data(int column) const
{
    switch(column){
    case 0:
        return QVariant(mDisplayName);
    case 1:
        return QString::number(childCount());
    default:
        return QVariant();
    }
}

//Activator Item

ActivatorDataItem::ActivatorDataItem(const ESM::Activator activator, ESMDataItem *parent)
    : mActivator(activator)
    , ESMDataItem(parent)
{
}

int ActivatorDataItem::columnCount() const
{
    return 4;
}

QVariant ActivatorDataItem::data(int column) const
{    
    QString result;
    switch(column) {
    case 0:
        result = mId;
        break;
    case 1:
        result = QString::fromStdString(mActivator.name);
        break;
    case 2:
        result = QString::fromStdString(mActivator.model);
        break;
    case 3:
        result = QString::fromStdString(mActivator.script);
        break;
    default:
        result = "-";
    }

    return QVariant(result);
}

// Potion Item

PotionDataItem::PotionDataItem(const ESM::Potion potion, PotionDataItem::ESMDataItem *parent)
    : mPotion(potion)
    , ESMDataItem(parent)
{

    for(std::vector<ESM::ENAMstruct>::const_iterator iter(mPotion.effects.list.begin()); iter!=mPotion.effects.list.end(); ++iter)
    {
        MagicEffectDataItem *effect = new MagicEffectDataItem(*iter, this);
        this->appendChild(effect);
    }
}

int PotionDataItem::columnCount() const
{
    return 7;
}

QVariant PotionDataItem::data(int column) const
{
    switch(column) {
    case 0:
        return mId;
    case 1:
        return QVariant(QString::fromStdString(mPotion.name));
    case 2:
        return QVariant(QString::fromStdString(mPotion.model));
    case 3:
        return QVariant(QString::fromStdString(mPotion.script));
    case 4:
        return QVariant(mPotion.data.weight);
    case 5:
        return QVariant(mPotion.data.value);
    case 6:
        return QVariant(mPotion.data.autoCalc);
    default:
        return QVariant("-");
    }
}

//Magic Effect Item

MagicEffectDataItem::MagicEffectDataItem(const ESM::ENAMstruct magicEffect, ESMDataItem *parent)
    :mMagicEffect(magicEffect)
    ,ESMDataItem(parent)
{
}

int MagicEffectDataItem::columnCount() const
{
    return 10;
}

QVariant MagicEffectDataItem::data(int column) const
{
    switch(column){
    case 0:
        return QVariant(mId);
    case 1:
        return QVariant(mMagicEffect.effectID);
    case 2:
        return QVariant(mMagicEffect.skill);
    case 3:
        return QVariant(mMagicEffect.attribute);
    case 4:
        return QVariant(mMagicEffect.range);
    case 5:
        return QVariant(mMagicEffect.area);
    case 6:
        return QVariant(mMagicEffect.duration);
    case 7:
        return QVariant(mMagicEffect.magnMin);
    case 8:
        return QVariant(mMagicEffect.magnMax);
    default:
        return QVariant();
    }
}
