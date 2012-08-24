#ifndef FILTER_HPP
#define FILTER_HPP

#include <QObject>
#include <QVariant>

class Filter : public QObject
{
    Q_OBJECT

public:
    explicit Filter(Filter *parent = 0);
    ~Filter();

    virtual bool accept(QList<QString> headers, QList<QVariant> row) = 0;

    Filter *parent();

    bool enabled();
    void setEnabled(bool enabled);

    QString name();
    void setName(QString name);

protected:
    Filter *mParentItem;
    bool mEnabled;
    QString mName;
};

class FilterList : public Filter
{
    Q_OBJECT

public:
    explicit FilterList(Filter *parent = 0);
    ~FilterList();

    int childCount() const;
    int rowOfChild(Filter* child);

    Filter *child(int row);

    void appendChild(Filter *child);
    void removeChild(int row);

protected:
    QList<Filter*> mChildItems;
};

#endif
