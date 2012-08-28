#ifndef INTERSECTIONFILTER_HPP
#define INTERSECTIONFILTER_HPP

#include "filter.hpp"

class IntersectionFilter : public FilterList
{
    Q_OBJECT

public:
    explicit IntersectionFilter(Filter *parent=0)
      : FilterList(parent)
    {}

    ~IntersectionFilter(){}

    bool accept(QList<QString> headers, QList<QVariant> row);
};

#endif
