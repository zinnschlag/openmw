/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MWGUI_MODE_H
#define MWGUI_MODE_H

namespace MWGui
{
  enum GuiMode
    {
      GM_Settings,      // Settings window
      GM_Inventory,     // Inventory mode
      GM_Container,
      GM_MainMenu,      // Main menu mode

      GM_Console,       // Console mode
      GM_Journal,       // Journal mode

      GM_Scroll,        // Read scroll
      GM_Book,          // Read book
      GM_Alchemy,       // Make potions

      GM_Dialogue,      // NPC interaction
      GM_Barter,
      GM_Rest,
      GM_RestBed,
      GM_SpellBuying,
      GM_Travel,
      GM_SpellCreation,
      GM_Enchanting,
      GM_Training,

      GM_Levelup,

      // Startup character creation dialogs
      GM_Name,
      GM_Race,
      GM_Birth,
      GM_Class,
      GM_ClassGenerate,
      GM_ClassPick,
      GM_ClassCreate,
      GM_Review,
      
      // interactive MessageBox
      GM_InterMessageBox,

      GM_Loading,
      GM_LoadingWallpaper,

      GM_QuickKeysMenu,

      GM_Video
    };

  // Windows shown in inventory mode
  enum GuiWindow
    {
      GW_None           = 0,

      GW_Map            = 0x01,
      GW_Inventory      = 0x02,
      GW_Magic          = 0x04,
      GW_Stats          = 0x08,

      GW_ALL            = 0xFF
    };
}

#endif
