/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COMPONENTS_FILES_CONSTRAINEDFILEDATASTREAM_HPP
#define COMPONENTS_FILES_CONSTRAINEDFILEDATASTREAM_HPP

#include <OgreDataStream.h>

Ogre::DataStreamPtr openConstrainedFileDataStream (char const * filename, size_t offset = 0, size_t length = 0xFFFFFFFF);

#endif // COMPONENTS_FILES_CONSTRAINEDFILEDATASTREAM_HPP
