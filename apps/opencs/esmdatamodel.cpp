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

    QList<QVariant> rootData;
    rootData << "Name";
    mRootItem = new ESMDataItem(rootData);

    // Create root items for every record type
    QList<QVariant> headerText;

    headerText << "Activator" << "Mesh" << "Script";
    mActivator = new ESMDataItem(headerText, mRootItem);
    mRootItem->appendChild(mActivator);
    headerText.clear();

    headerText << "Potion" << "Model" << "Icon" << "Script" << "Effects" << "Weight" << "Value" << "AutoCalc";
    mPotion = new ESMDataItem(headerText, mRootItem);
    mRootItem->appendChild(mPotion);
    headerText.clear();


    headerText << "Apparatus" << "Model" << "Icon" << "Script" << "Quality" << "Type" << "Weight" << "Value";
    mApparatus = new ESMDataItem(headerText, mRootItem);
    mRootItem->appendChild(mApparatus);
    headerText.clear();

    headerText << "Armor" << "Model" << "Icon" << "Script" << "Enchantment" << "Type" << "Weight" << "Value" << "Health" << "Armor Rating";
    mArmor = new ESMDataItem(headerText, mRootItem);
    mRootItem->appendChild(mArmor);
    headerText.clear();

    headerText << "BodyPart" << "Model" << "Part" << "Type" << "Flags" << "Vampire";
    mBodyPart = new ESMDataItem(headerText, mRootItem);
    mRootItem->appendChild(mBodyPart);
    headerText.clear();
/*
    ESMDataItem *mBirthSign = new ESMDataItem(headerText);
    ESMDataItem *mCell = new ESMDataItem(headerText);
    ESMDataItem *mClass = new ESMDataItem(headerText);
    ESMDataItem *mClothing = new ESMDataItem(headerText);
    ESMDataItem *mContainer = new ESMDataItem(headerText);
    ESMDataItem *mCreature = new ESMDataItem(headerText);
    ESMDataItem *mDialogue = new ESMDataItem(headerText);
    ESMDataItem *mDoor = new ESMDataItem(headerText);
    ESMDataItem *mEnchantment = new ESMDataItem(headerText);
    ESMDataItem *mGameSetting = new ESMDataItem(headerText);
    ESMDataItem *mDialInfo = new ESMDataItem(headerText);
    ESMDataItem *mSound = new ESMDataItem(headerText);
    ESMDataItem *mSpell = new ESMDataItem(headerText);
*/

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
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return mRootItem->data(section);

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
    bool skipped = false;
    QList<QVariant> columnData;

    while(esm.hasMoreRecs()) {
        ESM::NAME n = esm.getRecName();
        esm.getRecHeader();
        std::string id = esm.getHNOString("NAME");

        columnData.clear();
        columnData << QString::fromStdString(id);

        switch(n.val) {
        case ESM::REC_ACTI:
        {
            ESM::Activator ac;
            ac.load(esm);
            columnData << QString::fromStdString(ac.name) << QString::fromStdString(ac.model);
            columnData << QString::fromStdString(ac.script);

            mActivator->appendChild(new ESMDataItem(columnData, mActivator));
        }
            break;
        case ESM::REC_ALCH:
        {
            ESM::Potion p;
            p.load(esm);

            columnData << QString::fromStdString(p.name) << QString::fromStdString(p.model);
            columnData << p.data.weight << p.data.value << p.data.weight;

            ESMDataItem *potion = new ESMDataItem(columnData, mPotion);
            mPotion->appendChild(potion);
            columnData.clear();

            for(std::vector<ESM::ENAMstruct>::const_iterator iter(p.effects.list.begin()); iter!=p.effects.list.end(); ++iter)
            {
                columnData << iter->effectID << iter->skill << iter->attribute << iter->range << iter->area << iter->duration << iter->magnMin << iter->magnMax;

                ESMDataItem *effect = new ESMDataItem(columnData, potion);
                potion->appendChild(effect);
                columnData.clear();
            }
        }
            break;
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
        default:
            esm.skipRecord();
            break;
        }
    }
}
        /*case REC_ALCH:
        {
            Potion p;
            p.load(esm);
            if(quiet) break;
            cout << "  Name: " << p.name << endl;
            break;
        }

        case REC_APPA:
        {
            Apparatus p;
            p.load(esm);
            if(quiet) break;
            cout << "  Name: " << p.name << endl;
            break;
        }
        case REC_ARMO:
        {
            Armor am;
            am.load(esm);
            if(quiet) break;
            cout << "  Name: " << am.name << endl;
            cout << "  Mesh: " << am.model << endl;
            cout << "  Icon: " << am.icon << endl;
            cout << "  Script: " << am.script << endl;
            cout << "  Enchantment: " << am.enchant << endl;
            cout << "  Type: " << am.data.type << endl;
            cout << "  Weight: " << am.data.weight << endl;
            break;
        }
        case REC_BODY:
        {
            BodyPart bp;
            bp.load(esm);
            if(quiet) break;
            cout << "  Name: " << bp.name << endl;
            cout << "  Mesh: " << bp.model << endl;
            break;
        }
        case REC_BOOK:
        {
            Book b;
            b.load(esm);
            if(quiet) break;
            cout << "  Name: " << b.name << endl;
            cout << "  Mesh: " << b.model << endl;
            break;
        }
        case REC_BSGN:
        {
            BirthSign bs;
            bs.load(esm);
            if(quiet) break;
            cout << "  Name: " << bs.name << endl;
            cout << "  Texture: " << bs.texture << endl;
            cout << "  Description: " << bs.description << endl;
            break;
        }
        case REC_CELL:
        {
            Cell b;
            b.load(esm);
            if(!quiet)
            {
                cout << "  Name: " << b.name << endl;
                cout << "  Region: " << b.region << endl;
            }
            if(loadCells)
                loadCell(b, esm, quiet);
            break;
        }
        case REC_CLAS:
        {
            Class b;
            b.load(esm);
            if(quiet) break;
            cout << "  Name: " << b.name << endl;
            cout << "  Description: " << b.description << endl;
            break;
        }
        case REC_CLOT:
        {
            Clothing b;
            b.load(esm);
            if(quiet) break;
            cout << "  Name: " << b.name << endl;
            break;
        }
        case REC_CONT:
        {
            Container b;
            b.load(esm);
            if(quiet) break;
            cout << "  Name: " << b.name << endl;
            break;
        }
        case REC_CREA:
        {
            Creature b;
            b.load(esm, id);
            if(quiet) break;
            cout << "  Name: " << b.name << endl;
            break;
        }
        case REC_DIAL:
        {
            Dialogue b;
            b.load(esm);
            break;
        }
        case REC_DOOR:
        {
            Door d;
            d.load(esm);
            if(quiet) break;
            cout << "  Name: " << d.name << endl;
            cout << "  Mesh: " << d.model << endl;
            cout << "  Script: " << d.script << endl;
            cout << "  OpenSound: " << d.openSound << endl;
            cout << "  CloseSound: " << d.closeSound << endl;
            break;
        }
        case REC_ENCH:
        {
            Enchantment b;
            b.load(esm);
            break;
        }
        case REC_GMST:
        {
            GameSetting b;
            b.id = id;
            b.load(esm);
            if(quiet) break;
            cout << "  Value: ";
            if(b.type == VT_String)
                cout << "'" << b.str << "' (string)";
            else if(b.type == VT_Float)
                cout << b.f << " (float)";
            else if(b.type == VT_Int)
                cout << b.i << " (int)";
            cout << "\n  Dirty: " << b.dirty << endl;
            break;
        }
        case REC_INFO:
        {
            DialInfo p;
            p.load(esm);
            if(quiet) break;
            cout << "  Id: " << p.id << endl;
            cout << "  Text: " << p.response << endl;
            break;
        }
        case REC_SOUN:
        {
            Sound d;
            d.load(esm);
            if(quiet) break;
            cout << "  Sound: " << d.sound << endl;
            cout << "  Volume: " << (int)d.data.volume << endl;
            break;
        }
        case REC_SPEL:
        {
            Spell s;
            s.load(esm);
            if(quiet) break;
            cout << "  Name: " << s.name << endl;
            break;
        }
        default:
            esm.skipRecord();
            if(quiet) break;
            cout << "  Skipping\n";
        }
    }*/
