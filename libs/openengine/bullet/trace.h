#ifndef OENGINE_BULLET_TRACE_H
#define OENGINE_BULLET_TRACE_H

#include <OgreVector3.h>


class btCollisionObject;
class btCollisionShape;


namespace OEngine
{
namespace Physic
{
    class PhysicEngine;

    struct ActorTracer
    {
        Ogre::Vector3 mEndPos;
        Ogre::Vector3 mPlaneNormal;

        float mFraction;

        /// @param ignore collision object to ignore in the hit results (usually belongs to the actor we are tracing)
        /// @param shape use this shape instead of the actor's shape
        void doTrace(btCollisionObject *actor, btCollisionShape* shapeOverride, const Ogre::Vector3 &start, const Ogre::Vector3 &end,
                     const PhysicEngine *enginePass);
    };
}
}

#endif
