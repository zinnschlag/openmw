#include "intersectionfilter.hpp"

bool IntersectionFilter::accept(QList<QString> headers, QList<QVariant> row)
{
    if (!enabled())
        return false;

    bool allTrue = true;
    foreach (Filter* filter, mChildItems)
    if (filter->enabled() && !filter->accept(headers, row))
        allTrue = false;

    return allTrue;
}
