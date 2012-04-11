
#include "containerstore.hpp"

#include <cassert>
#include <typeinfo>
#include <stdexcept>

#include <components/esm/loadcont.hpp>

#include "../mwworld/class.hpp"

#include "manualref.hpp"
#include "refdata.hpp"

namespace
{
    template<typename T>
    float getTotalWeight (const ESMS::CellRefList<T, MWWorld::RefData>& cellRefList)
    {
        float sum = 0;

        for (typename ESMS::CellRefList<T, MWWorld::RefData>::List::const_iterator iter (
            cellRefList.list.begin());
            iter!=cellRefList.list.end();
            ++iter)
        {
            if (iter->mData.getCount()>0)
                sum += iter->mData.getCount()*iter->base->data.weight;
        }

        return sum;
    }
}

MWWorld::ContainerStore::ContainerStore() : mStateId (0), mCachedWeight (0), mWeightUpToDate (false) {}

MWWorld::ContainerStore::~ContainerStore() {}

MWWorld::ContainerStoreIterator MWWorld::ContainerStore::begin (int mask)
{
    return ContainerStoreIterator (mask, this);
}

MWWorld::ContainerStoreIterator MWWorld::ContainerStore::end()
{
    return ContainerStoreIterator (this);
}

void MWWorld::ContainerStore::add (const Ptr& ptr)
{
    int type = getType(ptr);
    switch (type)
    {
        case Type_Potion:
        {
            std::string name = ptr.get<ESM::Potion>()->base->name;
            if(__potions.find(name) == __potions.end())
            {
                __potions[name] = 1;
                potions.list.push_back(*ptr.get<ESM::Potion>());
            } // new
            else
                __potions[name] += 1;  // stack
        }break;
        case Type_Apparatus:
        {
            std::string name = ptr.get<ESM::Apparatus>()->base->name;
            if(__appas.find(name) == __appas.end())
            {
                __appas[name] = 1;
                appas.list.push_back(*ptr.get<ESM::Apparatus>());
            } // new
            else
                __appas[name] += 1;  // stack
        }break;
        case Type_Armor:
        {
            std::string name = ptr.get<ESM::Armor>()->base->name;
            if(__armors.find(name) == __armors.end())
            {
                __armors[name] = 1;
                armors.list.push_back(*ptr.get<ESM::Armor>());
            } // new
            else
                __armors[name] += 1;  // stack
        }break;
        case Type_Book:
        {
            std::string name = ptr.get<ESM::Book>()->base->name;
            if(__books.find(name) == __books.end())
            {
                __books[name] = 1;
                books.list.push_back(*ptr.get<ESM::Book>());
            } // new
            else
                __books[name] += 1;  // stack
        }break;
        case Type_Clothing:
        {
            std::string name = ptr.get<ESM::Clothing>()->base->name;
            if(__clothes.find(name) == __clothes.end())
            {
                __clothes[name] = 1;
                clothes.list.push_back(*ptr.get<ESM::Clothing>());
            } // new
            else
                __clothes[name] += 1;  // stack
        }break;
        case Type_Ingredient:
        {
            std::string name = ptr.get<ESM::Ingredient>()->base->name;
            if(__ingreds.find(name) == __ingreds.end())
            {
                __ingreds[name] = 1;
                ingreds.list.push_back(*ptr.get<ESM::Ingredient>());
            } // new
            else
                __ingreds[name] += 1;  // stack
        }break;
        case Type_Light:
        {
            std::string name = ptr.get<ESM::Light>()->base->name;
            if(__lights.find(name) == __lights.end())
            {
                __lights[name] = 1;
                lights.list.push_back(*ptr.get<ESM::Light>());
            } // new
            else
                __lights[name] += 1;  // stack
        }break;
        case Type_Lockpick:
        {
            std::string name = ptr.get<ESM::Tool>()->base->name;
            if(__lockpicks.find(name) == __lockpicks.end())
            {
                __lockpicks[name] = 1;
                lockpicks.list.push_back(*ptr.get<ESM::Tool>());
            } // new
            else
                __lockpicks[name] += 1;  // stack
        }break;
        case Type_Miscellaneous:
        {
            std::string name = ptr.get<ESM::Miscellaneous>()->base->name;
            if(__miscItems.find(name) == __miscItems.end())
            {
                __miscItems[name] = 1;
                miscItems.list.push_back(*ptr.get<ESM::Miscellaneous>());
            } // new
            else
                __miscItems[name] += 1;  // stack
        }break;
        case Type_Probe:
        {
            std::string name = ptr.get<ESM::Probe>()->base->name;
            if(__probes.find(name) == __probes.end())
            {
                __probes[name] = 1;
                probes.list.push_back(*ptr.get<ESM::Probe>());
            } // new
            else
                __probes[name] += 1;  // stack
        }break;
        case Type_Repair:
        {
            std::string name = ptr.get<ESM::Repair>()->base->name;
            if(__repairs.find(name) == __repairs.end())
            {
                __repairs[name] = 1;
                repairs.list.push_back(*ptr.get<ESM::Repair>());
            } // new
            else
                __repairs[name] += 1;  // stack
        }break;
        case Type_Weapon:
        {
            std::string name = ptr.get<ESM::Weapon>()->base->name;
            if(__weapons.find(name) == __weapons.end())
            {
                __weapons[name] = 1;
                weapons.list.push_back(*ptr.get<ESM::Weapon>());
            } // new
            else
                __weapons[name] += 1;  // stack
        }break;
        default:
            throw std::logic_error("trying to add an item that does not have a record.");
    }

    flagAsModified();
}

void ContainerStore::remove(const Ptr& ptr)
{
    int type = getType(ptr);
    typedef std::map<std::string,short>::iterator IterType;
    switch(type)
    {
       case Type_Potion:
       {
            std::string name = ptr.get<ESM::Potion>()->base->name;
            IterType iter = __potions.find(name);
            if(iter == __potions.end())
                throw std::runtime_error("trying to remove a potion that is not in the container");
            else
            {
                __potions.erase(iter);
                ESMS::CellRefList<ESM::Potion,RefData>::List::iterator list_iter = potions.find(*ptr.get<ESM::Potion>());
                potions.erase(list_iter);
            }
       }break;
       case Type_Apparatus:
       {
            std::string name = ptr.get<ESM::Apparatus>()->base->name;
            IterType iter = __appas.find(name);
            if(iter == __appas.end())
                throw std::runtime_error("trying to remove an apparatus that is not in the container");
            else
            {
                __appas.erase(iter);
                ESMS::CellRefList<ESM::Apparatus,RefData>::List::iterator list_iter = appas.find(*ptr.get<ESM::Apparatus>());
                appas.erase(list_iter);
            }
       }
    }
    flagAsModified();
}

int ContainerStore::getStackCount(const Ptr& ptr)
{
    int type = getType(ptr);
    typedef std::map<std::string,short>::iterator IterType;
    switch(type)
    {
        case Type_Potion:
        {
             std::string name = ptr.get<ESM::Potion>()->base->name;
             IterType iter = __potions.find(name);
             if(iter == __potions.end())
                  throw std::runtime_error("trying to to get the stack count of a potion that is not in the container");
             else
                return iter->second;
        }break;
        case Type_Apparatus:
        {
            std::string name = ptr.get<ESM::Apparatus>()->base->name;
            IterType iter = __appas.find(name);
            if(iter == __appas.end())
                 throw std::runtime_error("trying to to get the stack count of an apparatus that is not in the container");
            else
               return iter->second;
        }break;
        case Type_Armor:
        {
            std::string name = ptr.get<ESM::Armor>()->base->name;
            IterType iter = __armors.find(name);
            if(iter == __armors.end())
                 throw std::runtime_error("trying to to get the stack count of an armor that is not in the container");
            else
               return iter->second;
        }break;
        case Type_Book:
        {
            std::string name = ptr.get<ESM::Book>()->base->name;
            IterType iter = __books.find(name);
            if(iter == __books.end())
                 throw std::runtime_error("trying to to get the stack count of a book that is not in the container");
            else
               return iter->second;
        }break;
        case Type_Clothing:
        {
            std::string name = ptr.get<ESM::Clothing>()->base->name;
            IterType iter = __clothes.find(name);
            if(iter == __clothes.end())
                 throw std::runtime_error("trying to to get the stack count of an apparel part that is not in the container");
            else
               return iter->second;
        }break;
        case Type_Ingredient:
        {
            std::string name = ptr.get<ESM::Ingredient>()->base->name;
            IterType iter = __ingreds.find(name);
            if(iter == __ingreds.end())
                 throw std::runtime_error("trying to to get the stack count of an ingredient that is not in the container");
            else
               return iter->second;
        }break;
        case Type_Light:
        {
            std::string name = ptr.get<ESM::Light>()->base->name;
            IterType iter = __lights.find(name);
            if(iter == __lights.end())
                 throw std::runtime_error("trying to to get the stack count of a light source that is not in the container");
            else
               return iter->second;
        }break;
        case Type_Lockpick:
        {
            std::string name = ptr.get<ESM::Tool>()->base->name;
            IterType iter = __lockpicks.find(name);
            if(iter == __lockpicks.end())
                 throw std::runtime_error("trying to to get the stack count of a lockpick that is not in the container");
            else
               return iter->second;
        }break;
        case Type_Miscellaneous:
        {
            std::string name = ptr.get<ESM::Miscellaneous>()->base->name;
            IterType iter = __miscItems.find(name);
            if(iter == __miscItems.end())
                 throw std::runtime_error("trying to to get the stack count of a misc item that is not in the container");
            else
               return iter->second;
        }break;
        case Type_Probe:
        {
            std::string name = ptr.get<ESM::Probe>()->base->name;
            IterType iter = __probes.find(name);
            if(iter == __probes.end())
                 throw std::runtime_error("trying to to get the stack count of a probe that is not in the container");
            else
               return iter->second;
        }break;
        case Type_Repair:
        {
            std::string name = ptr.get<ESM::Repair>()->base->name;
            IterType iter = __repairs.find(name);
            if(iter == __repairs.end())
                 throw std::runtime_error("trying to to get the stack count of a repair tool that is not in the container");
            else
               return iter->second;
        }break;
        case Type_Weapon:
        {
            std::string name = ptr.get<ESM::Weapon>()->base->name;
            IterType iter = __weapon.find(name);
            if(iter == __weapons.end())
                 throw std::runtime_error("trying to to get the stack count of  a weapon that is not in the container");
            else
               return iter->second;
        }break;
    }
    return 0;
}
MWWorl::Ptr ContainerStore::get(std::string name)
{
    // TO DO -- add newlines to the excpetion messages and see if that checks are really neccessary
    if(__potions.find(name) != __potions.end()) 
    {
        if(__potions[name] < 1)
           throw std::runtime_error("tried to get a potion whose stack count was 0");
        ESMS::LiveCellRef<ESM::Potion,RefData>* liveCellRef = potions.find(name);
        MWWorld::Ptr ptr(liveCellRef,0);
        return ptr;
    }
    else if(__appas.find(name) != __appas.end())
    {
       if(__appas[name] < 1)
           throw std::runtime_error("tried to get an apparatus whose stack count was 0");
        ESMS::LiveCellRef<ESM::Apparatus,RefData>* liveCellRef = appas.find(name);
        MWWorld::Ptr ptr(liveCellRef,0);
        return ptr;
    }
    else if(__armors.find(name) != __armors.end())
    {
        if(__armors[name] < 1)
            throw std::runtime_error("tried to get an armor whose stack count was 0");
         ESMS::LiveCellRef<ESM::Armor,RefData>* liveCellRef = armors.find(name);
         MWWorld::Ptr ptr(liveCellRef,0);
         return ptr;
    }
    else if(__books.find(name) != __books.end())
    {
        if(__books[name] < 1)
            throw std::runtime_error("tried to get a book whose stack count was 0");
         ESMS::LiveCellRef<ESM::Book,RefData>* liveCellRef = books.find(name);
         MWWorld::Ptr ptr(liveCellRef,0);
         return ptr;
    }
    else if(__clothes.find(name) != __clothes.end())
    {
        if(__clothes[name] < 1)
            throw std::runtime_error("tried to get an apparel part whose stack count was 0");
         ESMS::LiveCellRef<ESM::Clothing,RefData>* liveCellRef = clothes.find(name);
         MWWorld::Ptr ptr(liveCellRef,0);
         return ptr;
    }
    else if(__ingreds.find(name) != __ingreds.end())
    {
        if(__ingreds[name] < 1)
            throw std::runtime_error("tried to get an ingredient whose stack count was 0");
         ESMS::LiveCellRef<ESM::Ingredient,RefData>* liveCellRef = ingreds.find(name);
         MWWorld::Ptr ptr(liveCellRef,0);
         return ptr;
    }
    else if(__lights.find(name) != __lights.end())
    {
        if(__lights[name] < 1)
            throw std::runtime_error("tried to get a light source whose stack count was 0");
         ESMS::LiveCellRef<ESM::Light,RefData>* liveCellRef = lights.find(name);
         MWWorld::Ptr ptr(liveCellRef,0);
         return ptr;
    }
    else if(__lockpicks.find(name) != __lockpicks.end())
    {
        if(__lockpicks[name] < 1)
            throw std::runtime_error("tried to get a lockpick whose stack count was 0");
         ESMS::LiveCellRef<ESM::Tool,RefData>* liveCellRef = lockpicks.find(name);
         MWWorld::Ptr ptr(liveCellRef,0);
         return ptr;
    }
    else if(__miscItems.find(name) != __miscItems.end())
    {
        if(__miscItems[name] < 1)
            throw std::runtime_error("tried to get a misc item whose stack count was 0");
         ESMS::LiveCellRef<ESM::Miscellaneous,RefData>* liveCellRef = miscItems.find(name);
         MWWorld::Ptr ptr(liveCellRef,0);
         return ptr;
    }
    else if(__probes.find(name) != __probes.end())
    {
        if(__probes[name] < 1)
            throw std::runtime_error("tried to get a probe whose stack count was 0");
         ESMS::LiveCellRef<ESM::Miscellaneous,RefData>* liveCellRef = probes.find(name);
         MWWorld::Ptr ptr(liveCellRef,0);
         return ptr;
    }
    else if(__repairs.find(name) != __repairs.end())
    {
        if(__repairs[name] < 1)
            throw std::runtime_error("tried to get an item that helps with repairing whose stack count was 0");
         ESMS::LiveCellRef<ESM::Repair,RefData>* liveCellRef = repairs.find(name);
         MWWorld::Ptr ptr(liveCellRef,0);
         return ptr;
    }
    else if(__weapons.find(name) != __repairs.end())
    {
        if(__weapons[name] < 1)
            throw std::runtime_error("tried to get a weapon whose stack count was 0");
         ESMS::LiveCellRef<ESM::Weapon,RefData>* liveCellRef = weapons.find(name);
         MWWorld::Ptr ptr(liveCellRef,0);
         return ptr;
    }
    else
        throw std::runtime_error("there is no item with name " + name + " in this container" );
}

bool ContainerStore::contains(const Ptr& ptr)
{
    int type = getType(ptr);
    switch(type)
    {
         case Type_Potion:
         {
               std::string name = ptr.get<ESM::Potion>()->base->name;
               return __potions.find(name) != __potions.end();
         }break;
    }
}

void MWWorld::ContainerStore::fill (const ESM::InventoryList& items, const ESMS::ESMStore& store)
{
    for (std::vector<ESM::ContItem>::const_iterator iter (items.list.begin()); iter!=items.list.end();
        ++iter)
    {
        ManualRef ref (store, iter->item.toString());

        if (ref.getPtr().getTypeName()==typeid (ESM::ItemLevList).name())
        {
            /// \todo implement leveled item lists
            continue;
        }

        ref.getPtr().getRefData().setCount (iter->count);
        add (ref.getPtr());
    }

    flagAsModified();
}

void MWWorld::ContainerStore::clear()
{
    potions.list.clear();__potions.clear();
    appas.list.clear();__appas.clear();
    armors.list.clear();__armors.clear();
    books.list.clear();__books.clear();
    clothes.list.clear();__clothes.clear();
    ingreds.list.clear();__ingreds.clear();
    lights.list.clear();__lights.clear();
    lockpicks.list.clear();__lockpicks.clear();
    miscItems.list.clear();__miscItems.clear();
    probes.list.clear();__probes.clear();
    repairs.list.clear();__repairs.clear();
    weapons.list.clear();__weapons.clear();

    flagAsModified();
}

void MWWorld::ContainerStore::flagAsModified()
{
    ++mStateId;
    mWeightUpToDate = false;
}

int MWWorld::ContainerStore::getStateId() const
{
    return mStateId;
}

float MWWorld::ContainerStore::getWeight() const
{
    if (!mWeightUpToDate)
    {
        mCachedWeight = 0;

        mCachedWeight += getTotalWeight (potions);
        mCachedWeight += getTotalWeight (appas);
        mCachedWeight += getTotalWeight (armors);
        mCachedWeight += getTotalWeight (books);
        mCachedWeight += getTotalWeight (clothes);
        mCachedWeight += getTotalWeight (ingreds);
        mCachedWeight += getTotalWeight (lights);
        mCachedWeight += getTotalWeight (lockpicks);
        mCachedWeight += getTotalWeight (miscItems);
        mCachedWeight += getTotalWeight (probes);
        mCachedWeight += getTotalWeight (repairs);
        mCachedWeight += getTotalWeight (weapons);

        mWeightUpToDate = true;
    }

    return mCachedWeight;
}

int MWWorld::ContainerStore::getType (const Ptr& ptr)
{
    if (ptr.isEmpty())
        throw std::runtime_error ("can't put a non-existent object into a container");

    if (ptr.getTypeName()==typeid (ESM::Potion).name())
        return Type_Potion;

    if (ptr.getTypeName()==typeid (ESM::Apparatus).name())
        return Type_Apparatus;

    if (ptr.getTypeName()==typeid (ESM::Armor).name())
        return Type_Armor;

    if (ptr.getTypeName()==typeid (ESM::Book).name())
        return Type_Book;

    if (ptr.getTypeName()==typeid (ESM::Clothing).name())
        return Type_Clothing;

    if (ptr.getTypeName()==typeid (ESM::Ingredient).name())
        return Type_Ingredient;

    if (ptr.getTypeName()==typeid (ESM::Light).name())
        return Type_Light;

    if (ptr.getTypeName()==typeid (ESM::Tool).name())
        return Type_Lockpick;

    if (ptr.getTypeName()==typeid (ESM::Miscellaneous).name())
        return Type_Miscellaneous;

    if (ptr.getTypeName()==typeid (ESM::Probe).name())
        return Type_Probe;

    if (ptr.getTypeName()==typeid (ESM::Repair).name())
        return Type_Repair;

    if (ptr.getTypeName()==typeid (ESM::Weapon).name())
        return Type_Weapon;

    throw std::runtime_error (
        "Object of type " + ptr.getTypeName() + " can not be placed into a container");
}


MWWorld::ContainerStoreIterator::ContainerStoreIterator (ContainerStore *container)
: mType (-1), mMask (0), mContainer (container)
{}

MWWorld::ContainerStoreIterator::ContainerStoreIterator (int mask, ContainerStore *container)
: mType (0), mMask (mask), mContainer (container)
{
    nextType();
}

void MWWorld::ContainerStoreIterator::incType()
{
    if (mType==0)
        mType = 1;
    else if (mType!=-1)
    {
        mType <<= 1;

        if (mType>ContainerStore::Type_Last)
            mType = -1;
    }
}

void MWWorld::ContainerStoreIterator::nextType()
{
    while (mType!=-1)
    {
        incType();

        if (mType & mMask)
            if (resetIterator())
                break;
    }
}

bool MWWorld::ContainerStoreIterator::resetIterator()
{
    switch (mType)
    {
        case ContainerStore::Type_Potion:

            mPotion = mContainer->potions.list.begin();
            return mPotion!=mContainer->potions.list.end();

        case ContainerStore::Type_Apparatus:

            mApparatus = mContainer->appas.list.begin();
            return mApparatus!=mContainer->appas.list.end();

        case ContainerStore::Type_Armor:

            mArmor = mContainer->armors.list.begin();
            return mArmor!=mContainer->armors.list.end();

        case ContainerStore::Type_Book:

            mBook = mContainer->books.list.begin();
            return mBook!=mContainer->books.list.end();

        case ContainerStore::Type_Clothing:

            mClothing = mContainer->clothes.list.begin();
            return mClothing!=mContainer->clothes.list.end();

        case ContainerStore::Type_Ingredient:

            mIngredient = mContainer->ingreds.list.begin();
            return mIngredient!=mContainer->ingreds.list.end();

        case ContainerStore::Type_Light:

            mLight = mContainer->lights.list.begin();
            return mLight!=mContainer->lights.list.end();

        case ContainerStore::Type_Lockpick:

            mLockpick = mContainer->lockpicks.list.begin();
            return mLockpick!=mContainer->lockpicks.list.end();

        case ContainerStore::Type_Miscellaneous:

            mMiscellaneous = mContainer->miscItems.list.begin();
            return mMiscellaneous!=mContainer->miscItems.list.end();

        case ContainerStore::Type_Probe:

            mProbe = mContainer->probes.list.begin();
            return mProbe!=mContainer->probes.list.end();

        case ContainerStore::Type_Repair:

            mRepair = mContainer->repairs.list.begin();
            return mRepair!=mContainer->repairs.list.end();

        case ContainerStore::Type_Weapon:

            mWeapon = mContainer->weapons.list.begin();
            return mWeapon!=mContainer->weapons.list.end();
    }

    return false;
}

bool MWWorld::ContainerStoreIterator::incIterator()
{
    switch (mType)
    {
        case ContainerStore::Type_Potion:

            ++mPotion;
            return mPotion==mContainer->potions.list.end();

        case ContainerStore::Type_Apparatus:

            ++mApparatus;
            return mApparatus==mContainer->appas.list.end();

        case ContainerStore::Type_Armor:

            ++mArmor;
            return mArmor==mContainer->armors.list.end();

        case ContainerStore::Type_Book:

            ++mBook;
            return mBook==mContainer->books.list.end();

        case ContainerStore::Type_Clothing:

            ++mClothing;
            return mClothing==mContainer->clothes.list.end();

        case ContainerStore::Type_Ingredient:

            ++mIngredient;
            return mIngredient==mContainer->ingreds.list.end();

        case ContainerStore::Type_Light:

            ++mLight;
            return mLight==mContainer->lights.list.end();

        case ContainerStore::Type_Lockpick:

            ++mLockpick;
            return mLockpick==mContainer->lockpicks.list.end();

        case ContainerStore::Type_Miscellaneous:

            ++mMiscellaneous;
            return mMiscellaneous==mContainer->miscItems.list.end();

        case ContainerStore::Type_Probe:

            ++mProbe;
            return mProbe==mContainer->probes.list.end();

        case ContainerStore::Type_Repair:

            ++mRepair;
            return mRepair==mContainer->repairs.list.end();

        case ContainerStore::Type_Weapon:

            ++mWeapon;
            return mWeapon==mContainer->weapons.list.end();
    }

    return true;
}

MWWorld::Ptr *MWWorld::ContainerStoreIterator::operator->() const
{
    mPtr = **this;
    return &mPtr;
}

MWWorld::Ptr MWWorld::ContainerStoreIterator::operator*() const
{
    Ptr ptr;

    switch (mType)
    {
        case ContainerStore::Type_Potion: ptr = MWWorld::Ptr (&*mPotion, 0); break;
        case ContainerStore::Type_Apparatus: ptr = MWWorld::Ptr (&*mApparatus, 0); break;
        case ContainerStore::Type_Armor: ptr = MWWorld::Ptr (&*mArmor, 0); break;
        case ContainerStore::Type_Book: ptr = MWWorld::Ptr (&*mBook, 0); break;
        case ContainerStore::Type_Clothing: ptr = MWWorld::Ptr (&*mClothing, 0); break;
        case ContainerStore::Type_Ingredient: ptr = MWWorld::Ptr (&*mIngredient, 0); break;
        case ContainerStore::Type_Light: ptr = MWWorld::Ptr (&*mLight, 0); break;
        case ContainerStore::Type_Lockpick: ptr = MWWorld::Ptr (&*mLockpick, 0); break;
        case ContainerStore::Type_Miscellaneous: ptr = MWWorld::Ptr (&*mMiscellaneous, 0); break;
        case ContainerStore::Type_Probe: ptr = MWWorld::Ptr (&*mProbe, 0); break;
        case ContainerStore::Type_Repair: ptr = MWWorld::Ptr (&*mRepair, 0); break;
        case ContainerStore::Type_Weapon: ptr = MWWorld::Ptr (&*mWeapon, 0); break;
    }

    if (ptr.isEmpty())
        throw std::runtime_error ("invalid iterator");

    ptr.setContainerStore (mContainer);

    return ptr;
}

MWWorld::ContainerStoreIterator& MWWorld::ContainerStoreIterator::operator++()
{
    do
    {
        if (incIterator())
            nextType();
    }
    while (mType!=-1 && !(**this).getRefData().getCount());

    return *this;
}

MWWorld::ContainerStoreIterator MWWorld::ContainerStoreIterator::operator++ (int)
{
    ContainerStoreIterator iter (*this);
    ++*this;
    return iter;
}

bool MWWorld::ContainerStoreIterator::isEqual (const ContainerStoreIterator& iter) const
{
    assert (mContainer==iter.mContainer);

    if (mType!=iter.mType)
        return false;

    switch (mType)
    {
        case ContainerStore::Type_Potion: return mPotion==iter.mPotion;
        case ContainerStore::Type_Apparatus: return mApparatus==iter.mApparatus;
        case ContainerStore::Type_Armor: return mArmor==iter.mArmor;
        case ContainerStore::Type_Book: return mBook==iter.mBook;
        case ContainerStore::Type_Clothing: return mClothing==iter.mClothing;
        case ContainerStore::Type_Ingredient: return mIngredient==iter.mIngredient;
        case ContainerStore::Type_Light: return mLight==iter.mLight;
        case ContainerStore::Type_Lockpick: return mLockpick==iter.mLockpick;
        case ContainerStore::Type_Miscellaneous: return mMiscellaneous==iter.mMiscellaneous;
        case ContainerStore::Type_Probe: return mProbe==iter.mProbe;
        case ContainerStore::Type_Repair: return mRepair==iter.mRepair;
        case ContainerStore::Type_Weapon: return mWeapon==iter.mWeapon;
        case -1: return true;
    }

    return false;
}

int MWWorld::ContainerStoreIterator::getType() const
{
    return mType;
}

const MWWorld::ContainerStore *MWWorld::ContainerStoreIterator::getContainerStore() const
{
    return mContainer;
}

bool MWWorld::operator== (const ContainerStoreIterator& left, const ContainerStoreIterator& right)
{
    return left.isEqual (right);
}

bool MWWorld::operator!= (const ContainerStoreIterator& left, const ContainerStoreIterator& right)
{
    return !(left==right);
}
