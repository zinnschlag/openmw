#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include "esmdataitem.hpp"

class ScriptDataItem : public ESMDataItem
{
    Q_OBJECT

    Q_CLASSINFO("id", "scriptId")
    Q_PROPERTY(QString scriptId READ scriptId)
    Q_PROPERTY(QString text READ text)

public:
    ScriptDataItem(DataItem *parent);

    virtual void load(ESM::ESMReader &esm)
    {
        mScript.load(esm);
    }

    QString scriptId()
    {
        return QString::fromStdString(mScript.data.name.toString());
    }

    QString text()
    {
        return QString::fromStdString(mScript.scriptText);
    }

private:
    ESM::Script mScript;
};

#endif
