#ifndef GAME_MWMECHANICS_ENCHANTING_H
#define GAME_MWMECHANICS_ENCHANTING_H
#include <string>
#include "../mwworld/ptr.hpp"
#include <components/esm/effectlist.hpp>
namespace MWMechanics
{
    class Enchanting
    {
            
            MWWorld::Ptr mOldItem;
            MWWorld::Ptr mNewItem;
            int mEnchant;
        public:
            void setOldItem(MWWorld::Ptr OldItem);
            void setNewItemName(const std::string s);
            void setEnchantment(int enchant);
            void create();
            MWWorld::Ptr getNewItem();
    };
}
#endif
