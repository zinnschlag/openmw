/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _GAME_RENDER_ANIMATION_H
#define _GAME_RENDER_ANIMATION_H

#include <vector>

#include <components/nifogre/ogre_nif_loader.hpp>
#include <openengine/ogre/renderer.hpp>
#include "../mwworld/actiontalk.hpp"
#include <components/nif/node.hpp>
#include <openengine/bullet/physic.hpp>




namespace MWRender {

class Animation {
    struct GroupTimes {
        float mStart;
        float mStop;
        float mLoopStart;
        float mLoopStop;

        size_t mLoops;

        GroupTimes()
          : mStart(-1.0f), mStop(-1.0f), mLoopStart(-1.0f), mLoopStop(-1.0f),
            mLoops(0)
        { }
    };

protected:
    Ogre::SceneNode* mInsert;

    float mTime;
    GroupTimes mCurGroup;
    GroupTimes mNextGroup;

    bool mSkipFrame;

    NifOgre::EntityList mEntityList;
    NifOgre::TextKeyMap mTextKeys;

    bool findGroupTimes(const std::string &groupname, GroupTimes *times);

public:
    Animation();
    virtual ~Animation();

    void playGroup(std::string groupname, int mode, int loops);
    void skipAnim();
    virtual void runAnimation(float timepassed);
};

}
#endif
