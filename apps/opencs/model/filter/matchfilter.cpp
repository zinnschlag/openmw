#include "matchfilter.hpp"



MatchFilter::MatchFilter(MatchType matchType, QString expectedKey, QString expectedValue, Filter *parent)
    : Filter(parent)
    , mMatchType(matchType)
    , mExpectedKey(expectedKey)
    , mExpectedValue(expectedValue)
{
    updateRegex();
}

MatchFilter::~MatchFilter()
{
}

QString MatchFilter::displayString()
{
    return mExpectedKey + " : " + mExpectedValue;
}

bool MatchFilter::accept(QList<QString> headers, QList<QVariant> row)
{
    if(!enabled() || !headers.contains(mExpectedKey))
        return false;

    QVariant value = row.at(headers.indexOf(mExpectedKey));

    if(mMatchType == Exact) {
        return value == mExpectedValue;
    } else {
        return mMatchRegExp.exactMatch(value.toString());
    }
}

void MatchFilter::updateRegex()
{
    if(mMatchType == Wildcard) {
        mMatchRegExp = QRegExp(mExpectedValue, Qt::CaseSensitive, QRegExp::WildcardUnix);
    } else if(mMatchType == Regex) {
        mMatchRegExp = QRegExp(mExpectedValue, Qt::CaseSensitive, QRegExp::RegExp2);
    }
}
