#include "enchanting.hpp"
#include "../mwworld/player.hpp"
#include "../mwworld/manualref.hpp"
#include "../mwworld/class.hpp"
#include "../mwworld/containerstore.hpp"
namespace MWMechanics
{

    void Enchanting::setOldItem(MWWorld::Ptr oldItem)
    {
        mOldItemPtr=oldItem;
    }

    void Enchanting::setNewItemName(std::string s)
    {
        mNewItemName=s;
    }

    void Enchanting::setEffect(ESM::EffectList effectList)
    {
        mEffectList=effectList;
    }
    void Enchanting::setEnchantType(int enchantType)
    {
        mEnchantType=enchantType;
    }

    void Enchanting::create()
    {
        std::string mOldItemId= mOldItemPtr.getCellRef().mRefID;
        std::string mObjectType = mOldItemPtr.getTypeName();
        MWWorld::Ptr player= MWBase::Environment::get().getWorld()->getPlayer().getPlayer();
        const MWWorld::ESMStore &store = MWBase::Environment::get().getWorld()->getStore();
        if(mEnchantType==3)
            mCharge=0;
        else
           mCharge=1000;
        mEnchantment.mData.mCharge = mCharge;
        mEnchantment.mData.mType = mEnchantType;
        mEnchantment.mData.mCost = 1000; //TO IMPLEMENT
        mEnchantment.mEffects = mEffectList;
        const ESM::Enchantment *enchantment;
        enchantment = MWBase::Environment::get().getWorld()->createRecord (mEnchantment);

        if (mObjectType =="N3ESM5ArmorE") //Just for test
        {
            const ESM::Armor *record;
            ESM::Armor newItem;
            ESM::Armor oldItem = *store.get<ESM::Armor>().find(mOldItemId);
            newItem=oldItem;
            newItem.mName=mNewItemName;
            newItem.mId="";
            newItem.mData.mEnchant=mCharge;
            newItem.mEnchant=enchantment->mId;
            record = MWBase::Environment::get().getWorld()->createRecord (newItem);
            MWWorld::ManualRef ref (MWBase::Environment::get().getWorld()->getStore(), record->mId);
            MWWorld::Class::get (player).getContainerStore (player).add (ref.getPtr());
        }
        else if(mObjectType =="N3ESM5WeaponE") //Just for test
        {
            const ESM::Weapon *record;
            ESM::Weapon newItem;
            ESM::Weapon oldItem = *store.get<ESM::Weapon>().find(mOldItemId);
            newItem=oldItem;
            newItem.mName=mNewItemName;
            newItem.mId="";
            newItem.mData.mEnchant=mCharge;
            newItem.mEnchant=enchantment->mId;
            record = MWBase::Environment::get().getWorld()->createRecord (newItem);
            MWWorld::ManualRef ref (MWBase::Environment::get().getWorld()->getStore(), record->mId);
            MWWorld::Class::get (player).getContainerStore (player).add (ref.getPtr());
        }
        else if(mObjectType =="N3ESM5ClothingE") //Just for test
        {
            const ESM::Clothing *record;
            ESM::Clothing newItem;
            ESM::Clothing oldItem = *store.get<ESM::Clothing>().find(mOldItemId);
            newItem=oldItem;
            newItem.mName=mNewItemName;
            newItem.mId="";
            newItem.mData.mEnchant=mCharge;
            newItem.mEnchant=enchantment->mId;
            record = MWBase::Environment::get().getWorld()->createRecord (newItem);
            MWWorld::ManualRef ref (MWBase::Environment::get().getWorld()->getStore(), record->mId);
            MWWorld::Class::get (player).getContainerStore (player).add (ref.getPtr());
        }
    }

}
