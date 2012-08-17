#include "inputmanagerimp.hpp"

#include <OgreRoot.h>

#include <openengine/input/dispatcher.hpp>
#include <openengine/input/poller.hpp>

#include <openengine/gui/events.hpp>

#include <openengine/ogre/renderer.hpp>

#include "../mwbase/windowmanager.hpp"

#include <mangle/input/servers/ois_driver.hpp>
#include <mangle/input/filters/eventlist.hpp>

#include <libs/platform/strings.h>

#include "mouselookevent.hpp"

#include "../engine.hpp"

#include "../mwworld/player.hpp"
#include "../mwbase/world.hpp"

#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include <OgreRoot.h>
#include <OIS/OIS.h>

namespace MWInput
{
  enum Actions
    {
      A_Quit,           // Exit the program

      A_Screenshot,     // Take a screenshot

      A_Inventory,      // Toggle inventory screen

      A_Console,        // Toggle console screen

      A_MoveLeft,       // Move player left / right
      A_MoveRight,
      A_MoveForward,    // Forward / Backward
      A_MoveBackward,

      A_Activate,

      A_Use,        //Use weapon, spell, etc.
      A_Jump,
      A_AutoMove,   //Toggle Auto-move forward
      A_Rest,       //Rest
      A_Journal,    //Journal
      A_Weapon,     //Draw/Sheath weapon
      A_Spell,      //Ready/Unready Casting
      A_AlwaysRun,  //Toggle Always Run
      A_CycleSpellLeft, //cycling through spells
      A_CycleSpellRight,
      A_CycleWeaponLeft,//Cycling through weapons
      A_CycleWeaponRight,
      A_ToggleSneak,    //Toggles Sneak, add Push-Sneak later
      A_ToggleWalk, //Toggle Walking/Running
      A_Crouch,
      A_TogglePOV,

      A_QuickSave,
      A_QuickLoad,
      A_QuickMenu,
      A_GameMenu,
      A_ToggleWeapon,
      A_ToggleSpell,

      A_LAST            // Marker for the last item
    };

  // Class that handles all input and key bindings for OpenMW
  class InputImpl
  {
    OEngine::Input::DispatcherPtr disp;
    OEngine::Render::OgreRenderer &ogre;
    Mangle::Input::OISDriver input;
    OEngine::Input::Poller poller;
    MouseLookEventPtr mouse;
    OEngine::GUI::EventInjectorPtr guiEvents;
    MWWorld::Player &player;
    MWBase::WindowManager &windows;
    OMW::Engine& mEngine;

    bool mDragDrop;

    std::map<std::string, bool> mControlSwitch;

    float mPreviewPOVDelay;

   /* InputImpl Methods */
public:
    void adjustMouseRegion(int width, int height)
    {
        input.adjustMouseClippingSize(width, height);
    }
private:
    void toggleSpell()
    {
        if (windows.isGuiMode()) return;

        MWMechanics::DrawState_ state = player.getDrawState();
        if (state == MWMechanics::DrawState_Weapon || state == MWMechanics::DrawState_Nothing)
        {
            player.setDrawState(MWMechanics::DrawState_Spell);
            std::cout << "Player has now readied his hands for spellcasting!\n";
        }
        else
        {
            player.setDrawState(MWMechanics::DrawState_Nothing);
            std::cout << "Player does not have any kind of attack ready now.\n";
        }
    }

    void toggleWeapon()
    {
        if (windows.isGuiMode()) return;

        MWMechanics::DrawState_ state = player.getDrawState();
        if (state == MWMechanics::DrawState_Spell || state == MWMechanics::DrawState_Nothing)
        {
            player.setDrawState(MWMechanics::DrawState_Weapon);
            std::cout << "Player is now drawing his weapon.\n";
        }
        else
        {
            player.setDrawState(MWMechanics::DrawState_Nothing);
            std::cout << "Player does not have any kind of attack ready now.\n";
        }
    }

    void screenshot()
    {
        mEngine.screenshot();

        std::vector<std::string> empty;
        windows.messageBox ("Screenshot saved", empty);
    }

    /* toggleInventory() is called when the user presses the button to toggle the inventory screen. */
    void toggleInventory()
    {
        using namespace MWGui;

        if (mDragDrop)
            return;

        bool gameMode = !windows.isGuiMode();

        // Toggle between game mode and inventory mode
        if(gameMode)
            windows.pushGuiMode(GM_Inventory);
        else if(windows.getMode() == GM_Inventory)
            windows.popGuiMode();

        // .. but don't touch any other mode.
    }

    // Toggle console
    void toggleConsole()
    {
      using namespace MWGui;

      if (mDragDrop)
        return;

      bool gameMode = !windows.isGuiMode();

      // Switch to console mode no matter what mode we are currently
      // in, except of course if we are already in console mode
      if (!gameMode)
      {
          if (windows.getMode() == GM_Console)
              windows.popGuiMode();
          else
              windows.pushGuiMode(GM_Console);
      }
      else
          windows.pushGuiMode(GM_Console);
    }

    void toggleJournal()
    {
        using namespace MWGui;

        // Toggle between game mode and journal mode
        bool gameMode = !windows.isGuiMode();

        if(gameMode)
            windows.pushGuiMode(GM_Journal);
        else if(windows.getMode() == GM_Journal)
            windows.popGuiMode();
        // .. but don't touch any other mode.
    }

    void activate()
    {
        mEngine.activate();
    }

    void toggleAutoMove()
    {
        if (windows.isGuiMode()) return;
        player.setAutoMove (!player.getAutoMove());
    }

    void toggleWalking()
    {
        if (windows.isGuiMode()) return;
        player.toggleRunning();
    }

    void toggleMainMenu()
    {
        if (windows.isGuiMode () && (windows.getMode () == MWGui::GM_MainMenu || windows.getMode () == MWGui::GM_Settings))
            windows.popGuiMode();
        else
            windows.pushGuiMode (MWGui::GM_MainMenu);
    }

    // Exit program now button (which is disabled in GUI mode)
    void exitNow()
    {
        if(!windows.isGuiMode())
            Ogre::Root::getSingleton().queueEndRendering ();
    }

  public:
    InputImpl(OEngine::Render::OgreRenderer &_ogre,
                   MWWorld::Player &_player,
                   MWBase::WindowManager &_windows,
                   bool debug,
                   OMW::Engine& engine)
      : ogre(_ogre),
        input(ogre.getWindow(), !debug),
        poller(input),
        player(_player),
        windows(_windows),
        mEngine (engine),
        mDragDrop(false),
        mPreviewPOVDelay(0.f)
    {
      using namespace OEngine::Input;
      using namespace OEngine::Render;
      using namespace OEngine::GUI;
      using namespace Mangle::Input;
      using namespace OIS;

      disp = DispatcherPtr(new Dispatcher(A_LAST));

      // Bind MW-specific functions
      disp->funcs.bind(A_Quit, boost::bind(&InputImpl::exitNow, this),
                      "Quit program");
      disp->funcs.bind(A_Screenshot, boost::bind(&InputImpl::screenshot, this),
                      "Screenshot");
      disp->funcs.bind(A_Inventory, boost::bind(&InputImpl::toggleInventory, this),
                       "Toggle inventory screen");
      disp->funcs.bind(A_Console, boost::bind(&InputImpl::toggleConsole, this),
                       "Toggle console");
      disp->funcs.bind(A_Journal, boost::bind(&InputImpl::toggleJournal, this),
                       "Toggle journal");
      disp->funcs.bind(A_Activate, boost::bind(&InputImpl::activate, this),
                       "Activate");
      disp->funcs.bind(A_AutoMove, boost::bind(&InputImpl::toggleAutoMove, this),
                      "Auto Move");
      disp->funcs.bind(A_ToggleWalk, boost::bind(&InputImpl::toggleWalking, this),
                      "Toggle Walk/Run");
      disp->funcs.bind(A_ToggleWeapon,boost::bind(&InputImpl::toggleWeapon,this),
                      "Draw Weapon");
      disp->funcs.bind(A_ToggleSpell,boost::bind(&InputImpl::toggleSpell,this),
                      "Ready hands");
      disp->funcs.bind(A_GameMenu, boost::bind(&InputImpl::toggleMainMenu, this),
                      "Toggle main menu");

      mouse = MouseLookEventPtr(new MouseLookEvent());

      // This event handler pumps events into MyGUI
      guiEvents = EventInjectorPtr(new EventInjector(windows.getGui()));

      // Hook 'mouse' and 'disp' up as event handlers into 'input'
      // (the OIS driver and event source.) We do this through an
      // EventList which dispatches the event to multiple handlers for
      // us.
      {
        EventList *lst = new EventList;
        input.setEvent(EventPtr(lst));
        lst->add(mouse,Event::EV_MouseMove);
        lst->add(disp,Event::EV_KeyDown);
        lst->add(guiEvents,Event::EV_ALL);
      }

      mControlSwitch["playercontrols"]      = true;
      mControlSwitch["playerfighting"]      = true;
      mControlSwitch["playerjumping"]       = true;
      mControlSwitch["playerlooking"]       = true;
      mControlSwitch["playermagic"]         = true;
      mControlSwitch["playerviewswitch"]    = true;
      mControlSwitch["vanitymode"]          = true;

      changeInputMode(false);

      /**********************************
        Key binding section

        The rest of this function has hard coded key bindings, and is
        intended to be replaced by user defined bindings later.
       **********************************/

      // Key bindings for keypress events
      // NOTE: These keys do not require constant polling - use in conjuction with variables in loops.

      disp->bind(A_Quit, KC_Q);
      disp->bind(A_GameMenu, KC_ESCAPE);
      disp->bind(A_Screenshot, KC_SYSRQ);
      disp->bind(A_Inventory, KC_I);
      disp->bind(A_Console, KC_F1);
      disp->bind(A_Journal, KC_J);
      disp->bind(A_Activate, KC_SPACE);
      disp->bind(A_AutoMove, KC_Z);
      disp->bind(A_ToggleSneak, KC_X);
      disp->bind(A_ToggleWalk, KC_C);
      disp->bind(A_ToggleWeapon,KC_F);
      disp->bind(A_ToggleSpell,KC_R);

      // Key bindings for polled keys
      // NOTE: These keys are constantly being polled. Only add keys that must be checked each frame.

      // Arrow keys
      poller.bind(A_MoveLeft, KC_LEFT);
      poller.bind(A_MoveRight, KC_RIGHT);
      poller.bind(A_MoveForward, KC_UP);
      poller.bind(A_MoveBackward, KC_DOWN);

      // WASD keys
      poller.bind(A_MoveLeft, KC_A);
      poller.bind(A_MoveRight, KC_D);
      poller.bind(A_MoveForward, KC_W);
      poller.bind(A_MoveBackward, KC_S);

      poller.bind(A_Jump, KC_E);
      poller.bind(A_Crouch, KC_LCONTROL);

      poller.bind(A_TogglePOV, KC_TAB);
    }

    void setDragDrop(bool dragDrop)
    {
        mDragDrop = dragDrop;
    }

    //NOTE: Used to check for movement keys
    void update (float duration)
    {
        // Tell OIS to handle all input events
        input.capture();

        // Update windows/gui as a result of input events
        // For instance this could mean opening a new window/dialog,
        // by doing this after the input events are handled we
        // ensure that window/gui changes appear quickly while
        // avoiding that window/gui changes does not happen in
        // event callbacks (which may crash)
        windows.update();

        // Disable movement in Gui mode

        if (windows.isGuiMode()) return;

        // Configure player movement according to keyboard input. Actual movement will
        // be done in the physics system.
        if (mControlSwitch["playercontrols"]) {
            if (poller.isDown(A_MoveLeft))
            {
                player.setAutoMove (false);
                player.setLeftRight (1);
            }
            else if (poller.isDown(A_MoveRight))
            {
                player.setAutoMove (false);
                player.setLeftRight (-1);
            }
            else
                player.setLeftRight (0);

            if (poller.isDown(A_MoveForward))
            {
                player.setAutoMove (false);
                player.setForwardBackward (1);
            }
            else if (poller.isDown(A_MoveBackward))
            {
                player.setAutoMove (false);
                player.setForwardBackward (-1);
            }
            else
                player.setForwardBackward (0);

            if (poller.isDown(A_Jump) && mControlSwitch["playerjumping"])
                player.setUpDown (1);
            else if (poller.isDown(A_Crouch))
                player.setUpDown (-1);
            else
                player.setUpDown (0);

            if (mControlSwitch["playerviewswitch"]) {
                if (poller.isDown(A_TogglePOV)) {
                    if (mPreviewPOVDelay <= 0.5 &&
                        (mPreviewPOVDelay += duration) > 0.5)
                    {
                        mPreviewPOVDelay = 1.f;
                        MWBase::Environment::get().getWorld()->togglePreviewMode(true);
                    }
                } else {
                    if (mPreviewPOVDelay > 0.5) {
                        //disable preview mode
                        MWBase::Environment::get().getWorld()->togglePreviewMode(false);
                    } else if (mPreviewPOVDelay > 0.f) {
                        togglePOV();
                    }
                    mPreviewPOVDelay = 0.f;
                }
            }
        }
    }

    // Switch between gui modes. Besides controlling the Gui windows
    // this also makes sure input is directed to the right place
    void changeInputMode(bool guiMode)
    {
      // Are we in GUI mode now?
      if(guiMode)
        {
          // Disable mouse look
          mouse->disable();

          // Enable GUI events
          guiEvents->enabled = true;
        }
      else
        {
          mouse->enable();

          // Disable GUI events
          guiEvents->enabled = false;
        }
    }

    void toggleControlSwitch(const std::string &sw, bool value)
    {
        if (mControlSwitch[sw] == value) {
            return;
        }
        /// \note 7 switches at all, if-else is relevant
        if (sw == "playercontrols" && !value) {
            player.setLeftRight(0);
            player.setForwardBackward(0);
            player.setAutoMove(false);
            player.setUpDown(0);
        } else if (sw == "playerjumping" && !value) {
            /// \fixme maybe crouching at this time
            player.setUpDown(0);
        } else if (sw == "vanitymode") {
            MWBase::Environment::get().getWorld()->allowVanityMode(value);
        } else if (sw == "playerlooking") {
            MWBase::Environment::get().getWorld()->togglePlayerLooking(value);
        }
        mControlSwitch[sw] = value;
    }

    bool getControlSwitch(const std::string &sw)
    {
        return mControlSwitch[sw];
    }

    void togglePOV()
    {
        MWBase::Environment::get().getWorld()->togglePOV();
    }

  };

  /***CONSTRUCTOR***/
  MWInputManager::MWInputManager(OEngine::Render::OgreRenderer &ogre,
                                 MWWorld::Player &player,
                                 MWBase::WindowManager &windows,
                                 bool debug,
                                 OMW::Engine& engine)
  {
    impl = new InputImpl(ogre,player,windows,debug, engine);
  }

  /***DESTRUCTOR***/
  MWInputManager::~MWInputManager()
  {
    delete impl;
  }

  void MWInputManager::update(float duration)
  {
      impl->update(duration);
  }

  void MWInputManager::setDragDrop(bool dragDrop)
  {
      impl->setDragDrop(dragDrop);
  }

  void MWInputManager::changeInputMode(bool guiMode)
  {
      impl->changeInputMode(guiMode);
  }

  void MWInputManager::processChangedSettings(const Settings::CategorySettingVector& changed)
  {
      bool changeRes = false;
      for (Settings::CategorySettingVector::const_iterator it = changed.begin();
        it != changed.end(); ++it)
      {
          if (it->first == "Video" && (
            it->second == "resolution x"
            || it->second == "resolution y"))
                changeRes = true;
      }

      if (changeRes)
          impl->adjustMouseRegion(Settings::Manager::getInt("resolution x", "Video"), Settings::Manager::getInt("resolution y", "Video"));
  }

    void MWInputManager::toggleControlSwitch (const std::string& sw, bool value)
    {
        impl->toggleControlSwitch(sw, value);
    }

    bool MWInputManager::getControlSwitch(const std::string &sw)
    {
        return impl->getControlSwitch(sw);
    }
}
