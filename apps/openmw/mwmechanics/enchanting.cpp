#include "enchanting.hpp"
#include "../mwworld/player.hpp"
#include "../mwworld/manualref.hpp"
#include "../mwworld/class.hpp"
#include "../mwworld/containerstore.hpp"
namespace MWMechanics
{
    Enchanting::Enchanting()
    {
        mEnchantType=0;
    }

    void Enchanting::setOldItem(MWWorld::Ptr oldItem)
    {
        mOldItemPtr=oldItem;
        mObjectType = mOldItemPtr.getTypeName();
        mOldItemId = mOldItemPtr.getCellRef().mRefID;
    }

    void Enchanting::setNewItemName(std::string s)
    {
        mNewItemName=s;
    }

    void Enchanting::setEffect(ESM::EffectList effectList)
    {
        mEffectList=effectList;
    }

    int Enchanting::getEnchantType()
    {
        return mEnchantType;
    }

    void Enchanting::setSoulGem(MWWorld::Ptr soulGem)
    {
        mSoulGem=soulGem;
    }

    void Enchanting::create()
    {
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

        if (mObjectType == typeid(ESM::Armor).name())
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
        else if(mObjectType == typeid(ESM::Weapon).name())
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
        else if(mObjectType == typeid(ESM::Clothing).name())
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
        else if(mObjectType == typeid(ESM::Book).name())
        {
            const ESM::Book *record;
            ESM::Book newItem;
            ESM::Book oldItem = *store.get<ESM::Book>().find(mOldItemId);
            newItem=oldItem;
            newItem.mName=mNewItemName;
            newItem.mId="";
            newItem.mData.mIsScroll=1;
            newItem.mData.mEnchant=0;
            newItem.mEnchant=enchantment->mId;
            record = MWBase::Environment::get().getWorld()->createRecord (newItem);
            MWWorld::ManualRef ref (MWBase::Environment::get().getWorld()->getStore(), record->mId);
            MWWorld::Class::get (player).getContainerStore (player).add (ref.getPtr());
        }
    }
    
    void Enchanting::nextEnchantType()
    {
        mEnchantType++;
        if ((mObjectType == typeid(ESM::Armor).name())||(mObjectType == typeid(ESM::Clothing).name()))
        {
            switch(mEnchantType)
            {
                case 1:
                    mEnchantType = 2;
                case 4:
                    mEnchantType = 2;
            }
        }
        else if(mObjectType == typeid(ESM::Weapon).name())
        {
            switch(mEnchantType)
            {
                case 3:
                    mEnchantType = 1;
            }
        }
        else if(mObjectType == typeid(ESM::Book).name())
        {
            mEnchantType=0;
        }
    }
}
