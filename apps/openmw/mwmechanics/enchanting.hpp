#ifndef GAME_MWMECHANICS_ENCHANTING_H
#define GAME_MWMECHANICS_ENCHANTING_H
#include <string>
#include "../mwworld/ptr.hpp"
#include <components/esm/effectlist.hpp>
#include "../mwbase/world.hpp"
#include "../mwbase/environment.hpp"
namespace MWMechanics
{
    class Enchanting
    {
            
            MWWorld::Ptr mOldItemPtr;
            MWWorld::Ptr mSoulGem;
            const MWWorld::Ptr *mNewItemPtr;
            int mEnchantType;
            int mCharge;
            int mUsedEnchantmentPoints;

            //ESM::Clothing mClothingEnch;
            //ESM::Weapon mWeaponEnch;
            //ESM::Armor mArmorEnch;

            ESM::EffectList mEffectList;
            ESM::Enchantment mEnchantment;

            std::string mNewItemName;
            std::string mObjectType;
            std::string mOldItemId;
        public:
            Enchanting();
            void setOldItem(MWWorld::Ptr oldItem);
            void setNewItemName(std::string s);
            void setEffect(ESM::EffectList effectList);
            void setSoulGem(MWWorld::Ptr soulGem);
            void create();
            const MWWorld::Ptr *getNewItem();
            void nextEnchantType();
            int getEnchantType();
    };
}
#endif
