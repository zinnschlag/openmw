#include "filter.hpp"

Filter::Filter(Filter *parent)
    : QObject(parent)
    , mParentItem(parent)
    , mEnabled(true)
{
}

int FilterList::childCount() const
{
    return mChildItems.count();
}

int FilterList::rowOfChild(Filter *child)
{
    if (child)
        return mChildItems.indexOf(child);

    return 0;
}


Filter *FilterList::child(int row)
{
    return mChildItems.at(row);
}


void FilterList::appendChild(Filter *child)
{
    mChildItems.append(child);
}

void FilterList::removeChild(int row)
{
    mChildItems.removeAt(row);
}





