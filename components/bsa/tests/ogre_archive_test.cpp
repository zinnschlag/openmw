/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include <Ogre.h>
#include <iostream>

// This is a test of the BSA archive handler for OGRE.

#include "../bsa_archive.hpp"

using namespace Ogre;
using namespace std;

int main()
{
  // Disable Ogre logging
  new LogManager;
  Log *log = LogManager::getSingleton().createLog("");
  log->setDebugOutputEnabled(false);

  // Set up Root
  Root *root = new Root("","","");

  // Add the BSA
  Bsa::addBSA("../../data/Morrowind.bsa");

  // Pick a sample file
  String tex = "textures\\tx_natural_cavern_wall13.dds";
  cout << "Opening file: " << tex << endl;

  // Get it from the resource system
  DataStreamPtr data = ResourceGroupManager::getSingleton().openResource(tex, "General");

  cout << "Size: " << data->size() << endl;

  return 0;
}
