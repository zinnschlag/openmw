#include "filter.hpp"

Filter::Filter(Filter *parent)
    : ModelItem(parent)
    , mParentItem(parent)
    , mEnabled(true)
{}

Filter::~Filter()
{}

Filter *Filter::parentFilter()
{
    return mParentItem;
}

Filter *Filter::childFilter(int row)
{
    return static_cast<Filter*>(child(row));
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
