#include <QtGui>

#include <string>
#include <iostream>

#include <components/esm/esm_reader.hpp>
#include <components/esm/records.hpp>

#include "esmdataitem.hpp"
#include "esmdatamodel.hpp"

ESMDataModel::ESMDataModel(ESM::ESMReader &esm, QObject *parent)
    : QAbstractItemModel(parent)
{
    mArmorTypeNames.insert(ESM::Armor::Helmet,    "Helmet");
    mArmorTypeNames.insert(ESM::Armor::Cuirass,   "Cuirass");
    mArmorTypeNames.insert(ESM::Armor::LPauldron, "Left Pauldron");
    mArmorTypeNames.insert(ESM::Armor::RPauldron, "Right Pauldron");
    mArmorTypeNames.insert(ESM::Armor::Greaves,   "Greaves");
    mArmorTypeNames.insert(ESM::Armor::Boots,     "Boots");
    mArmorTypeNames.insert(ESM::Armor::LGauntlet, "Left Gauntlet");
    mArmorTypeNames.insert(ESM::Armor::RGauntlet, "Right Gauntlet");
    mArmorTypeNames.insert(ESM::Armor::Shield,    "Shield");
    mArmorTypeNames.insert(ESM::Armor::LBracer,   "Left Bracer");
    mArmorTypeNames.insert(ESM::Armor::RBracer,   "Right Bracer");

    mArmorBodyPartNames.insert(ESM::PRT_Head, "Head");
    mArmorBodyPartNames.insert(ESM::PRT_Hair, "Hair");
    mArmorBodyPartNames.insert(ESM::PRT_Neck, "Neck");
    mArmorBodyPartNames.insert(ESM::PRT_Cuirass, "Cuirass");
    mArmorBodyPartNames.insert(ESM::PRT_Groin, "Groin");
    mArmorBodyPartNames.insert(ESM::PRT_Skirt, "Skirt");
    mArmorBodyPartNames.insert(ESM::PRT_RHand, "Right Hand");
    mArmorBodyPartNames.insert(ESM::PRT_LHand, "Left Hand");
    mArmorBodyPartNames.insert(ESM::PRT_RWrist, "Right Wrist");
    mArmorBodyPartNames.insert(ESM::PRT_LWrist, "Left Wrist");
    mArmorBodyPartNames.insert(ESM::PRT_Shield, "Shield");
    mArmorBodyPartNames.insert(ESM::PRT_RForearm, "Right Forearm");
    mArmorBodyPartNames.insert(ESM::PRT_LForearm, "Left Forearm");
    mArmorBodyPartNames.insert(ESM::PRT_RUpperarm, "Right Upper Arm");
    mArmorBodyPartNames.insert(ESM::PRT_LUpperarm, "Left Upper Arm");
    mArmorBodyPartNames.insert(ESM::PRT_RFoot, "Right Foot");
    mArmorBodyPartNames.insert(ESM::PRT_LFoot, "Left Foot");
    mArmorBodyPartNames.insert(ESM::PRT_RAnkle, "Right Ankle");
    mArmorBodyPartNames.insert(ESM::PRT_LAnkle, "Left Ankle");
    mArmorBodyPartNames.insert(ESM::PRT_RKnee, "Right Knee");
    mArmorBodyPartNames.insert(ESM::PRT_LKnee, "Left Knee");
    mArmorBodyPartNames.insert(ESM::PRT_RLeg, "Right Upper Leg");
    mArmorBodyPartNames.insert(ESM::PRT_LLeg, "Left Upper Leg");
    mArmorBodyPartNames.insert(ESM::PRT_RPauldron, "Right Pauldron");
    mArmorBodyPartNames.insert(ESM::PRT_LPauldron, "Left Pauldron");
    mArmorBodyPartNames.insert(ESM::PRT_Weapon, "Weapon");
    mArmorBodyPartNames.insert(ESM::PRT_Tail, "Tail");

    mBodyPartNames.insert(ESM::BodyPart::MP_Head, "Head");
    mBodyPartNames.insert(ESM::BodyPart::MP_Hair, "Hair");
    mBodyPartNames.insert(ESM::BodyPart::MP_Neck, "Neck");
    mBodyPartNames.insert(ESM::BodyPart::MP_Chest, "Chest");
    mBodyPartNames.insert(ESM::BodyPart::MP_Groin, "Groin");
    mBodyPartNames.insert(ESM::BodyPart::MP_Hand, "Hand");
    mBodyPartNames.insert(ESM::BodyPart::MP_Wrist, "Wrist");
    mBodyPartNames.insert(ESM::BodyPart::MP_Forearm, "Forearm");
    mBodyPartNames.insert(ESM::BodyPart::MP_Upperarm, "Upperarm");
    mBodyPartNames.insert(ESM::BodyPart::MP_Foot, "Foot");
    mBodyPartNames.insert(ESM::BodyPart::MP_Ankle, "Ankle");
    mBodyPartNames.insert(ESM::BodyPart::MP_Knee, "Knee");
    mBodyPartNames.insert(ESM::BodyPart::MP_Upperleg, "Upperleg");
    mBodyPartNames.insert(ESM::BodyPart::MP_Clavicle, "Clavicle");
    mBodyPartNames.insert(ESM::BodyPart::MP_Tail, "Tail");

    mRootItem = new ESMDataItem();

    setupModelData(esm);
}

ESMDataModel::~ESMDataModel()
{
    delete mRootItem;
}

int ESMDataModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<ESMDataItem*>(parent.internalPointer())->columnCount();
    else
        return 10;
        //return mRootItem->columnCount();
}

QVariant ESMDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    ESMDataItem *item = static_cast<ESMDataItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags ESMDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ESMDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        return QVariant(QString("title ") + QString::number(section));
     //   return mRootItem->data(section);
    }

    return QVariant();
}

QModelIndex ESMDataModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    ESMDataItem *parentItem;

    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<ESMDataItem*>(parent.internalPointer());

    ESMDataItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex ESMDataModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    ESMDataItem *childItem = static_cast<ESMDataItem*>(index.internalPointer());
    ESMDataItem *parentItem = childItem->parent();

    if (parentItem == mRootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
    return index;
}

int ESMDataModel::rowCount(const QModelIndex &parent) const
{
    ESMDataItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<ESMDataItem*>(parent.internalPointer());

    return parentItem->childCount();
    return 0;
}

void ESMDataModel::setupModelData(ESM::ESMReader &esm)
{

    while(esm.hasMoreRecs()) {
        ESM::NAME n = esm.getRecName();
        esm.getRecHeader();

        std::string id = esm.getHNOString("NAME");
        QString recordId = QString::fromStdString(id);

        ESMDataItem *sectionItem;

        if(!mSectionDataItems.contains(n.val)) {
            sectionItem = new SectionDataItem(n.val, mRootItem);
            mSectionDataItems[n.val] = sectionItem;
            mRootItem->appendChild(sectionItem);
        } else {
            sectionItem = mSectionDataItems[n.val];
        }

        switch(n.val) {
        case ESM::REC_ACTI:
        {
            ESM::Activator ac;
            ac.load(esm);

            ActivatorDataItem *activatorItem = new ActivatorDataItem(ac, sectionItem);
            activatorItem->setId(recordId);
            sectionItem->appendChild(activatorItem);
        }
        break;
        case ESM::REC_ALCH:
        {
            ESM::Potion p;
            p.load(esm);

            PotionDataItem *potionItem = new PotionDataItem(p, sectionItem);
            potionItem->setId(recordId);
            sectionItem->appendChild(potionItem);
        }
            break;
            /*
        case ESM::REC_APPA:
        {
            ESM::Apparatus p;
            p.load(esm);

            columnData << QString::fromStdString(p.name) << QString::fromStdString(p.model);
            switch(p.data.type) {
            case ESM::Apparatus::MortarPestle:
                columnData << "Mortar and Pestle";
                break;
            case ESM::Apparatus::Albemic:
                columnData << "Albemic";
                break;
            case ESM::Apparatus::Calcinator:
                columnData << "Calcinator";
                break;
            case ESM::Apparatus::Retort:
                columnData << "Retort";
                break;
            }
            columnData << p.data.quality << p.data.weight << p.data.value;

            mApparatus->appendChild(new ESMDataItem(columnData, mApparatus));
        }
            break;
        case ESM::REC_ARMO:
        {
            ESM::Armor am;
            am.load(esm);

            columnData  << QString::fromStdString(am.name) << QString::fromStdString(am.model);

            columnData  << mArmorTypeNames.value(am.data.type, "Unknown");

            columnData << am.data.weight << am.data.value << am.data.health << am.data.enchant << am.data.armor;
            columnData << QString::fromStdString(am.script) << QString::fromStdString(am.enchant);

            ESMDataItem *armor = new ESMDataItem(columnData, mArmor);
            mArmor->appendChild(armor);
            columnData.clear();

            for(std::vector<ESM::PartReference>::const_iterator iter(am.parts.parts.begin()); iter!=am.parts.parts.end(); ++iter)
            {
                columnData << mArmorBodyPartNames.value(iter->part, "");
                columnData << QString::fromStdString(iter->male) << QString::fromStdString(iter->female);

                ESMDataItem *armorPart = new ESMDataItem(columnData, armor);
                armor->appendChild(armorPart);
                columnData.clear();
            }
        }
            break;
        case ESM::REC_BODY:
        {
            ESM::BodyPart bp;
            bp.load(esm);

            columnData << QString::fromStdString(bp.name) << QString::fromStdString(bp.model);
            columnData << mBodyPartNames.value(bp.data.part, "Unknown");

            ESMDataItem *bodyPart = new ESMDataItem(columnData, mBodyPart);
            mBodyPart->appendChild(bodyPart);
            columnData.clear();

            break;
        }
        */
        default:
            esm.skipRecord();
            break;
        }
    }
}
