
#include "potion.hpp"

#include <components/esm/loadalch.hpp>

#include "../mwbase/environment.hpp"
#include "../mwbase/world.hpp"
#include "../mwbase/windowmanager.hpp"

#include "../mwworld/ptr.hpp"
#include "../mwworld/actiontake.hpp"
#include "../mwworld/actionapply.hpp"
#include "../mwworld/cellstore.hpp"
#include "../mwworld/physicssystem.hpp"
#include "../mwworld/player.hpp"

#include "../mwgui/tooltips.hpp"

#include "../mwrender/objects.hpp"
#include "../mwrender/renderinginterface.hpp"

namespace MWClass
{
    void Potion::insertObjectRendering (const MWWorld::Ptr& ptr, MWRender::RenderingInterface& renderingInterface) const
    {
        const std::string model = getModel(ptr);
        if (!model.empty()) {
            MWRender::Objects& objects = renderingInterface.getObjects();
            objects.insertBegin(ptr, ptr.getRefData().isEnabled(), false);
            objects.insertMesh(ptr, model);
        }
    }

    void Potion::insertObject(const MWWorld::Ptr& ptr, MWWorld::PhysicsSystem& physics) const
    {
        const std::string model = getModel(ptr);
        if(!model.empty())
            physics.addObject(ptr);
    }

    std::string Potion::getModel(const MWWorld::Ptr &ptr) const
    {
        MWWorld::LiveCellRef<ESM::Potion> *ref =
            ptr.get<ESM::Potion>();
        assert(ref->base != NULL);

        const std::string &model = ref->base->mModel;
        if (!model.empty()) {
            return "meshes\\" + model;
        }
        return "";
    }

    std::string Potion::getName (const MWWorld::Ptr& ptr) const
    {
        MWWorld::LiveCellRef<ESM::Potion> *ref =
            ptr.get<ESM::Potion>();

        return ref->base->mName;
    }

    boost::shared_ptr<MWWorld::Action> Potion::activate (const MWWorld::Ptr& ptr,
        const MWWorld::Ptr& actor) const
    {
    	boost::shared_ptr<MWWorld::Action> action(
    	            new MWWorld::ActionTake (ptr));

    	action->setSound (getUpSoundId(ptr));

        return action;
    }

    std::string Potion::getScript (const MWWorld::Ptr& ptr) const
    {
        MWWorld::LiveCellRef<ESM::Potion> *ref =
            ptr.get<ESM::Potion>();

        return ref->base->mScript;
    }

    int Potion::getValue (const MWWorld::Ptr& ptr) const
    {
        MWWorld::LiveCellRef<ESM::Potion> *ref =
            ptr.get<ESM::Potion>();

        return ref->base->mData.mValue;
    }

    void Potion::registerSelf()
    {
        boost::shared_ptr<Class> instance (new Potion);

        registerClass (typeid (ESM::Potion).name(), instance);
    }

    std::string Potion::getUpSoundId (const MWWorld::Ptr& ptr) const
    {
        return std::string("Item Potion Up");
    }

    std::string Potion::getDownSoundId (const MWWorld::Ptr& ptr) const
    {
        return std::string("Item Potion Down");
    }

    std::string Potion::getInventoryIcon (const MWWorld::Ptr& ptr) const
    {
          MWWorld::LiveCellRef<ESM::Potion> *ref =
            ptr.get<ESM::Potion>();

        return ref->base->mIcon;
    }

    bool Potion::hasToolTip (const MWWorld::Ptr& ptr) const
    {
        MWWorld::LiveCellRef<ESM::Potion> *ref =
            ptr.get<ESM::Potion>();

        return (ref->base->mName != "");
    }

    MWGui::ToolTipInfo Potion::getToolTipInfo (const MWWorld::Ptr& ptr) const
    {
        MWWorld::LiveCellRef<ESM::Potion> *ref =
            ptr.get<ESM::Potion>();

        MWGui::ToolTipInfo info;
        info.caption = ref->base->mName + MWGui::ToolTips::getCountString(ptr.getRefData().getCount());
        info.icon = ref->base->mIcon;

        std::string text;

        text += "\n#{sWeight}: " + MWGui::ToolTips::toString(ref->base->mData.mWeight);
        text += MWGui::ToolTips::getValueString(ref->base->mData.mValue, "#{sValue}");

        info.effects = MWGui::Widgets::MWEffectList::effectListFromESM(&ref->base->mEffects);
        info.isPotion = true;

        if (MWBase::Environment::get().getWindowManager()->getFullHelp()) {
            text += MWGui::ToolTips::getMiscString(ref->ref.mOwner, "Owner");
            text += MWGui::ToolTips::getMiscString(ref->base->mScript, "Script");
        }

        info.text = text;

        return info;
    }

    boost::shared_ptr<MWWorld::Action> Potion::use (const MWWorld::Ptr& ptr) const
    {
        MWWorld::LiveCellRef<ESM::Potion> *ref =
            ptr.get<ESM::Potion>();

        ptr.getRefData().setCount (ptr.getRefData().getCount()-1);

        MWWorld::Ptr actor = MWBase::Environment::get().getWorld()->getPlayer().getPlayer();

        boost::shared_ptr<MWWorld::Action> action (
            new MWWorld::ActionApply (actor, ref->base->mId));

        action->setSound ("Drink");

        return action;
    }

    MWWorld::Ptr
    Potion::copyToCellImpl(const MWWorld::Ptr &ptr, MWWorld::CellStore &cell) const
    {
        MWWorld::LiveCellRef<ESM::Potion> *ref =
            ptr.get<ESM::Potion>();

        return MWWorld::Ptr(&cell.potions.insert(*ref), &cell);
    }
}
