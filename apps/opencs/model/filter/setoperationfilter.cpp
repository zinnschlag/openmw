#include "setoperationfilter.hpp"

SetOperationFilter::SetOperationFilter(OperationType type, Filter *parent)
    : FilterList(parent)
    , mType(type)
{
}

SetOperationFilter::~SetOperationFilter()
{
}

bool SetOperationFilter::accept(QList<QString> headers, QList<QVariant> row)
{
    switch(mType) {
    case Union:
    {
        if (!enabled())
            return false;

        foreach (Filter* filter, mChildItems)
            if (filter->accept(headers, row))
                return true;

        return false;
    }
    case Intersection:
    {
        if (!enabled())
            return false;

        bool allTrue = true;
        foreach (Filter* filter, mChildItems)
            if (filter->enabled() && !filter->accept(headers, row))
                allTrue = false;

        return allTrue;
    }
    default:
        return false;
    }
}
