
#include "weapon.hpp"

#include <components/esm/loadweap.hpp>

#include <components/esm_store/cell_store.hpp>

#include "../mwworld/ptr.hpp"
#include "../mwworld/actiontake.hpp"
#include "../mwworld/environment.hpp"
#include "../mwworld/inventorystore.hpp"

#include "../mwrender/objects.hpp"

#include "../mwsound/soundmanager.hpp"

namespace MWClass
{
    void Weapon::insertObjectRendering (const MWWorld::Ptr& ptr, MWRender::RenderingInterface& renderingInterface) const
    {
        ESMS::LiveCellRef<ESM::Weapon, MWWorld::RefData> *ref =
            ptr.get<ESM::Weapon>();

        assert (ref->base != NULL);
        const std::string &model = ref->base->model;

        if (!model.empty())
        {
            MWRender::Objects& objects = renderingInterface.getObjects();
            objects.insertBegin(ptr, ptr.getRefData().isEnabled(), false);
            objects.insertMesh(ptr, "meshes\\" + model);
        }
    }

    void Weapon::insertObject(const MWWorld::Ptr& ptr, MWWorld::PhysicsSystem& physics, MWWorld::Environment& environment) const
    {
        ESMS::LiveCellRef<ESM::Weapon, MWWorld::RefData> *ref =
            ptr.get<ESM::Weapon>();


        const std::string &model = ref->base->model;
        assert (ref->base != NULL);
        if(!model.empty()){
            physics.insertObjectPhysics(ptr, "meshes\\" + model);
        }

    }

    std::string Weapon::getName (const MWWorld::Ptr& ptr) const
    {
        ESMS::LiveCellRef<ESM::Weapon, MWWorld::RefData> *ref =
            ptr.get<ESM::Weapon>();

        return ref->base->name;
    }

    boost::shared_ptr<MWWorld::Action> Weapon::activate (const MWWorld::Ptr& ptr,
        const MWWorld::Ptr& actor, const MWWorld::Environment& environment) const
    {
        environment.mSoundManager->playSound3D (ptr, getUpSoundId(ptr, environment), 1.0, 1.0, false, true);

        return boost::shared_ptr<MWWorld::Action> (
            new MWWorld::ActionTake (ptr));
    }

    bool Weapon::hasItemHealth (const MWWorld::Ptr& ptr) const
    {
        return true;
    }

    int Weapon::getItemMaxHealth (const MWWorld::Ptr& ptr) const
    {
        ESMS::LiveCellRef<ESM::Weapon, MWWorld::RefData> *ref =
            ptr.get<ESM::Weapon>();

        return ref->base->data.health;
    }

    std::string Weapon::getScript (const MWWorld::Ptr& ptr) const
    {
        ESMS::LiveCellRef<ESM::Weapon, MWWorld::RefData> *ref =
            ptr.get<ESM::Weapon>();

        return ref->base->script;
    }

    std::pair<std::vector<int>, bool> Weapon::getEquipmentSlots (const MWWorld::Ptr& ptr) const
    {
        ESMS::LiveCellRef<ESM::Weapon, MWWorld::RefData> *ref =
            ptr.get<ESM::Weapon>();

        std::vector<int> slots;
        bool stack = false;

        if (ref->base->data.type==ESM::Weapon::Arrow || ref->base->data.type==ESM::Weapon::Bolt)
        {
            slots.push_back (int (MWWorld::InventoryStore::Slot_Ammunition));
            stack = true;
        }
        else if (ref->base->data.type==ESM::Weapon::MarksmanThrown)
        {
            slots.push_back (int (MWWorld::InventoryStore::Slot_CarriedRight));
            stack = true;
        }
        else
            slots.push_back (int (MWWorld::InventoryStore::Slot_CarriedRight));

        return std::make_pair (slots, stack);
    }

    int Weapon::getEuqipmentSkill (const MWWorld::Ptr& ptr,
        const MWWorld::Environment& environment) const
    {
        ESMS::LiveCellRef<ESM::Weapon, MWWorld::RefData> *ref =
            ptr.get<ESM::Weapon>();

        const int size = 12;

        static const int sMapping[size][2] =
        {
            { ESM::Weapon::ShortBladeOneHand, ESM::Skill::ShortBlade },
            { ESM::Weapon::LongBladeOneHand, ESM::Skill::LongBlade },
            { ESM::Weapon::LongBladeTwoHand, ESM::Skill::LongBlade },
            { ESM::Weapon::BluntOneHand, ESM::Skill::BluntWeapon },
            { ESM::Weapon::BluntTwoClose, ESM::Skill::BluntWeapon },
            { ESM::Weapon::BluntTwoWide, ESM::Skill::BluntWeapon },
            { ESM::Weapon::SpearTwoWide, ESM::Skill::Spear },
            { ESM::Weapon::AxeOneHand, ESM::Skill::Axe },
            { ESM::Weapon::AxeTwoHand, ESM::Skill::Axe },
            { ESM::Weapon::MarksmanBow, ESM::Skill::Marksman },
            { ESM::Weapon::MarksmanCrossbow, ESM::Skill::Marksman },
            { ESM::Weapon::MarksmanThrown, ESM::Skill::Marksman }
        };

        for (int i=0; i<size; ++i)
            if (sMapping[i][0]==ref->base->data.type)
                return sMapping[i][1];

        return -1;
    }

    void Weapon::registerSelf()
    {
        boost::shared_ptr<Class> instance (new Weapon);

        registerClass (typeid (ESM::Weapon).name(), instance);
    }

    std::string Weapon::getUpSoundId (const MWWorld::Ptr& ptr, const MWWorld::Environment& environment) const
    {
        ESMS::LiveCellRef<ESM::Weapon, MWWorld::RefData> *ref =
            ptr.get<ESM::Weapon>();

        int type = ref->base->data.type;
        // Ammo
        if (type == 12 || type == 13)
        {
            return std::string("Item Ammo Up");
        }
        // Bow
        if (type == 9)
        {
            return std::string("Item Weapon Bow Up");
        }
        // Crossbow
        if (type == 10)
        {
            return std::string("Item Weapon Crossbow Up");
        }
        // Longblades, One hand and Two
        if (type == 1 || type == 2)
        {
            return std::string("Item Weapon Longblade Up");
        }
        // Shortblade and thrown weapons
        // thrown weapons may not be entirely correct
        if (type == 0 || type == 11)
        {
            return std::string("Item Weapon Shortblade Up");
        }
        // Spear
        if (type == 6)
        {
            return std::string("Item Weapon Spear Up");
        }
        // Blunts and Axes
        if (type == 3 || type == 4 || type == 5 || type == 7 || type == 8)
        {
            return std::string("Item Weapon Blunt Up");
        }

        return std::string("Item Misc Up");
    }

    std::string Weapon::getDownSoundId (const MWWorld::Ptr& ptr, const MWWorld::Environment& environment) const
    {
        ESMS::LiveCellRef<ESM::Weapon, MWWorld::RefData> *ref =
            ptr.get<ESM::Weapon>();

        int type = ref->base->data.type;
        // Ammo
        if (type == 12 || type == 13)
        {
            return std::string("Item Ammo Down");
        }
        // Bow
        if (type == 9)
        {
            return std::string("Item Weapon Bow Down");
        }
        // Crossbow
        if (type == 10)
        {
            return std::string("Item Weapon Crossbow Down");
        }
        // Longblades, One hand and Two
        if (type == 1 || type == 2)
        {
            return std::string("Item Weapon Longblade Down");
        }
        // Shortblade and thrown weapons
        // thrown weapons may not be entirely correct
        if (type == 0 || type == 11)
        {
            return std::string("Item Weapon Shortblade Down");
        }
        // Spear
        if (type == 6)
        {
            return std::string("Item Weapon Spear Down");
        }
        // Blunts and Axes
        if (type == 3 || type == 4 || type == 5 || type == 7 || type == 8)
        {
            return std::string("Item Weapon Blunt Down");
        }

        return std::string("Item Misc Down");
    }
}
