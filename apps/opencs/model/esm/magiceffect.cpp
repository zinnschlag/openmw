#include "magiceffect.hpp"

MagicEffectDataItem::MagicEffectDataItem(ESM::ENAMstruct effectData, DataItem *parent)
    : mMagicEffect(effectData)
    , ESMDataItem(parent)
{
}
