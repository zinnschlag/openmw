/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MWMECHANICS_AISEQUENCE_H
#define GAME_MWMECHANICS_AISEQUENCE_H

#include <list>

namespace MWWorld
{
    class Ptr;
}

namespace MWMechanics
{
    class AiPackage;
    
    /// \brief Sequence of AI-packages for a single actor
    class AiSequence
    {
            std::list<AiPackage *> mPackages;
            bool mDone;

            void copy (const AiSequence& sequence);

        public:
        
            AiSequence();
            
            AiSequence (const AiSequence& sequence);
            
            AiSequence& operator= (const AiSequence& sequence);
            
            virtual ~AiSequence();

            int getTypeId() const;
            ///< -1: None, 0: Wanter, 1 Travel, 2 Escort, 3 Follow, 4 Activate    
            
            bool isPackageDone() const;
            ///< Has a package been completed during the last update?
            
            void execute (const MWWorld::Ptr& actor);
            ///< Execute package.
            
            void clear();
            ///< Remove all packages.
            
            void stack (const AiPackage& package);
            ///< Add \a package to the front of the sequence (suspends current package)
            
            void queue (const AiPackage& package);
            ///< Add \a package to the end of the sequence (executed after all other packages have been
            /// completed)
    };
}

#endif
