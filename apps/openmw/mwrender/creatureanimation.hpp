/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _GAME_RENDER_CREATUREANIMATION_H
#define _GAME_RENDER_CREATUREANIMATION_H

#include "animation.hpp"

#include "components/nifogre/ogre_nif_loader.hpp"


namespace MWRender{

    class CreatureAnimation: public Animation
    {
    public:
        virtual ~CreatureAnimation();
        CreatureAnimation(const MWWorld::Ptr& ptr);
        virtual void runAnimation(float timepassed);

    };
}
#endif
