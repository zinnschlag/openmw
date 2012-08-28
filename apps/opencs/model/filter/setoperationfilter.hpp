#ifndef SETOPERATIONFILTER_HPP
#define SETOPERATIONFILTER_HPP

#include "filter.hpp"

class SetOperationFilter : public FilterList
{
    Q_OBJECT

    Q_PROPERTY(OperationType type READ type WRITE setType)

    Q_ENUMS(OperationType)
public:
    enum OperationType {
        Union,
        Intersection
    };

    explicit SetOperationFilter(OperationType type, Filter *parent=0);
    ~SetOperationFilter();

    OperationType type(){return mType;}
    void setType(OperationType type){mType = type;}

    virtual bool accept(QList<QString> headers, QList<QVariant> row);

private:
    OperationType mType;
};

#endif
