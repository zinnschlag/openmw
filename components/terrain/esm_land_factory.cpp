/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "esm_land_factory.hpp"

// The first one already includes the others implicitly, but it
// doesn't hurt to be explicit.
#include "../esm_store/store.hpp"
#include "../esm/esmreader.hpp"
#include "../esm/loadland.hpp"

using namespace Terrain;

bool ESMLandFactory::has(int x, int y)
{
  return store.landscapes.has(x,y);
}
