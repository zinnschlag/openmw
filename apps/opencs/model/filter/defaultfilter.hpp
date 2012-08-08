#ifndef DEFAULTFILTER_HPP
#define DEFAULTFILTER_HPP

#include "filter.hpp"

class NoFilter : public Filter
{
    Q_OBJECT

public:
    explicit NoFilter(QString name, Filter *parent=0) : Filter(parent) {mDisplayName = name;}
    ~NoFilter() {}

    virtual QString displayString() {return "NoFilter";}

    virtual bool accept(QList<QString> headers, QList<QVariant> row) {
        return enabled();
    }
};

#endif
