#ifndef FILTERDOM_HPP
#define FILTERDOM_HPP

#include <QObject>
#include <QDomElement>


#include "../../model/filter/filter.hpp"
#include "../../model/filter/filterfile.hpp"

#include "../../model/filter/setoperationfilter.hpp"
#include "../../model/filter/defaultfilter.hpp"
#include "../../model/filter/matchfilter.hpp"

class FilterDom : public QObject
{
    Q_OBJECT

public:
    FilterDom(QObject *parent = 0) : QObject(parent) {}
    ~FilterDom(){}

    FilterFile* loadFile(QString fileName, ModelItem *parent);

private:
    Filter* createFilter(const QDomElement &element, ModelItem* parent);
    SetOperationFilter* createSetOperationFilter(const QDomElement &element, ModelItem *parent);
    MatchFilter* createMatchFilter(const QDomElement &element, ModelItem* parent);
};


#endif
