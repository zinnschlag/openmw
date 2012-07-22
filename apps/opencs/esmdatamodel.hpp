#ifndef ESMDATAMODEL_HPP
#define ESMDATAMODEL_HPP

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <QFile>

class DataItem;

class ESMDataModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ESMDataModel(QObject *parent);
    ~ESMDataModel();


    void loadEsmFile(QString file);


    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    void updateHeaders(DataItem *parent);

    DataItem *mRootItem;

    QList<QVariant> m_ColumnNames;
};


#endif // ESMDATAMODEL_HPP
