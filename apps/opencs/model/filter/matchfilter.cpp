#include "matchfilter.hpp"

MatchFilter::MatchFilter(QString expectedKey, QString expectedValue, Filter *parent)
    : Filter(parent)
    , mExpectedKey(expectedKey)
    , mExpectedValue(expectedValue)
{
}

MatchFilter::~MatchFilter()
{
}

QString MatchFilter::displayString()
{
    return "Match: " + mExpectedKey + "=" + mExpectedValue;
}

bool MatchFilter::accept(QList<QString> headers, QList<QVariant> row)
{
    return enabled() && headers.contains(mExpectedKey) && row.at(headers.indexOf(mExpectedKey)) == mExpectedValue;
}
