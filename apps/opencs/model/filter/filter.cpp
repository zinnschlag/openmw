#include "filter.hpp"

Filter::Filter(Filter *parent)
    : QObject(parent)
    , mParentItem(parent)
    , mEnabled(true)
{
}

