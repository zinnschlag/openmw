#ifndef SETOPERATIONFILTER_HPP
#define SETOPERATIONFILTER_HPP

#include "filter.hpp"
#include <QIcon>

class SetOperationFilter : public Filter
{
    Q_OBJECT

    Q_CLASSINFO("icon.0", "icon")
    Q_PROPERTY(QString icon READ icon)

    Q_CLASSINFO("view.1", "type")
    Q_CLASSINFO("edit.1", "type")
    Q_PROPERTY(OperationType type READ type WRITE setType)

    Q_ENUMS(OperationType)
public:
    enum OperationType {
        Union,
        Intersection
    };

    explicit SetOperationFilter(OperationType type, ModelItem *parent=0);
    ~SetOperationFilter();

    OperationType type(){return mType;}
    void setType(OperationType type){mType = type;}

    QString icon() {
        switch(mType) {
        case SetOperationFilter::Union:
            return ":/icon/filter/union.png";
        case SetOperationFilter::Intersection:
            return ":/icon/filter/intersection.png";
        }
    }

    virtual bool accept(QList<QString> headers, QList<QVariant> row);

private:
    OperationType mType;
};

#endif
