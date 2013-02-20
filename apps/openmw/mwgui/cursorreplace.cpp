/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "cursorreplace.hpp"

#include <boost/filesystem.hpp>
#include <openengine/ogre/imagerotate.hpp>

#include <OgreResourceGroupManager.h>
#include <OgreRoot.h>

using namespace MWGui;

CursorReplace::CursorReplace()
{
    OEngine::Render::ImageRotate::rotate("textures\\tx_cursormove.dds", "mwpointer_vresize.png", 90);
    OEngine::Render::ImageRotate::rotate("textures\\tx_cursormove.dds", "mwpointer_dresize1.png", -45);
    OEngine::Render::ImageRotate::rotate("textures\\tx_cursormove.dds", "mwpointer_dresize2.png", 45);
}
