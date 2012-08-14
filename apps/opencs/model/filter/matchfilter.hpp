#ifndef MATCHFILTER_HPP
#define MATCHFILTER_HPP

#include "filter.hpp"

#include <QRegExp>

class MatchFilter : public Filter
{
    Q_OBJECT

public:
    enum MatchType {
        Exact,
        Wildcard,
        Regex
    };

    explicit MatchFilter(MatchType matchType, QString expectedKey, QString expectedValue, Filter *parent=0);
    ~MatchFilter();

    virtual QString displayString();

    virtual bool accept(QList<QString> headers, QList<QVariant> row);

private:
    MatchType mMatchType;
    QString mExpectedKey;
    QString mExpectedValue;

    QRegExp mMatchRegExp;
};

#endif
