#include "unionfilter.hpp"

UnionFilter::UnionFilter(Filter *parent)
    : FilterList(parent)
{
}

UnionFilter::~UnionFilter()
{
}

bool UnionFilter::accept(QList<QString> headers, QList<QVariant> row)
{
    if (!enabled())
        return false;

    foreach (Filter* filter, mChildItems)
        if (filter->accept(headers, row))
            return true;

    return false;
}
