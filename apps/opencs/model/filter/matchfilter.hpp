#ifndef MATCHFILTER_HPP
#define MATCHFILTER_HPP

#include "filter.hpp"

class MatchFilter : public Filter
{
    Q_OBJECT

public:
    explicit MatchFilter(QString expectedKey,QString expectedValue, Filter *parent=0)
        : Filter(parent)
    {
        mExpectedKey = expectedKey;
        mExpectedValue = expectedValue;
    }
    ~MatchFilter() {}

    virtual QString displayString() {return "Match: " + mExpectedKey + "=" + mExpectedValue;}

    virtual bool accept(QList<QString> headers, QList<QVariant> row) {
        return enabled() && headers.contains(mExpectedKey) && row.at(headers.indexOf(mExpectedKey)) == mExpectedValue;
    }

private:
    QString mExpectedKey;
    QString mExpectedValue;
};

#endif
