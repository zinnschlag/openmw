#include "setoperationfilter.hpp"

SetOperationFilter::SetOperationFilter(OperationType type, Filter *parent)
    : Filter(parent)
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

        for(int i=0; i<childCount(); i++)
            if (childFilter(i)->accept(headers, row))
                return true;

        return false;
    }
    case Intersection:
    {
        if (!enabled())
            return false;

        bool allTrue = true;

        for(int i=0; i<childCount(); i++) {
            Filter *child = childFilter(i);
            if (child->enabled() && !child->accept(headers, row))
                allTrue = false;
        }

        return allTrue;
    }
    default:
        return false;
    }
}
