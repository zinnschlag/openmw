/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWMECHANICS_ACTORS_H
#define GAME_MWMECHANICS_ACTORS_H

#include <set>
#include <vector>
#include <string>
#include <map>

namespace Ogre
{
    class Vector3;
}

namespace MWWorld
{
    class Ptr;
    class CellStore;
}

namespace MWMechanics
{
    class Actors
    {
            std::set<MWWorld::Ptr> mActors;
            float mDuration;
            std::map<std::string, int> mDeathCount;

            void updateNpc (const MWWorld::Ptr& ptr, float duration, bool paused);

            void adjustMagicEffects (const MWWorld::Ptr& creature);

            void calculateDynamicStats (const MWWorld::Ptr& ptr);

            void calculateCreatureStatModifiers (const MWWorld::Ptr& ptr);

            void calculateRestoration (const MWWorld::Ptr& ptr, float duration);


        public:

            Actors();

            void addActor (const MWWorld::Ptr& ptr);
            ///< Register an actor for stats management
            ///
            /// \note Dead actors are ignored.

            void removeActor (const MWWorld::Ptr& ptr);
            ///< Deregister an actor for stats management
            ///
            /// \note Ignored, if \a ptr is not a registered actor.

            void dropActors (const MWWorld::CellStore *cellStore);
            ///< Deregister all actors in the given cell.

            void update (std::vector<std::pair<std::string, Ogre::Vector3> >& movement,
                float duration, bool paused);
            ///< Update actor stats and store desired velocity vectors in \a movement

            void updateActor (const MWWorld::Ptr& ptr, float duration);
            ///< This function is normally called automatically during the update process, but it can
            /// also be called explicitly at any time to force an update.

            void restoreDynamicStats();
            ///< If the player is sleeping, this should be called every hour.
            
            int countDeaths (const std::string& id) const;
            ///< Return the number of deaths for actors with the given ID.
    };
}

#endif
