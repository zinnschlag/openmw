/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_SOUND_AUDIERE_DECODER_H
#define GAME_SOUND_AUDIERE_DECODER_H

#include <OgreDataStream.h>

#include "audiere.h"

#include "sound_decoder.hpp"


namespace MWSound
{
    class Audiere_Decoder : public Sound_Decoder
    {
        std::string mSoundFileName;
        audiere::FilePtr mSoundFile;
        audiere::SampleSourcePtr mSoundSource;
        int mSampleRate;
        SampleType mSampleType;
        ChannelConfig mChannelConfig;

        virtual void open(const std::string &fname);
        virtual void close();

        virtual std::string getName();
        virtual void getInfo(int *samplerate, ChannelConfig *chans, SampleType *type);

        virtual size_t read(char *buffer, size_t bytes);
        virtual void rewind();
        virtual size_t getSampleOffset();

        Audiere_Decoder& operator=(const Audiere_Decoder &rhs);
        Audiere_Decoder(const Audiere_Decoder &rhs);

        Audiere_Decoder();
    public:
        virtual ~Audiere_Decoder();

        friend class SoundManager;
    };
#ifndef DEFAULT_DECODER
#define DEFAULT_DECODER (::MWSound::Audiere_Decoder)
#endif
};

#endif
