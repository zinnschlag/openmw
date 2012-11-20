#ifndef POTION_HPP
#define POTION_HPP

#include "../esmdataitem.hpp"
#include "magiceffect.hpp"

class PotionDataItem : public ESMDataItem
{
    Q_OBJECT
    Q_PROPERTY(QString mwName READ name WRITE setName)
    Q_PROPERTY(QString model READ model WRITE setModel)
    Q_PROPERTY(QString scriptRef READ script WRITE setScript)

    Q_PROPERTY(QString icon READ icon WRITE setIcon)

    Q_PROPERTY(float weight READ weight WRITE setWeight)
    Q_PROPERTY(int value READ value WRITE setValue)
    Q_PROPERTY(int autoCalc READ autoCalc WRITE setAutoCalc)

public:
    explicit PotionDataItem(ModelItem *parent);

    virtual void load(ESM::ESMReader &esm)
    {
        mPotion.mId = mId.toStdString();
        mPotion.load (esm);

        for (std::vector<ESM::ENAMstruct>::const_iterator iter(mPotion.mEffects.mList.begin()); iter!=mPotion.mEffects.mList.end(); ++iter)
        {
            MagicEffectDataItem *effect = new MagicEffectDataItem(*iter, this);
            this->appendChild(effect);
        }
    }

    virtual QString type()
    {
        return "ALCH";
    }

    QString name()
    {
        return QString::fromStdString(mPotion.mName);
    }

    void setName(QString name)
    {
        mPotion.mName = name.toStdString();
    }


    QString model()
    {
        return QString::fromStdString(mPotion.mModel);
    }

    void setModel(QString model)
    {
        mPotion.mModel = model.toStdString();
    }


    QString script()
    {
        return QString::fromStdString(mPotion.mScript);
    }

    void setScript(QString script)
    {
        mPotion.mScript = script.toStdString();
    }


    QString icon()
    {
        return QString::fromStdString(mPotion.mIcon);
    }

    void setIcon(QString icon)
    {
        mPotion.mIcon = icon.toStdString();
    }


    float weight()
    {
        return mPotion.mData.mWeight;
    }

    void setWeight(float weight)
    {
        mPotion.mData.mWeight = weight;
    }


    int value()
    {
        return mPotion.mData.mValue;
    }

    void setValue(int value)
    {
        mPotion.mData.mValue = value;
    }


    int autoCalc()
    {
        return mPotion.mData.mAutoCalc;
    }

    void setAutoCalc(int autoCalc)
    {
        mPotion.mData.mAutoCalc = autoCalc;
    }

private:
    ESM::Potion mPotion;
};

#endif
