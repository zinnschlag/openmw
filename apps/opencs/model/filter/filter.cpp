#include "filter.hpp"

Filter::Filter(Filter *parent)
    : QObject(parent)
    , mParentItem(parent)
    , mEnabled(true)
{}

Filter::~Filter()
{}

Filter *Filter::parent()
{
    return mParentItem;
}

bool Filter::enabled()
{
    return mEnabled;
}

void Filter::setEnabled(bool enabled)
{
    mEnabled = enabled;
}

QString Filter::name()
{
    return mName;
}

void Filter::setName(QString name)
{
    mName = name;
}



FilterList::FilterList(Filter *parent)
    : Filter(parent)
{}

FilterList::~FilterList()
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

