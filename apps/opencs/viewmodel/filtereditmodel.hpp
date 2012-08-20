#ifndef FILTEREDITMODEL_HPP
#define FILTEREDITMODEL_HPP

#include <QAbstractItemModel>

#include <QtXml/QDomElement>

#include "../model/filter/filter.hpp"
#include "../model/filter/unionfilter.hpp"

class FilterEditModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    FilterEditModel(QObject *parent);
    ~FilterEditModel();

    void load();
    void readFilter(const QDomElement &element, Filter *parent);


    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool removeRows(int row, int count, const QModelIndex &parent);

    void addUnionFilter(const QModelIndex &parent);
    void addMatchFilter(const QModelIndex &parent);

    bool accept(QList<QString> headers, QList<QVariant> row);

private:
    UnionFilter *mRootItem;
};

#endif
