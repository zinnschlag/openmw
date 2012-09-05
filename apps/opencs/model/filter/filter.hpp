#ifndef FILTER_HPP
#define FILTER_HPP

#include <QObject>
#include <QVariant>

#include "../modelitem.hpp"

class Filter : public ModelItem
{
    Q_OBJECT

    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    explicit Filter(Filter *parent = 0);
    ~Filter();

    virtual bool accept(QList<QString> headers, QList<QVariant> row) = 0;

    Filter *parentFilter();
    Filter *childFilter(int row);

    bool enabled();
    void setEnabled(bool enabled);

    QString name();
    void setName(QString name);

signals:
    void enabledChanged();
    void nameChanged();

protected:
    Filter *mParentItem;

    bool mEnabled;
    QString mName;
};

#endif
