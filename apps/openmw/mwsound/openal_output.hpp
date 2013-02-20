/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_SOUND_OPENAL_OUTPUT_H
#define GAME_SOUND_OPENAL_OUTPUT_H

#include <string>
#include <vector>
#include <map>
#include <deque>

#include "alc.h"
#include "al.h"

#include "sound_output.hpp"

namespace MWSound
{
    class SoundManager;
    class Sound;

    class OpenAL_Output : public Sound_Output
    {
        ALCdevice *mDevice;
        ALCcontext *mContext;

        typedef std::deque<ALuint> IDDq;
        IDDq mFreeSources;
        IDDq mUnusedBuffers;

        typedef std::map<std::string,ALuint> NameMap;
        NameMap mBufferCache;

        typedef std::map<ALuint,ALuint> IDRefMap;
        IDRefMap mBufferRefs;

        uint64_t mBufferCacheMemSize;

        typedef std::vector<Sound*> SoundVec;
        SoundVec mActiveSounds;

        ALuint getBuffer(const std::string &fname);
        void bufferFinished(ALuint buffer);

        Environment mLastEnvironment;

        virtual std::vector<std::string> enumerate();
        virtual void init(const std::string &devname="");
        virtual void deinit();

        virtual MWBase::SoundPtr playSound(const std::string &fname, float vol, float basevol, float pitch, int flags);
        virtual MWBase::SoundPtr playSound3D(const std::string &fname, const Ogre::Vector3 &pos,
                                             float vol, float basevol, float pitch, float min, float max, int flags);
        virtual MWBase::SoundPtr streamSound(DecoderPtr decoder, float volume, float pitch, int flags);

        virtual void updateListener(const Ogre::Vector3 &pos, const Ogre::Vector3 &atdir, const Ogre::Vector3 &updir, Environment env);

        virtual void pauseSounds(int types);
        virtual void resumeSounds(int types);

        OpenAL_Output& operator=(const OpenAL_Output &rhs);
        OpenAL_Output(const OpenAL_Output &rhs);

        OpenAL_Output(SoundManager &mgr);
        virtual ~OpenAL_Output();

        class StreamThread;
        std::auto_ptr<StreamThread> mStreamThread;

        friend class OpenAL_Sound;
        friend class OpenAL_Sound3D;
        friend class OpenAL_SoundStream;
        friend class SoundManager;
    };
#ifndef DEFAULT_OUTPUT
#define DEFAULT_OUTPUT(x) ::MWSound::OpenAL_Output((x))
#endif
}

#endif
