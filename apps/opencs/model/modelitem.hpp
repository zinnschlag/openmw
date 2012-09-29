#ifndef MODELITEM_HPP
#define MODELITEM_HPP

#include <QObject>
#include <QList>
#include <QStringList>

class ModelItem : public QObject
{
    Q_OBJECT

    Q_CLASSINFO("display.0", "objectName")

public:
    ModelItem(ModelItem *parent = 0);
    ModelItem(QString name, ModelItem *parent = 0);
    ~ModelItem();

    ModelItem *parent();
    int row() const;

    int childCount() const;
    int childRow(ModelItem *child) const;
    ModelItem *child(int row);

    void appendChild(ModelItem *child);
    void removeChild(int row);

    QString getFullPathName() {
        QStringList parentNames;

        ModelItem *parent = mParentItem;
        while(parent) {
            parentNames.push_front(parent->objectName());
            parent = parent->parent();
        }

        return parentNames.join("/");
    }
    //virtual bool acceptChild(ModelItem *child);

protected:
    ModelItem *mParentItem;
    QList<ModelItem*> mChildItems;

    QString mPathName;
};

#endif
