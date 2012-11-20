#ifndef MAGICEFFECT_HPP
#define MAGICEFFECT_HPP

#include "../esmdataitem.hpp"

class MagicEffectDataItem : public ESMDataItem
{
    Q_OBJECT
    Q_PROPERTY(short effectId READ effectID WRITE setEffectID)
    Q_PROPERTY(int area READ area WRITE setArea)

public:
    MagicEffectDataItem(ESM::ENAMstruct effectData, ModelItem *parent);

    virtual void load(ESM::ESMReader &esm)
    {
//        std::count << "cannot load directly";
//        mMagicEffect.load(esm);
    }


    virtual QString type()
    {
        return "ENAM";
    }


    short effectID()
    {
        return mMagicEffect.mEffectID;
    }

    void setEffectID(short id)
    {
        mMagicEffect.mEffectID = id;
    }

    int area()
    {
        return mMagicEffect.mArea;
    }

    void setArea(int area)
    {
        mMagicEffect.mArea = area;
    }

    //TODO The rest of the properties

private:
    ESM::ENAMstruct mMagicEffect;
};

#endif
