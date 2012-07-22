#include "magiceffect.hpp"

MagicEffectDataItem::MagicEffectDataItem(ESM::ENAMstruct effectData, ESMDataItem *parent)
    : mMagicEffect(effectData)
    , ESMDataItem(parent)
{
}
