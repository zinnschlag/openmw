#ifndef UNIONFITLER_HPP
#define UNIONFILTER_HPP

#include "filter.hpp"

class UnionFilter : public Filter
{
    Q_OBJECT

public:
    explicit UnionFilter(QString name, Filter *parent=0) : Filter(parent) {mDisplayName = name;}
    ~UnionFilter() {}

    virtual QString displayString() {return "Union :" + mDisplayName;}
};

#endif
