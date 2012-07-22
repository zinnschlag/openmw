#ifndef ACTIVATOR_HPP
#define ACTIVATOR_HPP

#include "../esmdataitem.hpp"


class ActivatorDataItem : public ESMDataItem
{
    Q_OBJECT
    Q_PROPERTY(QString mwName READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QString script READ script WRITE setScript NOTIFY scriptChanged)

public:
    ActivatorDataItem(DataItem *parent);

    virtual void load(ESM::ESMReader &esm){
        mActivator.load(esm);
    }

    QString name() { return QString::fromStdString(mActivator.name);}
    void setName(QString name) { mActivator.name = name.toStdString(); emit nameChanged(name); }

    QString model() { return QString::fromStdString(mActivator.model);}
    void setModel(QString model) { mActivator.model = model.toStdString(); emit modelChanged(model);}

    QString script() { return QString::fromStdString(mActivator.script);}
    void setScript(QString script) { mActivator.script = script.toStdString(); emit scriptChanged(script);}

signals:
    void nameChanged(QString);
    void modelChanged(QString);
    void scriptChanged(QString);

private:
    ESM::Activator mActivator;
};

#endif
