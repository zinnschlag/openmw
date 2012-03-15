#ifndef GAME_MWCLASS_APPARATUS_H
#define GAME_MWCLASS_APPARATUS_H

#include "../mwworld/class.hpp"

namespace MWClass
{
    class Apparatus : public MWWorld::Class
    {
        public:

            virtual void insertObjectRendering (const MWWorld::Ptr& ptr, MWRender::RenderingInterface& renderingInterface) const;
            ///< Add reference into a cell for rendering

            virtual void insertObject(const MWWorld::Ptr& ptr, MWWorld::PhysicsSystem& physics, MWWorld::Environment& environment) const;

            virtual std::string getName (const MWWorld::Ptr& ptr) const;
            ///< \return name (the one that is to be presented to the user; not the internal one);
            /// can return an empty string.

            virtual boost::shared_ptr<MWWorld::Action> activate (const MWWorld::Ptr& ptr,
                const MWWorld::Ptr& actor, const MWWorld::Environment& environment) const;
            ///< Generate action for activation

            virtual std::string getScript (const MWWorld::Ptr& ptr) const;
            ///< Return name of the script attached to ptr

            static void registerSelf();

            virtual std::string getUpSoundId (const MWWorld::Ptr& ptr) const;
            ///< Return the pick up sound Id

            virtual std::string getDownSoundId (const MWWorld::Ptr& ptr) const;
            ///< Return the put down sound Id
    };
}

#endif
