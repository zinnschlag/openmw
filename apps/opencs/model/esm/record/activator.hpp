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
    ActivatorDataItem(ModelItem *parent);

    virtual void load(ESM::ESMReader &esm)
    {
        mActivator.load(esm);
    }

    virtual QString type() {return "ACTI";}

    QString name()
    {
        return QString::fromStdString(mActivator.mName);
    }

    void setName(QString name)
    {
        mActivator.mName = name.toStdString();
        emit nameChanged(name);
    }

    QString model()
    {
        return QString::fromStdString(mActivator.mModel);
    }

    void setModel(QString model)
    {
        mActivator.mModel = model.toStdString();
        emit modelChanged(model);
    }

    QString script()
    {
        return QString::fromStdString(mActivator.mScript);
    }

    void setScript(QString script)
    {
        mActivator.mScript = script.toStdString();
        emit scriptChanged(script);
    }

signals:
    void nameChanged(QString);
    void modelChanged(QString);
    void scriptChanged(QString);

private:
    ESM::Activator mActivator;
};

#endif
