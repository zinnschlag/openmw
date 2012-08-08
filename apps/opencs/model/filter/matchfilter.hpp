#ifndef MATCHFILTER_HPP
#define MATCHFILTER_HPP

#include "filter.hpp"

class MatchFilter : public Filter
{
    Q_OBJECT

public:
    explicit MatchFilter(QString expectedKey, QString expectedValue, Filter *parent=0);
    ~MatchFilter();

    virtual QString displayString();

    virtual bool accept(QList<QString> headers, QList<QVariant> row);

private:
    QString mExpectedKey;
    QString mExpectedValue;
};

#endif
