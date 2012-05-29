#ifndef MWGUI_WINDOWMANAGER_H
#define MWGUI_WINDOWMANAGER_H

/**
   This class owns and controls all the MW specific windows in the
   GUI. It can enable/disable Gui mode, and is responsible for sending
   and retrieving information from the Gui.

   MyGUI should be initialized separately before creating instances of
   this class.
**/

#include <string>
#include <vector>
#include <set>

#include "MyGUI_UString.h"

#include <components/esm_store/store.hpp>
#include <components/settings/settings.hpp>
#include <openengine/ogre/renderer.hpp>
#include <openengine/gui/manager.hpp>

#include "../mwmechanics/stat.hpp"
#include "../mwworld/ptr.hpp"

#include "mode.hpp"

namespace MyGUI
{
  class Gui;
  class Widget;
}

namespace Compiler
{
    class Extensions;
}

namespace MWWorld
{
    class World;
}

namespace MWMechanics
{
    class MechanicsManager;
}

namespace OEngine
{
    namespace GUI
    {
        class Layout;
    }
}

namespace MWGui
{
  class WindowBase;
  class HUD;
  class MapWindow;
  class MainMenu;
  class StatsWindow;
  class InventoryWindow;
  class Console;
  class JournalWindow;
  class CharacterCreation;
  class ContainerWindow;
  class DragAndDrop;
  class InventoryWindow;
  class ToolTips;
  class ScrollWindow;
  class BookWindow;
  class TextInputDialog;
  class InfoBoxDialog;
  class DialogueWindow;
  class MessageBoxManager;
  class CountDialog;
  class TradeWindow;
  class SettingsWindow;
  class ConfirmationDialog;
  class AlchemyWindow;

  struct ClassPoint
  {
      const char *id;
      // Specialization points to match, in order: Stealth, Combat, Magic
      // Note: Order is taken from http://www.uesp.net/wiki/Morrowind:Class_Quiz
      unsigned int points[3];
  };

  class WindowManager
  {
  public:
    typedef std::pair<std::string, int> Faction;
    typedef std::vector<Faction> FactionList;
    typedef std::vector<int> SkillList;

    WindowManager(const Compiler::Extensions& extensions, int fpsLevel, bool newGame, OEngine::Render::OgreRenderer *mOgre, const std::string logpath);
    virtual ~WindowManager();

    /**
     * Should be called each frame to update windows/gui elements.
     * This could mean updating sizes of gui elements or opening
     * new dialogs.
     */
    void update();

    void pushGuiMode(GuiMode mode);
    void popGuiMode();
    void removeGuiMode(GuiMode mode); ///< can be anywhere in the stack

    GuiMode getMode() const
    {
        if (mGuiModes.empty())
            throw std::runtime_error ("getMode() called, but there is no active mode");
        return mGuiModes.back();
    }

    bool isGuiMode() const { return !mGuiModes.empty(); }

    void toggleVisible(GuiWindow wnd)
    {
        shown = (shown & wnd) ? (GuiWindow) (shown & ~wnd) : (GuiWindow) (shown | wnd);
        updateVisible();
    }

    // Disallow all inventory mode windows
    void disallowAll()
    {
      allowed = GW_None;
      updateVisible();
    }

    // Allow one or more windows
    void allow(GuiWindow wnd)
    {
      allowed = (GuiWindow)(allowed | wnd);
      updateVisible();
    }

    bool isAllowed(GuiWindow wnd)
    {
        return allowed & wnd;
    }

    MWGui::DialogueWindow* getDialogueWindow() {return mDialogueWindow;}
    MWGui::ContainerWindow* getContainerWindow() {return mContainerWindow;}
    MWGui::InventoryWindow* getInventoryWindow() {return mInventoryWindow;}
    MWGui::BookWindow* getBookWindow() {return mBookWindow;}
    MWGui::ScrollWindow* getScrollWindow() {return mScrollWindow;}
    MWGui::CountDialog* getCountDialog() {return mCountDialog;}
    MWGui::ConfirmationDialog* getConfirmationDialog() {return mConfirmationDialog;}
    MWGui::TradeWindow* getTradeWindow() {return mTradeWindow;}

    MyGUI::Gui* getGui() const { return gui; }

    void wmUpdateFps(float fps, size_t triangleCount, size_t batchCount)
    {
        mFPS = fps;
        mTriangleCount = triangleCount;
        mBatchCount = batchCount;
    }

//    MWMechanics::DynamicStat<int> getValue(const std::string& id);

    ///< Set value for the given ID.
    void setValue (const std::string& id, const MWMechanics::Stat<int>& value);
    void setValue(const ESM::Skill::SkillEnum parSkill, const MWMechanics::Stat<float>& value);
    void setValue (const std::string& id, const MWMechanics::DynamicStat<int>& value);
    void setValue (const std::string& id, const std::string& value);
    void setValue (const std::string& id, int value);

    void setPlayerClass (const ESM::Class &class_);                        ///< set current class of player
    void configureSkills (const SkillList& major, const SkillList& minor); ///< configure skill groups, each set contains the skill ID for that group.
    void setReputation (int reputation);                                   ///< set the current reputation value
    void setBounty (int bounty);                                           ///< set the current bounty value
    void updateSkillArea();                                                ///< update display of skills, factions, birth sign, reputation and bounty

    void changeCell(MWWorld::Ptr::CellStore* cell); ///< change the active cell
    void setPlayerPos(const float x, const float y); ///< set player position in map space
    void setPlayerDir(const float x, const float y); ///< set player view direction in map space

    void setFocusObject(const MWWorld::Ptr& focus);
    void setFocusObjectScreenCoords(float min_x, float min_y, float max_x, float max_y);

    void setMouseVisible(bool visible);
    void setDragDrop(bool dragDrop);

    void toggleFogOfWar();
    void toggleFullHelp(); ///< show extra info in item tooltips (owner, script)
    bool getFullHelp() const;

    void setInteriorMapTexture(const int x, const int y);
    ///< set the index of the map texture that should be used (for interiors)

    // sets the visibility of the hud health/magicka/stamina bars
    void setHMSVisibility(bool visible);
    // sets the visibility of the hud minimap
    void setMinimapVisibility(bool visible);
    void setWeaponVisibility(bool visible);
    void setSpellVisibility(bool visible);

    template<typename T>
    void removeDialog(T*& dialog); ///< Casts to OEngine::GUI::Layout and calls removeDialog, then resets pointer to nullptr.
    void removeDialog(OEngine::GUI::Layout* dialog); ///< Hides dialog and schedules dialog to be deleted.

    void messageBox (const std::string& message, const std::vector<std::string>& buttons);
    int readPressedButton (); ///< returns the index of the pressed button or -1 if no button was pressed (->MessageBoxmanager->InteractiveMessageBox)

    void onFrame (float frameDuration);

    std::map<ESM::Skill::SkillEnum, MWMechanics::Stat<float> > getPlayerSkillValues() { return playerSkillValues; }
    std::map<ESM::Attribute::AttributeID, MWMechanics::Stat<int> > getPlayerAttributeValues() { return playerAttributes; }
    SkillList getPlayerMinorSkills() { return playerMinorSkills; }
    SkillList getPlayerMajorSkills() { return playerMajorSkills; }

    /**
     * Fetches a GMST string from the store, if there is no setting with the given
     * ID or it is not a string the default string is returned.
     *
     * @param id Identifier for the GMST setting, e.g. "aName"
     * @param default Default value if the GMST setting cannot be used.
     */
    const std::string &getGameSettingString(const std::string &id, const std::string &default_);

    const ESMS::ESMStore& getStore() const;

    void processChangedSettings(const Settings::CategorySettingVector& changed);

  private:
    OEngine::GUI::MyGUIManager *mGuiManager;
    HUD *hud;
    MapWindow *map;
    MainMenu *menu;
    ToolTips *mToolTips;
    StatsWindow *mStatsWindow;
    MessageBoxManager *mMessageBoxManager;
    Console *console;
    JournalWindow* mJournal;
    DialogueWindow *mDialogueWindow;
    ContainerWindow *mContainerWindow;
    DragAndDrop* mDragAndDrop;
    InventoryWindow *mInventoryWindow;
    ScrollWindow* mScrollWindow;
    BookWindow* mBookWindow;
    CountDialog* mCountDialog;
    TradeWindow* mTradeWindow;
    SettingsWindow* mSettingsWindow;
    ConfirmationDialog* mConfirmationDialog;
    AlchemyWindow* mAlchemyWindow;

    CharacterCreation* mCharGen;

    // Various stats about player as needed by window manager
    ESM::Class playerClass;
    std::string playerName;
    std::string playerRaceId;
    std::map<ESM::Attribute::AttributeID, MWMechanics::Stat<int> > playerAttributes;
    SkillList playerMajorSkills, playerMinorSkills;
    std::map<ESM::Skill::SkillEnum, MWMechanics::Stat<float> > playerSkillValues;
    MWMechanics::DynamicStat<int> playerHealth, playerMagicka, playerFatigue;


    MyGUI::Gui *gui; // Gui
    std::vector<GuiMode> mGuiModes;

    std::vector<OEngine::GUI::Layout*> garbageDialogs;
    void cleanupGarbage();

    GuiWindow shown; // Currently shown windows in inventory mode

    /* Currently ALLOWED windows in inventory mode. This is used at
       the start of the game, when windows are enabled one by one
       through script commands. You can manipulate this through using
       allow() and disableAll().
     */
    GuiWindow allowed;

    void updateVisible(); // Update visibility of all windows based on mode, shown and allowed settings

    int showFPSLevel;
    float mFPS;
    size_t mTriangleCount;
    size_t mBatchCount;

    void onDialogueWindowBye();

    /**
     * Called when MyGUI tries to retrieve a tag. This usually corresponds to a GMST string,
     * so this method will retrieve the GMST with the name \a _tag and place the result in \a _result 
     */
    void onRetrieveTag(const MyGUI::UString& _tag, MyGUI::UString& _result);
  };

  template<typename T>
  void WindowManager::removeDialog(T*& dialog)
  {
      OEngine::GUI::Layout *d = static_cast<OEngine::GUI::Layout*>(dialog);
      removeDialog(d);
      dialog = 0;
  }
}

#endif
