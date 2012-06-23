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

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
    void setupModelData(ESM::ESMReader &esm);

    QMap<unsigned char, QString> mArmorTypeNames;
    QMap<unsigned char, QString> mArmorBodyPartNames;

    QMap<unsigned char, QString> mBodyPartNames;

    QMap<int32_t, ESMDataItem*> mSectionDataItems;

    ESMDataItem *mRootItem;
};


#endif // ESMDATAMODEL_HPP
