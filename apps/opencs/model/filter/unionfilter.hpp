#ifndef UNIONFITLER_HPP
#define UNIONFITLER_HPP

#include "filter.hpp"

class UnionFilter : public FilterList
{
    Q_OBJECT

public:
    explicit UnionFilter(Filter *parent=0);
    ~UnionFilter();

    virtual bool accept(QList<QString> headers, QList<QVariant> row);
};

#endif
