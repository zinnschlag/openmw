#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include "../esmdataitem.hpp"

class ScriptDataItem : public ESMDataItem
{
    Q_OBJECT
    Q_PROPERTY(QString relativeId READ name WRITE setName)
    Q_PROPERTY(QString text READ text WRITE setText)

public:
    ScriptDataItem(DataItem *parent);

    virtual void load(ESM::ESMReader &esm){
        mScript.load(esm);
    }

    QString name() { return QString::fromStdString(mScript.data.name.toString());}
    void setName(QString name) { /*mScript.data.name = name.toStdString();*/}

    QString text() { return QString::fromStdString(mScript.scriptText);}
    void setText(QString text) { mScript.scriptText = text.toStdString();}

private:
    ESM::Script mScript;
};

#endif
