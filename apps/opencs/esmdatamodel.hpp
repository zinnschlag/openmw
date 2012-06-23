#ifndef ESMDATAMODEL_HPP
#define ESMDATAMODEL_HPP

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class ESMDataItem;

namespace ESM
{
    class ESMReader;
}

class ESMDataModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ESMDataModel(ESM::ESMReader &esm, QObject *parent = 0);
    ~ESMDataModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

private:
    void setupModelData(ESM::ESMReader &esm);

    QMap<unsigned char, QString> mArmorTypeNames;
    QMap<unsigned char, QString> mArmorBodyPartNames;

    QMap<unsigned char, QString> mBodyPartNames;

    ESMDataItem *mRootItem;

    ESMDataItem *mActivator;
    ESMDataItem *mPotion;
    ESMDataItem *mApparatus;
    ESMDataItem *mArmor;
    ESMDataItem *mBodyPart;
    /*
    ESMDataItem *mBook;
    ESMDataItem *mBirthSign;
    ESMDataItem *mCell;
    ESMDataItem *mClass;
    ESMDataItem *mClothing;
    ESMDataItem *mContainer;
    ESMDataItem *mCreature;
    ESMDataItem *mDialogue;
    ESMDataItem *mDoor;
    ESMDataItem *mEnchantment;
    ESMDataItem *mGameSetting;
    ESMDataItem *mDialInfo;
    ESMDataItem *mSound;
    ESMDataItem *mSpell;
    */

};


#endif // ESMDATAMODEL_HPP
