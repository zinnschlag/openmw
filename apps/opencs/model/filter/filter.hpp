#ifndef FILTER_HPP
#define FILTER_HPP

#include <QObject>
#include <QVariant>

class Filter : public QObject
{
    Q_OBJECT
public:
    explicit Filter(Filter *parent = 0);
    ~Filter() {}

    virtual QString displayString() = 0;
    virtual bool accept(QList<QString> headers, QList<QVariant> row) = 0;

    Filter *parent() { return mParentItem;}

    bool enabled() {return mEnabled;}
    void setEnabled(bool enabled){mEnabled = enabled;}

protected:
    bool mEnabled;
    Filter *mParentItem;
};

#endif
