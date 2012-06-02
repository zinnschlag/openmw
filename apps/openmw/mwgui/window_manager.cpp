#include "window_manager.hpp"
#include "text_input.hpp"
#include "review.hpp"
#include "dialogue.hpp"
#include "dialogue_history.hpp"
#include "map_window.hpp"
#include "stats_window.hpp"
#include "messagebox.hpp"
#include "container.hpp"
#include "inventorywindow.hpp"
#include "tooltips.hpp"
#include "scrollwindow.hpp"
#include "bookwindow.hpp"
#include "list.hpp"
#include "hud.hpp"
#include "mainmenu.hpp"
#include "countdialog.hpp"
#include "tradewindow.hpp"
#include "settingswindow.hpp"
#include "confirmationdialog.hpp"
#include "alchemywindow.hpp"
#include "spellwindow.hpp"

#include "../mwmechanics/mechanicsmanager.hpp"
#include "../mwinput/inputmanager.hpp"

#include "../mwbase/environment.hpp"

#include "console.hpp"
#include "journalwindow.hpp"
#include "charactercreation.hpp"

#include <components/settings/settings.hpp>

#include <assert.h>
#include <iostream>
#include <iterator>

using namespace MWGui;

WindowManager::WindowManager(
    const Compiler::Extensions& extensions, int fpsLevel, bool newGame, OEngine::Render::OgreRenderer *mOgre, const std::string logpath)
  : mGuiManager(NULL)
  , hud(NULL)
  , map(NULL)
  , menu(NULL)
  , mStatsWindow(NULL)
  , mToolTips(NULL)
  , mMessageBoxManager(NULL)
  , console(NULL)
  , mJournal(NULL)
  , mDialogueWindow(NULL)
  , mBookWindow(NULL)
  , mScrollWindow(NULL)
  , mCountDialog(NULL)
  , mTradeWindow(NULL)
  , mSettingsWindow(NULL)
  , mConfirmationDialog(NULL)
  , mAlchemyWindow(NULL)
  , mSpellWindow(NULL)
  , mCharGen(NULL)
  , playerClass()
  , playerName()
  , playerRaceId()
  , playerAttributes()
  , playerMajorSkills()
  , playerMinorSkills()
  , playerSkillValues()
  , playerHealth()
  , playerMagicka()
  , playerFatigue()
  , gui(NULL)
  , garbageDialogs()
  , shown(GW_ALL)
  , allowed(newGame ? GW_None : GW_ALL)
  , showFPSLevel(fpsLevel)
  , mFPS(0.0f)
  , mTriangleCount(0)
  , mBatchCount(0)
{

    // Set up the GUI system
    mGuiManager = new OEngine::GUI::MyGUIManager(mOgre->getWindow(), mOgre->getScene(), false, logpath);
    gui = mGuiManager->getGui();
    
    //Register own widgets with MyGUI
    MyGUI::FactoryManager::getInstance().registerFactory<DialogueHistory>("Widget");
    MyGUI::FactoryManager::getInstance().registerFactory<MWGui::Widgets::MWSkill>("Widget");
    MyGUI::FactoryManager::getInstance().registerFactory<MWGui::Widgets::MWAttribute>("Widget");
    MyGUI::FactoryManager::getInstance().registerFactory<MWGui::Widgets::MWSpell>("Widget");
    MyGUI::FactoryManager::getInstance().registerFactory<MWGui::Widgets::MWEffectList>("Widget");
    MyGUI::FactoryManager::getInstance().registerFactory<MWGui::Widgets::MWSpellEffect>("Widget");
    MyGUI::FactoryManager::getInstance().registerFactory<MWGui::Widgets::MWDynamicStat>("Widget");
    MyGUI::FactoryManager::getInstance().registerFactory<MWGui::Widgets::MWList>("Widget");

    MyGUI::LanguageManager::getInstance().eventRequestTag = MyGUI::newDelegate(this, &WindowManager::onRetrieveTag);

    // Get size info from the Gui object
    assert(gui);
    int w = MyGUI::RenderManager::getInstance().getViewSize().width;
    int h = MyGUI::RenderManager::getInstance().getViewSize().height;

    MyGUI::Widget* dragAndDropWidget = gui->createWidgetT("Widget","",0,0,w,h,MyGUI::Align::Default,"DragAndDrop","DragAndDropWidget");
    dragAndDropWidget->setVisible(false);

    mDragAndDrop = new DragAndDrop();
    mDragAndDrop->mIsOnDragAndDrop = false;
    mDragAndDrop->mDraggedWidget = 0;
    mDragAndDrop->mDragAndDropWidget = dragAndDropWidget;

    menu = new MainMenu(w,h);
    map = new MapWindow(*this);
    mStatsWindow = new StatsWindow(*this);
    console = new Console(w,h, extensions);
    mJournal = new JournalWindow(*this);
    mMessageBoxManager = new MessageBoxManager(this);
    mInventoryWindow = new InventoryWindow(*this,mDragAndDrop);
    mTradeWindow = new TradeWindow(*this);
    mDialogueWindow = new DialogueWindow(*this);
    mContainerWindow = new ContainerWindow(*this,mDragAndDrop);
    hud = new HUD(w,h, showFPSLevel, mDragAndDrop);
    mToolTips = new ToolTips(this);
    mScrollWindow = new ScrollWindow(*this);
    mBookWindow = new BookWindow(*this);
    mCountDialog = new CountDialog(*this);
    mSettingsWindow = new SettingsWindow(*this);
    mConfirmationDialog = new ConfirmationDialog(*this);
    mAlchemyWindow = new AlchemyWindow(*this);
    mSpellWindow = new SpellWindow(*this);

    // The HUD is always on
    hud->setVisible(true);

    mCharGen = new CharacterCreation(this);

    // Setup player stats
    for (int i = 0; i < ESM::Attribute::Length; ++i)
    {
        playerAttributes.insert(std::make_pair(ESM::Attribute::attributeIds[i], MWMechanics::Stat<int>()));
    }

    for (int i = 0; i < ESM::Skill::Length; ++i)
    {
        playerSkillValues.insert(std::make_pair(ESM::Skill::skillIds[i], MWMechanics::Stat<float>()));
    }

    unsetSelectedSpell();
    unsetSelectedWeapon();

    // Set up visibility
    updateVisible();
}

WindowManager::~WindowManager()
{
    delete mGuiManager;
    delete console;
    delete mMessageBoxManager;
    delete hud;
    delete map;
    delete menu;
    delete mStatsWindow;
    delete mJournal;
    delete mDialogueWindow;
    delete mContainerWindow;
    delete mInventoryWindow;
    delete mToolTips;
    delete mCharGen;
    delete mDragAndDrop;
    delete mBookWindow;
    delete mScrollWindow;
    delete mTradeWindow;
    delete mSettingsWindow;
    delete mConfirmationDialog;
    delete mAlchemyWindow;
    delete mSpellWindow;

    cleanupGarbage();
}

void WindowManager::cleanupGarbage()
{
    // Delete any dialogs which are no longer in use
    if (!garbageDialogs.empty())
    {
        for (std::vector<OEngine::GUI::Layout*>::iterator it = garbageDialogs.begin(); it != garbageDialogs.end(); ++it)
        {
            delete *it;
        }
        garbageDialogs.clear();
    }
}

void WindowManager::update()
{
    cleanupGarbage();

    hud->setFPS(mFPS);
    hud->setTriangleCount(mTriangleCount);
    hud->setBatchCount(mBatchCount);
}

void WindowManager::updateVisible()
{
    // Start out by hiding everything except the HUD
    map->setVisible(false);
    menu->setVisible(false);
    mStatsWindow->setVisible(false);
    console->disable();
    mJournal->setVisible(false);
    mDialogueWindow->setVisible(false);
    mContainerWindow->setVisible(false);
    mInventoryWindow->setVisible(false);
    mScrollWindow->setVisible(false);
    mBookWindow->setVisible(false);
    mTradeWindow->setVisible(false);
    mSettingsWindow->setVisible(false);
    mAlchemyWindow->setVisible(false);
    mSpellWindow->setVisible(false);

    // Mouse is visible whenever we're not in game mode
    MyGUI::PointerManager::getInstance().setVisible(isGuiMode());

    bool gameMode = !isGuiMode();

    if (gameMode)
        mToolTips->enterGameMode();
    else
        mToolTips->enterGuiMode();

    setMinimapVisibility((allowed & GW_Map) && !map->pinned());
    setWeaponVisibility((allowed & GW_Inventory) && !mInventoryWindow->pinned());
    setSpellVisibility((allowed & GW_Magic) && !mSpellWindow->pinned());
    setHMSVisibility((allowed & GW_Stats) && !mStatsWindow->pinned());

    // If in game mode, don't show anything.
    if (gameMode)
        return;

    GuiMode mode = mGuiModes.back();

    switch(mode) {
        case GM_MainMenu:
            menu->setVisible(true);
            break;
        case GM_Settings:
            mSettingsWindow->setVisible(true);
            break;
        case GM_Console:
            console->enable();
            break;
        case GM_Scroll:
            mScrollWindow->setVisible(true);
            break;
        case GM_Book:
            mBookWindow->setVisible(true);
            break;
        case GM_Alchemy:
            mAlchemyWindow->setVisible(true);
            break;
        case GM_Name:
        case GM_Race:
        case GM_Class:
        case GM_ClassPick:
        case GM_ClassCreate:
        case GM_Birth:
        case GM_ClassGenerate:
        case GM_Review:
            mCharGen->spawnDialog(mode);
            break;
        case GM_Inventory:
        {
            // First, compute the effective set of windows to show.
            // This is controlled both by what windows the
            // user has opened/closed (the 'shown' variable) and by what
            // windows we are allowed to show (the 'allowed' var.)
            int eff = shown & allowed;

            // Show the windows we want
            map   -> setVisible(eff & GW_Map);
            mStatsWindow -> setVisible(eff & GW_Stats);
            mInventoryWindow->setVisible(eff & GW_Inventory);
            mSpellWindow->setVisible(eff & GW_Magic);
            break;
        }
        case GM_Container:
            mContainerWindow->setVisible(true);
            mInventoryWindow->setVisible(true);
            break;
        case GM_Dialogue:
            mDialogueWindow->setVisible(true);
            break;
        case GM_Barter:
            mInventoryWindow->setVisible(true);
            mTradeWindow->setVisible(true);
            break;
        case GM_InterMessageBox:
            break;
        case GM_Journal:
            mJournal->setVisible(true);
            mJournal->open();
            break;
        default:
            // Unsupported mode, switch back to game
            break;
    }
}

void WindowManager::setValue (const std::string& id, const MWMechanics::Stat<int>& value)
{
    mStatsWindow->setValue (id, value);
    mCharGen->setValue(id, value);

    static const char *ids[] =
    {
        "AttribVal1", "AttribVal2", "AttribVal3", "AttribVal4", "AttribVal5",
        "AttribVal6", "AttribVal7", "AttribVal8"
    };
    static ESM::Attribute::AttributeID attributes[] =
    {
        ESM::Attribute::Strength,
        ESM::Attribute::Intelligence,
        ESM::Attribute::Willpower,
        ESM::Attribute::Agility,
        ESM::Attribute::Speed,
        ESM::Attribute::Endurance,
        ESM::Attribute::Personality,
        ESM::Attribute::Luck
    };
    for (size_t i = 0; i < sizeof(ids)/sizeof(ids[0]); ++i)
    {
        if (id != ids[i])
            continue;
        playerAttributes[attributes[i]] = value;
        break;
    }
}


void WindowManager::setValue(const ESM::Skill::SkillEnum parSkill, const MWMechanics::Stat<float>& value)
{
    mStatsWindow->setValue(parSkill, value);
    mCharGen->setValue(parSkill, value);
    playerSkillValues[parSkill] = value;
}

void WindowManager::setValue (const std::string& id, const MWMechanics::DynamicStat<int>& value)
{
    mStatsWindow->setValue (id, value);
    hud->setValue (id, value);
    mCharGen->setValue(id, value);
    if (id == "HBar")
    {
        playerHealth = value;
        mCharGen->setPlayerHealth (value);
    }
    else if (id == "MBar")
    {
        playerMagicka = value;
        mCharGen->setPlayerMagicka (value);
    }
    else if (id == "FBar")
    {
        playerFatigue = value;
        mCharGen->setPlayerFatigue (value);
    }
}

#if 0
MWMechanics::DynamicStat<int> WindowManager::getValue(const std::string& id)
{
    if(id == "HBar")
        return playerHealth;
    else if (id == "MBar")
        return playerMagicka;
    else if (id == "FBar")
        return playerFatigue;
}
#endif

void WindowManager::setValue (const std::string& id, const std::string& value)
{
    mStatsWindow->setValue (id, value);
    if (id=="name")
        playerName = value;
    else if (id=="race")
        playerRaceId = value;
}

void WindowManager::setValue (const std::string& id, int value)
{
    mStatsWindow->setValue (id, value);
}

void WindowManager::setPlayerClass (const ESM::Class &class_)
{
    playerClass = class_;
    mStatsWindow->setValue("class", playerClass.name);
}

void WindowManager::configureSkills (const SkillList& major, const SkillList& minor)
{
    mStatsWindow->configureSkills (major, minor);
    mCharGen->configureSkills(major, minor);
    playerMajorSkills = major;
    playerMinorSkills = minor;
}

void WindowManager::setReputation (int reputation)
{
    mStatsWindow->setReputation (reputation);
}

void WindowManager::setBounty (int bounty)
{
    mStatsWindow->setBounty (bounty);
}

void WindowManager::updateSkillArea()
{
    mStatsWindow->updateSkillArea();
}

void WindowManager::removeDialog(OEngine::GUI::Layout*dialog)
{
    assert(dialog);
    if (!dialog)
        return;
    dialog->setVisible(false);
    garbageDialogs.push_back(dialog);
}

void WindowManager::messageBox (const std::string& message, const std::vector<std::string>& buttons)
{
    if (buttons.empty())
    {
        mMessageBoxManager->createMessageBox(message);
    }
    else
    {
        mMessageBoxManager->createInteractiveMessageBox(message, buttons);
        pushGuiMode(GM_InterMessageBox);
    }
}

int WindowManager::readPressedButton ()
{
    return mMessageBoxManager->readPressedButton();
}

const std::string &WindowManager::getGameSettingString(const std::string &id, const std::string &default_)
{
    const ESM::GameSetting *setting = MWBase::Environment::get().getWorld()->getStore().gameSettings.search(id);
    if (setting && setting->type == ESM::VT_String)
        return setting->str;
    return default_;
}

void WindowManager::onDialogueWindowBye()
{
    if (mDialogueWindow)
    {
        //FIXME set some state and stuff?
        //removeDialog(dialogueWindow);
        mDialogueWindow->setVisible(false);
    }
    popGuiMode();
}

void WindowManager::onFrame (float frameDuration)
{
    mMessageBoxManager->onFrame(frameDuration);
    mToolTips->onFrame(frameDuration);

    if (mDragAndDrop->mIsOnDragAndDrop)
    {
        assert(mDragAndDrop->mDraggedWidget);
        mDragAndDrop->mDraggedWidget->setPosition(MyGUI::InputManager::getInstance().getMousePosition());
    }

    mInventoryWindow->onFrame();

    mStatsWindow->onFrame();

    hud->onFrame(frameDuration);

    mDialogueWindow->checkReferenceAvailable();
    mTradeWindow->checkReferenceAvailable();
    mContainerWindow->checkReferenceAvailable();
    console->checkReferenceAvailable();
}

const ESMS::ESMStore& WindowManager::getStore() const
{
    return MWBase::Environment::get().getWorld()->getStore();
}

void WindowManager::changeCell(MWWorld::Ptr::CellStore* cell)
{
    if (!(cell->cell->data.flags & ESM::Cell::Interior))
    {
        std::string name;
        if (cell->cell->name != "")
            name = cell->cell->name;
        else
        {
            const ESM::Region* region = MWBase::Environment::get().getWorld()->getStore().regions.search(cell->cell->region);
            if (region)
                name = region->name;
            else
                name = getGameSettingString("sDefaultCellname", "Wilderness");
        }

        map->setCellName( name );
        hud->setCellName( name );

        map->setCellPrefix("Cell");
        hud->setCellPrefix("Cell");
        map->setActiveCell( cell->cell->data.gridX, cell->cell->data.gridY );
        hud->setActiveCell( cell->cell->data.gridX, cell->cell->data.gridY );
    }
    else
    {
        map->setCellName( cell->cell->name );
        hud->setCellName( cell->cell->name );
        map->setCellPrefix( cell->cell->name );
        hud->setCellPrefix( cell->cell->name );
    }

}

void WindowManager::setInteriorMapTexture(const int x, const int y)
{
    map->setActiveCell(x,y, true);
    hud->setActiveCell(x,y, true);
}

void WindowManager::setPlayerPos(const float x, const float y)
{
    map->setPlayerPos(x,y);
    hud->setPlayerPos(x,y);
}

void WindowManager::setPlayerDir(const float x, const float y)
{
    map->setPlayerDir(x,y);
    hud->setPlayerDir(x,y);
}

void WindowManager::setHMSVisibility(bool visible)
{
    hud->setBottomLeftVisibility(visible, hud->weapBox->getVisible(), hud->spellBox->getVisible());
}

void WindowManager::setMinimapVisibility(bool visible)
{
    hud->setBottomRightVisibility(hud->effectBox->getVisible(), visible);
}

void WindowManager::toggleFogOfWar()
{
    map->toggleFogOfWar();
    hud->toggleFogOfWar();
}

void WindowManager::setFocusObject(const MWWorld::Ptr& focus)
{
    mToolTips->setFocusObject(focus);
}

void WindowManager::setFocusObjectScreenCoords(float min_x, float min_y, float max_x, float max_y)
{
    mToolTips->setFocusObjectScreenCoords(min_x, min_y, max_x, max_y);
}

void WindowManager::toggleFullHelp()
{
    mToolTips->toggleFullHelp();
}

bool WindowManager::getFullHelp() const
{
    return mToolTips->getFullHelp();
}

void WindowManager::setWeaponVisibility(bool visible)
{
    hud->setBottomLeftVisibility(hud->health->getVisible(), visible, hud->spellBox->getVisible());
}

void WindowManager::setSpellVisibility(bool visible)
{
    hud->setBottomLeftVisibility(hud->health->getVisible(), hud->weapBox->getVisible(), visible);
    hud->setBottomRightVisibility(visible, hud->minimapBox->getVisible());
}

void WindowManager::setMouseVisible(bool visible)
{
    MyGUI::PointerManager::getInstance().setVisible(visible);
}

void WindowManager::setDragDrop(bool dragDrop)
{
    mToolTips->setEnabled(!dragDrop);
    MWBase::Environment::get().getInputManager()->setDragDrop(dragDrop);
}

void WindowManager::onRetrieveTag(const MyGUI::UString& _tag, MyGUI::UString& _result)
{
    const ESM::GameSetting *setting = MWBase::Environment::get().getWorld()->getStore().gameSettings.search(_tag);
    if (setting && setting->type == ESM::VT_String)
        _result = setting->str;
    else
        _result = _tag;
}

void WindowManager::processChangedSettings(const Settings::CategorySettingVector& changed)
{
    hud->setFpsLevel(Settings::Manager::getInt("fps", "HUD"));
    mToolTips->setDelay(Settings::Manager::getFloat("tooltip delay", "GUI"));

    bool changeRes = false;
    for (Settings::CategorySettingVector::const_iterator it = changed.begin();
        it != changed.end(); ++it)
    {
        if (it->first == "Video" &&  (
            it->second == "resolution x"
            || it->second == "resolution y"))
        {
            changeRes = true;
        }
    }

    if (changeRes)
    {
        int x = Settings::Manager::getInt("resolution x", "Video");
        int y = Settings::Manager::getInt("resolution y", "Video");
        hud->onResChange(x, y);
        console->onResChange(x, y);
        mSettingsWindow->center();
        mDragAndDrop->mDragAndDropWidget->setSize(MyGUI::IntSize(x, y));
    }
}

void WindowManager::pushGuiMode(GuiMode mode)
{
    if (mode==GM_Inventory && allowed==GW_None)
        return;

    mGuiModes.push_back(mode);

    bool gameMode = !isGuiMode();
    MWBase::Environment::get().getInputManager()->changeInputMode(!gameMode);

    updateVisible();
}

void WindowManager::popGuiMode()
{
    if (mGuiModes.size())
        mGuiModes.pop_back();

    bool gameMode = !isGuiMode();
    MWBase::Environment::get().getInputManager()->changeInputMode(!gameMode);

    updateVisible();
}

void WindowManager::removeGuiMode(GuiMode mode)
{
    std::vector<GuiMode>::iterator it = mGuiModes.begin();
    while (it != mGuiModes.end())
    {
        if (*it == mode)
            it = mGuiModes.erase(it);
        else
            ++it;
    }

    updateVisible();
}

void WindowManager::setSelectedSpell(const std::string& spellId, int successChancePercent)
{
    hud->setSelectedSpell(spellId, successChancePercent);
    const ESM::Spell* spell = MWBase::Environment::get().getWorld()->getStore().spells.find(spellId);
    mSpellWindow->setTitle(spell->name);
}

void WindowManager::setSelectedEnchantItem(const MWWorld::Ptr& item, int chargePercent)
{
    hud->setSelectedEnchantItem(item, chargePercent);
    mSpellWindow->setTitle(MWWorld::Class::get(item).getName(item));
}

void WindowManager::setSelectedWeapon(const MWWorld::Ptr& item, int durabilityPercent)
{
    hud->setSelectedWeapon(item, durabilityPercent);
    mInventoryWindow->setTitle(MWWorld::Class::get(item).getName(item));
}

void WindowManager::unsetSelectedSpell()
{
    hud->unsetSelectedSpell();
    mSpellWindow->setTitle("#{sNone}");
}

void WindowManager::unsetSelectedWeapon()
{
    hud->unsetSelectedWeapon();
    mInventoryWindow->setTitle("#{sSkillHandtohand}");
}

void WindowManager::getMousePosition(int &x, int &y)
{
    const MyGUI::IntPoint& pos = MyGUI::InputManager::getInstance().getMousePosition();
    x = pos.left;
    y = pos.top;
}

void WindowManager::getMousePosition(float &x, float &y)
{
    const MyGUI::IntPoint& pos = MyGUI::InputManager::getInstance().getMousePosition();
    x = pos.left;
    y = pos.top;
    const MyGUI::IntSize& viewSize = MyGUI::RenderManager::getInstance().getViewSize();
    x /= viewSize.width;
    y /= viewSize.height;
}

bool WindowManager::getWorldMouseOver()
{
    return hud->getWorldMouseOver();
}
