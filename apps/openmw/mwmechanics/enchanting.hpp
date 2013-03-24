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
            const MWWorld::Ptr *mNewItemPtr;
            int mEnchantType;
            int mCharge;

            //ESM::Clothing mClothingEnch;
            //ESM::Weapon mWeaponEnch;
            //ESM::Armor mArmorEnch;

            ESM::EffectList mEffectList;
            ESM::Enchantment mEnchantment;

            std::string mNewItemName;
        public:
            void setOldItem(MWWorld::Ptr oldItem);
            void setNewItemName(std::string s);
            void setEffect(ESM::EffectList effectList);
            void setEnchantType(int enchantType);
            void create();
            const MWWorld::Ptr *getNewItem();
    };
}
#endif
