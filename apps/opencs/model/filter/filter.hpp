#ifndef FILTER_HPP
#define FILTER_HPP

#include <QObject>
#include <QVariant>

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

#endif
