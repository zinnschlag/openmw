/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _GAME_RENDER_ACTORS_H
#define _GAME_RENDER_ACTORS_H

#include "npcanimation.hpp"
#include "creatureanimation.hpp"

namespace MWWorld
{
    class Ptr;
    class CellStore;
}

namespace MWRender
{
    class Actors
    {
        typedef std::map<MWWorld::CellStore*,Ogre::SceneNode*> CellSceneNodeMap;
        typedef std::map<MWWorld::Ptr,Animation*> PtrAnimationMap;

        OEngine::Render::OgreRenderer &mRend;
        Ogre::SceneNode* mMwRoot;
        CellSceneNodeMap mCellSceneNodes;
        PtrAnimationMap mAllActors;

    public:
        Actors(OEngine::Render::OgreRenderer& _rend): mRend(_rend) {}
        ~Actors();

        void setMwRoot(Ogre::SceneNode* root);
        void insertBegin (const MWWorld::Ptr& ptr, bool enabled, bool static_);
        void insertCreature (const MWWorld::Ptr& ptr);
        void insertNPC(const MWWorld::Ptr& ptr, MWWorld::InventoryStore& inv);
         bool deleteObject (const MWWorld::Ptr& ptr);
        ///< \return found?

        void removeCell(MWWorld::CellStore* store);

        void playAnimationGroup (const MWWorld::Ptr& ptr, const std::string& groupName, int mode,
        int number = 1);
        ///< Run animation for a MW-reference. Calls to this function for references that are currently not
        /// in the rendered scene should be ignored.
        ///
        /// \param mode: 0 normal, 1 immediate start, 2 immediate loop
        /// \param number How offen the animation should be run

        void skipAnimation (const MWWorld::Ptr& ptr);
        ///< Skip the animation for the given MW-reference for one frame. Calls to this function for
        /// references that are currently not in the rendered scene should be ignored.

        void update (float duration);

        /// Updates containing cell for object rendering data
        void updateObjectCell(const MWWorld::Ptr &ptr);
    };
}
#endif
