#ifndef MATCHFILTER_HPP
#define MATCHFILTER_HPP

#include "filter.hpp"

#include <QRegExp>

class MatchFilter : public Filter
{
    Q_OBJECT

    Q_CLASSINFO("icon.0", "icon")
    Q_PROPERTY(QString icon READ icon)

    Q_CLASSINFO("view.1", "type")
    Q_CLASSINFO("view.2", "key")
    Q_CLASSINFO("view.3", "value")

    Q_CLASSINFO("edit.1", "type")
    Q_CLASSINFO("edit.2", "key")
    Q_CLASSINFO("edit.3", "value")

    Q_PROPERTY(MatchType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)

    Q_ENUMS(MatchType)

public:
    enum MatchType {
        Exact,
        Wildcard,
        Regex
    };

    explicit MatchFilter(MatchType matchType, QString expectedKey, QString expectedValue, ModelItem *parent=0);
    ~MatchFilter();

    virtual QString displayString();
    virtual bool accept(QList<QString> headers, QList<QVariant> row);

    MatchType type(){return mMatchType;}
    void setType(MatchType type){mMatchType = type; updateRegex();}

    QString key(){return mExpectedKey;}
    void setKey(QString key){ mExpectedKey = key;}

    QString value(){return mExpectedValue;}
    void setValue(QString value){mExpectedValue = value; updateRegex();}

    QString icon() {
        switch(mMatchType) {
        case MatchFilter::Exact:
            return ":/icon/filter/exact.png";
        case MatchFilter::Wildcard:
            return ":/icon/filter/wildcard.png";
        case MatchFilter::Regex:
            return ":/icon/filter/regex.png";
        }
    }

signals:
    void typeChanged();
    void keyChanged();
    void valueChanged();

private:
    MatchType mMatchType;
    QString mExpectedKey;
    QString mExpectedValue;

    QRegExp mMatchRegExp;

    void updateRegex();
};

Q_DECLARE_METATYPE(MatchFilter::MatchType)

#endif
