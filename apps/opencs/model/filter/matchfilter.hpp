#ifndef MATCHFILTER_HPP
#define MATCHFILTER_HPP

#include "filter.hpp"

#include <QRegExp>

class MatchFilter : public Filter
{
    Q_OBJECT
    Q_ENUMS(MatchType)

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

    MatchType type(){return mMatchType;}
    void setType(MatchType type){mMatchType = type; updateRegex();}

    QString key(){return mExpectedKey;}
    void setKey(QString key){ mExpectedKey = key;}

    QString value(){return mExpectedValue;}
    void setValue(QString value){mExpectedValue = value; updateRegex();}

private:
    MatchType mMatchType;
    QString mExpectedKey;
    QString mExpectedValue;

    QRegExp mMatchRegExp;

    void updateRegex();
};

Q_DECLARE_METATYPE(MatchFilter::MatchType)

#endif
