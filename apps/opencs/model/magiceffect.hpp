#ifndef MAGICEFFECT_HPP
#define MAGICEFFECT_HPP

#include "../esmdataitem.hpp"

class MagicEffectDataItem : public ESMDataItem
{
    Q_OBJECT
    Q_PROPERTY(short effectID READ effectID WRITE setEffectID)
    Q_PROPERTY(int area READ area WRITE setArea)

public:
    MagicEffectDataItem(ESM::ENAMstruct effectData, DataItem *parent);

    virtual void load(ESM::ESMReader &esm){
//        std::count << "cannot load directly";
//        mMagicEffect.load(esm);
    }

    short effectID() {return mMagicEffect.effectID ;}
    void setEffectID(short id) { mMagicEffect.effectID = id;}

    int area() {return mMagicEffect.area ;}
    void setArea(int area) { mMagicEffect.area = area;}

    //TODO The rest of the properties

private:
    ESM::ENAMstruct mMagicEffect;
};

#endif
