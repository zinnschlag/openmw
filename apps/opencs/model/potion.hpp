#ifndef POTION_HPP
#define POTION_HPP

#include "../esmdataitem.hpp"
#include "magiceffect.hpp"

class PotionDataItem : public ESMDataItem
{
    Q_OBJECT
    Q_PROPERTY(QString mwName READ name WRITE setName)
    Q_PROPERTY(QString model READ model WRITE setModel)
    Q_PROPERTY(QString script READ script WRITE setScript)

    Q_PROPERTY(QString icon READ icon WRITE setIcon)

    Q_PROPERTY(float weight READ weight WRITE setWeight)
    Q_PROPERTY(int value READ value WRITE setValue)
    Q_PROPERTY(int autoCalc READ autoCalc WRITE setAutoCalc)

public:
    PotionDataItem(ESMDataItem *parent);

    virtual void load(ESM::ESMReader &esm){
        //WTF is this :/
        mPotion.load(esm, mId.toStdString());

        for(std::vector<ESM::ENAMstruct>::const_iterator iter(mPotion.effects.list.begin()); iter!=mPotion.effects.list.end(); ++iter)
        {
            MagicEffectDataItem *effect = new MagicEffectDataItem(*iter, this);
            this->appendChild(effect);
        }
    }

    QString name() { return QString::fromStdString(mPotion.name);}
    void setName(QString name) { mPotion.name = name.toStdString();}

    QString model() { return QString::fromStdString(mPotion.model);}
    void setModel(QString model) { mPotion.model = model.toStdString();}

    QString script() { return QString::fromStdString(mPotion.script);}
    void setScript(QString script) { mPotion.script = script.toStdString();}


    QString icon() { return QString::fromStdString(mPotion.icon);}
    void setIcon(QString icon) { mPotion.icon = icon.toStdString();}


    float weight() { return mPotion.data.weight;}
    void setWeight(float weight) { mPotion.data.weight = weight;}

    int value() { return mPotion.data.value;}
    void setValue(int value) { mPotion.data.value = value;}

    int autoCalc() { return mPotion.data.autoCalc;}
    void setAutoCalc(int autoCalc) { mPotion.data.autoCalc = autoCalc;}

private:
    ESM::Potion mPotion;
};

#endif
