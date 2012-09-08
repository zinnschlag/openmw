#ifndef DEFAULTFILTER_HPP
#define DEFAULTFILTER_HPP

#include "filter.hpp"

class DefaultFilter : public Filter
{
    Q_OBJECT

public:
    explicit DefaultFilter(ModelItem *parent=0)
      : Filter(parent)
    {
    }

    ~DefaultFilter()
    {
    }

    virtual QString displayString()
    {
      return "Default";
    }

    virtual bool accept(QList<QString> headers, QList<QVariant> row)
    {
      return enabled();
    }
};

#endif
