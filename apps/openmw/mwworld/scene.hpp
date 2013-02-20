/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWWORLD_SCENE_H
#define GAME_MWWORLD_SCENE_H

#include "../mwrender/renderingmanager.hpp"

#include "physicssystem.hpp"
#include "globals.hpp"

namespace Ogre
{
    class Vector3;
}

namespace ESM
{
    struct Position;
}

namespace Files
{
    class Collections;
}

namespace Render
{
    class OgreRenderer;
}

namespace MWRender
{
    class SkyManager;
    class CellRender;
}

namespace MWWorld
{
    class Player;
    class CellStore;
    class Ptr;

    class Scene
    {
        public:

            typedef std::set<CellStore *> CellStoreCollection;

        private:

            //OEngine::Render::OgreRenderer& mRenderer;
            CellStore* mCurrentCell; // the cell, the player is in
            CellStoreCollection mActiveCells;
            bool mCellChanged;
            PhysicsSystem *mPhysics;
            MWRender::RenderingManager& mRendering;

            void playerCellChange (CellStore *cell, const ESM::Position& position,
                bool adjustPlayerPos = true);


        public:

            Scene (MWRender::RenderingManager& rendering, PhysicsSystem *physics);

            ~Scene();

            void unloadCell (CellStoreCollection::iterator iter);

            void loadCell (CellStore *cell);

            void changeCell (int X, int Y, const ESM::Position& position, bool adjustPlayerPos);
            ///< Move from exterior to interior or from interior cell to a different
            /// interior cell.

            CellStore* getCurrentCell ();

            const CellStoreCollection& getActiveCells () const;

            bool hasCellChanged() const;
            ///< Has the player moved to a different cell, since the last frame?

            void changeToInteriorCell (const std::string& cellName, const ESM::Position& position);
            ///< Move to interior cell.

            void changeToExteriorCell (const ESM::Position& position);
            ///< Move to exterior cell.

            void markCellAsUnchanged();

            void insertCell (Ptr::CellStore &cell);

            void update (float duration, bool paused);

            void addObjectToScene (const Ptr& ptr);
            ///< Add an object that already exists in the world model to the scene.

            void removeObjectFromScene (const Ptr& ptr);
            ///< Remove an object from the scene, but not from the world model.

            bool isCellActive(const CellStore &cell);
    };
}

#endif
