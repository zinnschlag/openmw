#ifndef IDLISTFILTER_HPP
#define IDLISTFILTER_HPP

#include <QMap>

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

    virtual QString displayString() {return "Filter";}

    virtual bool accept(QList<QString> headers, QList<QVariant> row) {
        if(!enabled())
            return false;

        foreach(Filter* filter, mChildItems) {
            if(filter->accept(headers, row)) {
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

    virtual QString displayString() {return "Union :" + mDisplayName;}
};

class NoFilter : public Filter
{
    Q_OBJECT

public:
    explicit NoFilter(QString name, Filter *parent=0) : Filter(parent) {mDisplayName = name;}
    ~NoFilter() {}

    virtual QString displayString() {return "NoFilter";}

    virtual bool accept(QList<QString> headers, QList<QVariant> row) {
        return enabled();
    }
};

class MatchFilter : public Filter
{
    Q_OBJECT

public:
    explicit MatchFilter(QString expectedKey,QString expectedValue, Filter *parent=0)
        : Filter(parent)
    {
        mExpectedKey = expectedKey;
        mExpectedValue = expectedValue;
    }
    ~MatchFilter() {}

    virtual QString displayString() {return "Match: " + mExpectedKey + "=" + mExpectedValue;}

    virtual bool accept(QList<QString> headers, QList<QVariant> row) {
        return enabled() && headers.contains(mExpectedKey) && row.at(headers.indexOf(mExpectedKey)) == mExpectedValue;
    }

private:
    QString mExpectedKey;
    QString mExpectedValue;
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

    bool accept(QList<QString> headers, QList<QVariant> row);

private:
    Filter *mRootItem;
};

class FilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    FilterProxyModel(QObject *parent = 0);

    FilterEditModel *editModel() { return mEditModel;}

    void setSourceModel(QAbstractItemModel *model);

protected:
    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const;
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private slots:
    void headerDataChanged(Qt::Orientation,int,int);

private:
    FilterEditModel *mEditModel;

    QList<QString> mHeaders;
};

#endif
