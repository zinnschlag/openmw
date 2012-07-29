#ifndef IDLISTFILTER_HPP
#define IDLISTFILTER_HPP

#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

namespace Ui {
class IdList;
}

class Filter : public QObject
{
    Q_OBJECT
public:
    explicit Filter(Filter *parent = 0) : mParentItem(parent), mEnabled(true), QObject(parent) {}
    ~Filter() {}

    Filter *parent() { return mParentItem;}
    int row() const {
        if (mParentItem)
            return mParentItem->mChildItems.indexOf(const_cast<Filter*>(this));

        return 0;
    }

    int childCount() const { return mChildItems.count();}
    Filter *child(int row) {return mChildItems.at(row);}

    void appendChild(Filter *child) { mChildItems.append(child);}

    QString displayName() {return mDisplayName;}
    virtual QString displayType() {return "Filter";}

    virtual bool accept(QString key, QString value) {
        if(!enabled())
            return false;

        foreach(Filter* filter, mChildItems) {
            if(filter->accept(key, value)) {
                return true;
            }
        }
        return false;
    }

    bool enabled() {return mEnabled;}
    void setEnabled(bool enabled){mEnabled = enabled;}

protected:
    QString mDisplayName;

private:
    Filter *mParentItem;
    QList<Filter*> mChildItems;

    bool mEnabled;
};


class UnionFilter : public Filter
{
    Q_OBJECT

public:
    explicit UnionFilter(QString name, Filter *parent=0) : Filter(parent) {mDisplayName = name;}
    ~UnionFilter() {}

    virtual QString displayType() {return "Union";}
};

class MatchFilter : public Filter
{
    Q_OBJECT

public:
    explicit MatchFilter(QString name,Filter *parent=0) : Filter(parent) {mDisplayName = name;}
    ~MatchFilter() {}

    virtual QString displayType() {return "Match";}

    virtual bool accept(QString key, QString value) {
        if(!enabled())
            return false;

        return key == "mwType" && mDisplayName == value;
    }
};

class FilterEditModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    FilterEditModel(QObject *parent);
    ~FilterEditModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool accept(QString key, QString value);

private:
    Filter *mRootItem;
};

class FilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    FilterProxyModel(QObject *parent = 0);

    FilterEditModel *editModel() { return mEditModel;}

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    FilterEditModel *mEditModel;

};

#endif
