#ifndef UNIONFITLER_HPP
#define UNIONFITLER_HPP

#include "filter.hpp"

class UnionFilter : public Filter
{
    Q_OBJECT

public:
    explicit UnionFilter(QString name, Filter *parent=0);
    ~UnionFilter();

    virtual QString displayString() {return "Union :" + mDisplayName;}
    virtual bool accept(QList<QString> headers, QList<QVariant> row);

    int childCount() const { return mChildItems.count();}
    Filter *child(int row) {return mChildItems.at(row);}

    int rowOfChild(Filter* child);

    void appendChild(Filter *child) { mChildItems.append(child);}

private:
    QString mDisplayName;

    QList<Filter*> mChildItems;
};

#endif
