#ifndef COMPONENTITEM_HPP
#define COMPONENTITEM_HPP

#include "../modelitem.hpp"

class WidgetItem : public ModelItem
{
    Q_OBJECT

    Q_CLASSINFO("display.0", "title")
    Q_CLASSINFO("edit.0", "title")

    Q_PROPERTY(QString title READ title WRITE setTitle)

public:
    explicit WidgetItem(QString typeName, QString title, Qt::DockWidgetArea area, ModelItem *parent = 0)
        : ModelItem(parent)
        , mTypeName(typeName)
        , mTitle(title)
        , mArea(area)
    {}

    ~WidgetItem() {}

    QString typeName() {return mTypeName;}
    void setTitle(QString title){mTitle = title;}

    QString title() {return mTitle;}
    Qt::DockWidgetArea area() {return mArea;}

protected:
    Qt::DockWidgetArea mArea;

    QString mTypeName;
    QString mTitle;
};

#endif
