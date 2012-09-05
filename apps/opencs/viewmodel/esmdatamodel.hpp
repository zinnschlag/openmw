#ifndef ESMDATAMODEL_HPP
#define ESMDATAMODEL_HPP

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

#include <QFile>

#include <QMetaProperty>
#include <QStringList>

#include "../model/modelitem.hpp"

class DataItem;

class ESMDataModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum
    {
        PossibleValuesRole = Qt::UserRole
    };

    ESMDataModel(QObject *parent);
    ~ESMDataModel();

    void loadEsmFile(QString file);

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

private:

    QVariant valueAtColumn(const ModelItem *rowItem, int column) const;

    ModelItem *mRootItem;
    ModelItem *mMerged;

    int mRowCount;

    QStringList mColumnIds;

    QMultiMap<QString, QHash<const QMetaObject*, int>*> mNamedProperties;
};


#endif // ESMDATAMODEL_HPP
