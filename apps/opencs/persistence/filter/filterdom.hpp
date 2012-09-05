#ifndef FILTERDOM_HPP
#define FILTERDOM_HPP

#include <QObject>
#include <QDomElement>

#include "../../model/filter/filter.hpp"

#include "../../model/filter/setoperationfilter.hpp"
#include "../../model/filter/defaultfilter.hpp"
#include "../../model/filter/matchfilter.hpp"

class FilterDom : public QObject
{
    Q_OBJECT

public:
    FilterDom(QObject *parent = 0) : QObject(parent) {}
    ~FilterDom(){}

    Filter* loadFile(QString fileName, Filter *parent);

    Filter* createFilter(const QDomElement &element, Filter* parent);

private:
    SetOperationFilter* createSetOperationFilter(const QDomElement &element, Filter *parent);
    MatchFilter* createMatchFilter(const QDomElement &element, Filter* parent);

};


#endif
