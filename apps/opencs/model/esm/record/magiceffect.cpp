#include "magiceffect.hpp"

MagicEffectDataItem::MagicEffectDataItem(ESM::ENAMstruct effectData, ModelItem *parent)
    : mMagicEffect(effectData)
    , ESMDataItem(parent)
{
}
