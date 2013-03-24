#include "enchantingdialog.hpp"

#include <boost/lexical_cast.hpp>

#include "../mwbase/environment.hpp"
#include "../mwbase/world.hpp"
#include "../mwworld/player.hpp"
#include "../mwworld/manualref.hpp"

#include "itemselection.hpp"
#include "container.hpp"
#include "inventorywindow.hpp"

namespace MWGui
{


    EnchantingDialog::EnchantingDialog(MWBase::WindowManager &parWindowManager)
        : WindowBase("openmw_enchanting_dialog.layout", parWindowManager)
        , EffectEditorBase(parWindowManager)
        , mItemSelectionDialog(NULL)
        , mCurrentEnchantmentPoints(0)
    {
        getWidget(mName, "NameEdit");
        getWidget(mCancelButton, "CancelButton");
        getWidget(mAvailableEffectsList, "AvailableEffects");
        getWidget(mUsedEffectsView, "UsedEffects");
        getWidget(mItemBox, "ItemBox");
        getWidget(mSoulBox, "SoulBox");
        getWidget(mEnchantmentPoints, "Enchantment");
        getWidget(mCastCost, "CastCost");
        getWidget(mCharge, "Charge");
        getWidget(mTypeButton, "TypeButton");
        getWidget(mBuyButton, "BuyButton");
        getWidget(mPrice, "PriceLabel");

        setWidgets(mAvailableEffectsList, mUsedEffectsView);

        mCancelButton->eventMouseButtonClick += MyGUI::newDelegate(this, &EnchantingDialog::onCancelButtonClicked);
        mItemBox->eventMouseButtonClick += MyGUI::newDelegate(this, &EnchantingDialog::onSelectItem);
        mSoulBox->eventMouseButtonClick += MyGUI::newDelegate(this, &EnchantingDialog::onSelectSoul);
        mBuyButton->eventMouseButtonClick += MyGUI::newDelegate(this, &EnchantingDialog::onBuyButtonClicked);
        mTypeButton->eventMouseButtonClick += MyGUI::newDelegate(this, &EnchantingDialog::onTypeButtonClicked);
        enchanttype=0;
    }

    EnchantingDialog::~EnchantingDialog()
    {
        delete mItemSelectionDialog;
    }

    void EnchantingDialog::open()
    {
        center();
        onRemoveItem(NULL);
        onRemoveSoul(NULL);
    }

    void EnchantingDialog::updateLabels()
    {
        mEnchantmentPoints->setCaption(boost::lexical_cast<std::string>(mCurrentEnchantmentPoints)
                                       + " / " + (mItem.isEmpty() ? "0" : boost::lexical_cast<std::string>(MWWorld::Class::get(mItem).getEnchantmentPoints(mItem))));
        switch(enchanttype)
        {
            case 0:
                mTypeButton->setCaption("CastOnce");
                mAddEffectDialog.constantEffect=false;
                break;
            case 1:
                mTypeButton->setCaption("WhenStrikes");
                mAddEffectDialog.constantEffect=false;
                break;
            case 2:
                mTypeButton->setCaption("WhenUsed");
                mAddEffectDialog.constantEffect=false;
                break;
            case 3:
                mTypeButton->setCaption("ConstantEffect");
                mAddEffectDialog.constantEffect=true;
                break;
        }
    }

    void EnchantingDialog::startEnchanting (MWWorld::Ptr actor)
    {
        mPtr = actor;

        startEditing ();
    }

    void EnchantingDialog::onReferenceUnavailable ()
    {
        mWindowManager.removeGuiMode (GM_Dialogue);
        mWindowManager.removeGuiMode (GM_Enchanting);
    }

    void EnchantingDialog::onCancelButtonClicked(MyGUI::Widget* sender)
    {
        mWindowManager.removeGuiMode (GM_Enchanting);
    }

    void EnchantingDialog::onSelectItem(MyGUI::Widget *sender)
    {
        delete mItemSelectionDialog;
        mItemSelectionDialog = new ItemSelectionDialog("#{sEnchantItems}",
            ContainerBase::Filter_Apparel|ContainerBase::Filter_Weapon|ContainerBase::Filter_NoMagic, mWindowManager);
        mItemSelectionDialog->eventItemSelected += MyGUI::newDelegate(this, &EnchantingDialog::onItemSelected);
        mItemSelectionDialog->eventDialogCanceled += MyGUI::newDelegate(this, &EnchantingDialog::onItemCancel);
        mItemSelectionDialog->setVisible(true);
        mItemSelectionDialog->openContainer(MWBase::Environment::get().getWorld()->getPlayer().getPlayer());
        mItemSelectionDialog->drawItems ();
    }

    void EnchantingDialog::onItemSelected(MWWorld::Ptr item)
    {
        mItemSelectionDialog->setVisible(false);

        while (mItemBox->getChildCount ())
            MyGUI::Gui::getInstance ().destroyWidget (mItemBox->getChildAt(0));

        MyGUI::ImageBox* image = mItemBox->createWidget<MyGUI::ImageBox>("ImageBox", MyGUI::IntCoord(0, 0, 32, 32), MyGUI::Align::Default);
        std::string path = std::string("icons\\");
        path += MWWorld::Class::get(item).getInventoryIcon(item);
        int pos = path.rfind(".");
        path.erase(pos);
        path.append(".dds");
        image->setImageTexture (path);
        image->setUserString ("ToolTipType", "ItemPtr");
        image->setUserData(item);
        image->eventMouseButtonClick += MyGUI::newDelegate(this, &EnchantingDialog::onRemoveItem);

        mItem = item;
        updateLabels();
    }

    void EnchantingDialog::onRemoveItem(MyGUI::Widget *sender)
    {
        while (mItemBox->getChildCount ())
            MyGUI::Gui::getInstance ().destroyWidget (mItemBox->getChildAt(0));
        mItem = MWWorld::Ptr();
        updateLabels();
    }

    void EnchantingDialog::onItemCancel()
    {
        mItemSelectionDialog->setVisible(false);
    }

    void EnchantingDialog::onSoulSelected(MWWorld::Ptr item)
    {
        mItemSelectionDialog->setVisible(false);

        while (mSoulBox->getChildCount ())
            MyGUI::Gui::getInstance ().destroyWidget (mSoulBox->getChildAt(0));

        MyGUI::ImageBox* image = mSoulBox->createWidget<MyGUI::ImageBox>("ImageBox", MyGUI::IntCoord(0, 0, 32, 32), MyGUI::Align::Default);
        std::string path = std::string("icons\\");
        path += MWWorld::Class::get(item).getInventoryIcon(item);
        int pos = path.rfind(".");
        path.erase(pos);
        path.append(".dds");
        image->setImageTexture (path);
        image->setUserString ("ToolTipType", "ItemPtr");
        image->setUserData(item);
        image->eventMouseButtonClick += MyGUI::newDelegate(this, &EnchantingDialog::onRemoveSoul);

        mSoul = item;
        updateLabels();
    }

    void EnchantingDialog::onRemoveSoul(MyGUI::Widget *sender)
    {
        while (mSoulBox->getChildCount ())
            MyGUI::Gui::getInstance ().destroyWidget (mSoulBox->getChildAt(0));
        mSoul = MWWorld::Ptr();
        updateLabels();
    }

    void EnchantingDialog::onSoulCancel()
    {
        mItemSelectionDialog->setVisible(false);
    }

    void EnchantingDialog::onSelectSoul(MyGUI::Widget *sender)
    {
        delete mItemSelectionDialog;
        mItemSelectionDialog = new ItemSelectionDialog("#{sSoulGemsWithSouls}",
            ContainerBase::Filter_Misc|ContainerBase::Filter_ChargedSoulstones, mWindowManager);
        mItemSelectionDialog->eventItemSelected += MyGUI::newDelegate(this, &EnchantingDialog::onSoulSelected);
        mItemSelectionDialog->eventDialogCanceled += MyGUI::newDelegate(this, &EnchantingDialog::onSoulCancel);
        mItemSelectionDialog->setVisible(true);
        mItemSelectionDialog->openContainer(MWBase::Environment::get().getWorld()->getPlayer().getPlayer());
        mItemSelectionDialog->drawItems ();

        //mWindowManager.messageBox("#{sInventorySelectNoSoul}");
    }

    void EnchantingDialog::onTypeButtonClicked(MyGUI::Widget* sender)
    {
        if(enchanttype==3)
            enchanttype=0;
        else
            ++enchanttype;
        updateLabels();
    }

    void EnchantingDialog::onBuyButtonClicked(MyGUI::Widget* sender)
    {
        if (mEffects.size() <= 0)
        {
            mWindowManager.messageBox ("#{sNotifyMessage30}", std::vector<std::string>());
            return;
        }

        if (mName->getCaption ().empty())
        {
            mWindowManager.messageBox ("#{sNotifyMessage10}", std::vector<std::string>());
            return;
        }

        if (mCastCost->getCaption() == "0")
        {
            mWindowManager.messageBox ("#{sEnchantmentMenu8}", std::vector<std::string>());
            return;
        }

        if (boost::lexical_cast<int>(mPrice->getCaption()) > mWindowManager.getInventoryWindow()->getPlayerGold())
        {
            mWindowManager.messageBox ("#{sNotifyMessage18}", std::vector<std::string>());
            return;
        }
        const MWWorld::ESMStore &store = MWBase::Environment::get().getWorld()->getStore();
        std::string typeName = mItem.getTypeName();
        std::string oldItemId = mItem.getCellRef().mRefID;
        std::string newItemName = mName->getCaption();
        MWWorld::Ptr player = MWBase::Environment::get().getWorld()->getPlayer().getPlayer();

        ESM::Enchantment mEnchantment;
        ESM::EffectList effectList;
        effectList.mList = mEffects;
        mEnchantment.mData.mCost = 1000; //TO IMPLEMENT
        mEnchantment.mEffects = effectList;
        if(enchanttype==3)
            mChargeValue=0;
        else
            mChargeValue=1000;
        mEnchantment.mData.mCharge = mChargeValue;
        mEnchantment.mData.mType = enchanttype;
        const ESM::Enchantment *enchantment;
        enchantment = MWBase::Environment::get().getWorld()->createRecord (mEnchantment);
        
        if (typeName=="N3ESM5ArmorE") //Just for test
        {
            const ESM::Armor *record;
            ESM::Armor newItem;
            ESM::Armor oldItem = *store.get<ESM::Armor>().find(oldItemId);
            newItem=oldItem;
            newItem.mName=newItemName;
            newItem.mId="";
            newItem.mData.mEnchant=mChargeValue;
            newItem.mEnchant=enchantment->mId;
            record = MWBase::Environment::get().getWorld()->createRecord (newItem);
            MWWorld::ManualRef ref (MWBase::Environment::get().getWorld()->getStore(), record->mId);
            MWWorld::Class::get (player).getContainerStore (player).add (ref.getPtr());
        }
        else if(typeName=="N3ESM5WeaponE") //Just for test
        {
            const ESM::Weapon *record;
            ESM::Weapon newItem;
            ESM::Weapon oldItem = *store.get<ESM::Weapon>().find(oldItemId);
            newItem=oldItem;
            newItem.mName=newItemName;
            newItem.mId="";
            newItem.mData.mEnchant=mChargeValue;
            newItem.mEnchant=enchantment->mId;
            record = MWBase::Environment::get().getWorld()->createRecord (newItem);
            MWWorld::ManualRef ref (MWBase::Environment::get().getWorld()->getStore(), record->mId);
            MWWorld::Class::get (player).getContainerStore (player).add (ref.getPtr());
        }
        else if(typeName=="N3ESM5ClothingE") //Just for test
        {
            const ESM::Clothing *record;
            ESM::Clothing newItem;
            ESM::Clothing oldItem = *store.get<ESM::Clothing>().find(oldItemId);
            newItem=oldItem;
            newItem.mName=newItemName;
            newItem.mId="";
            newItem.mData.mEnchant=mChargeValue;
            newItem.mEnchant=enchantment->mId;
            record = MWBase::Environment::get().getWorld()->createRecord (newItem);
            MWWorld::ManualRef ref (MWBase::Environment::get().getWorld()->getStore(), record->mId);
            MWWorld::Class::get (player).getContainerStore (player).add (ref.getPtr());
        }
        mWindowManager.removeGuiMode (GM_Enchanting);
    }
}
