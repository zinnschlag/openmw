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
//    QList<QVariant> rootData;
//    rootData << "Title" << "Summary";
//    rootItem = new TreeItem(rootData);
//    setupModelData(data.split(QString("\n")), rootItem);

    // Create root items for every record type
    QList<QVariant> headerText;

    headerText << "Name" << "Mesh" << "Script";
    mActivator = new ESMDataItem(headerText);
    headerText.clear();

    headerText << "Name" << "Model" << "Icon" << "Script"
               << "Effects" << "Weight" << "Value" << "AutoCalc";
    mPotion = new ESMDataItem(headerText);
    headerText.clear();


    headerText << "Name" << "Model" << "Icon" << "Script"
               << "Quality" << "Type" << "Weight" << "Value";
    mApparatus = new ESMDataItem(headerText);
    headerText.clear();

    headerText << "Name" << "Model" << "Icon" << "Script"
               << "Enchantment" << "Type" << "Weight" << "Value" << "Health" << "Armor Rating";
    mArmor = new ESMDataItem(headerText);
    headerText.clear();

    headerText << "Name" << "Model" << "Part" << "Type" << "Flags" << "Vampire";
    mBodyPart = new ESMDataItem(headerText);
    headerText.clear();

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

    setupModelData(esm);
}

ESMDataModel::~ESMDataModel()
{
//    delete rootItem;
}

int ESMDataModel::columnCount(const QModelIndex &parent) const
{
    /*if (parent.isValid())
        return static_cast<ESMDataItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();*/
    return 0;
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

QVariant ESMDataModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
//    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
//        return rootItem->data(section);

//    return QVariant();
    return QVariant();
}

QModelIndex ESMDataModel::index(int row, int column, const QModelIndex &parent)
            const
{
    /*if (!hasIndex(row, column, parent))
        return QModelIndex();

    ESMDataItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<ESMDataItem*>(parent.internalPointer());

    ESMDataItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();*/
    return QModelIndex();
}

QModelIndex ESMDataModel::parent(const QModelIndex &index) const
{
    /*if (!index.isValid())
        return QModelIndex();

    ESMDataItem *childItem = static_cast<ESMDataItem*>(index.internalPointer());
    ESMDataItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);*/
    return index;
}

int ESMDataModel::rowCount(const QModelIndex &parent) const
{
    /*ESMDataItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();*/
    return 0;
}

void ESMDataModel::setupModelData(ESM::ESMReader &esm)
{
    // Loop through all records
    while(esm.hasMoreRecs()) {
        ESM::NAME n = esm.getRecName();
        esm.getRecHeader();
        std::string id = esm.getHNOString("NAME");

        //std::cout << "\nRecord: " << n.toString()
        //       << " '" << id << std::endl;

        switch(n.val) {

        case ESM::REC_ACTI:
        {
            ESM::Activator ac;
            ac.load(esm);
            /*std::cout << "  Name: " << ac.name << std::endl;
            std::cout << "  Mesh: " << ac.model << std::endl;
            std::cout << "  Script: " << ac.script << std::endl;*/

            QList<QVariant> columnData;

            columnData << QString::fromStdString(ac.name) << QString::fromStdString(ac.model)
                       << QString::fromStdString(ac.script);
            qDebug() << columnData;

               // columnData << columnStrings[column];
        }

        default:
            esm.skipRecord();
            //std::cout << "  Skipping\n";
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




    /* QList<TreeItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].mid(position, 1) != " ")
                break;
            position++;
        }

        QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
            QList<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            parents.last()->appendChild(new TreeItem(columnData, parents.last()));
        }

        number++;
    } */
}
