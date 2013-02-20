/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _GAME_RENDERING_INTERFACE_H
#define _GAME_RENDERING_INTERFACE_H

namespace MWRender
{
    class Objects;
    class Actors;
      
    class RenderingInterface
    {
    public:
        virtual MWRender::Objects& getObjects() = 0;
        virtual MWRender::Actors& getActors() = 0;
        virtual ~RenderingInterface(){};
    };
}
#endif
