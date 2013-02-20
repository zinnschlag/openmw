/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_SOUND_SOUND_H
#define GAME_SOUND_SOUND_H

#include <OgreVector3.h>

#include "soundmanagerimp.hpp"

namespace MWSound
{
    class Sound
    {
        virtual void update() = 0;

        Sound& operator=(const Sound &rhs);
        Sound(const Sound &rhs);

    protected:
        Ogre::Vector3 mPos;
        float mVolume; /* NOTE: Real volume = mVolume*mBaseVolume */
        float mBaseVolume;
        float mPitch;
        float mMinDistance;
        float mMaxDistance;
        int mFlags;

    public:
        virtual void stop() = 0;
        virtual bool isPlaying() = 0;
        virtual double getTimeOffset() = 0;
        void setPosition(const Ogre::Vector3 &pos) { mPos = pos; }
        void setVolume(float volume) { mVolume = volume; }

        MWBase::SoundManager::PlayType getPlayType() const
        { return (MWBase::SoundManager::PlayType)(mFlags&MWBase::SoundManager::Play_TypeMask); }


        Sound(const Ogre::Vector3& pos, float vol, float basevol, float pitch, float mindist, float maxdist, int flags)
          : mPos(pos)
          , mVolume(vol)
          , mBaseVolume(basevol)
          , mPitch(pitch)
          , mMinDistance(mindist)
          , mMaxDistance(maxdist)
          , mFlags(flags)
        { }
        virtual ~Sound() { }

        friend class OpenAL_Output;
        friend class SoundManager;
    };
}

#endif
