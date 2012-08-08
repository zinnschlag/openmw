#include "unionfilter.hpp"

UnionFilter::UnionFilter(QString name, Filter *parent)
    : Filter(parent)
    , mDisplayName(name)
{}

UnionFilter::~UnionFilter()
{}

bool UnionFilter::accept(QList<QString> headers, QList<QVariant> row) {
    if(!enabled())
        return false;

    foreach(Filter* filter, mChildItems) {
        if(filter->accept(headers, row)) {
            return true;
        }
    }
    return false;
}

int UnionFilter::rowOfChild(Filter *child)
{
    if (child)
        return mChildItems.indexOf(child);

    return 0;
}
