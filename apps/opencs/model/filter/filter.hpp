#ifndef FILTER_HPP
#define FILTER_HPP

#include <QObject>
#include <QVariant>

class Filter : public QObject
{
    Q_OBJECT
public:
    explicit Filter(Filter *parent = 0);
    ~Filter()
    {
    }

    virtual bool accept(QList<QString> headers, QList<QVariant> row) = 0;

    Filter *parent()
    {
        return mParentItem;
    }

    bool enabled()
    {
        return mEnabled;
    }

    void setEnabled(bool enabled)
    {
        mEnabled = enabled;
    }

    QString name()
    {
        return mName;
    }

    void setName(QString name)
    {
        mName = name;
    }

protected:
    Filter *mParentItem;
    bool mEnabled;
    QString mName;
};

class FilterList : public Filter
{
    Q_OBJECT

public:
    explicit FilterList(Filter *parent = 0) : Filter(parent) {}
    ~FilterList(){}

    int childCount() const;
    int rowOfChild(Filter* child);

    Filter *child(int row);

    void appendChild(Filter *child);
    void removeChild(int row);

protected:
    QList<Filter*> mChildItems;
};

#endif
