#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <vector>

#include <boost/thread.hpp>

#include "openal_output.hpp"
#include "sound_decoder.hpp"
#include "sound.hpp"
#include "soundmanager.hpp"

#ifndef ALC_ALL_DEVICES_SPECIFIER
#define ALC_ALL_DEVICES_SPECIFIER 0x1013
#endif


namespace MWSound
{

static void fail(const std::string &msg)
{ throw std::runtime_error("OpenAL exception: " + msg); }

static void throwALCerror(ALCdevice *device)
{
    ALCenum err = alcGetError(device);
    if(err != ALC_NO_ERROR)
        fail(alcGetString(device, err));
}

static void throwALerror()
{
    ALenum err = alGetError();
    if(err != AL_NO_ERROR)
        fail(alGetString(err));
}


static ALenum getALFormat(ChannelConfig chans, SampleType type)
{
    static const struct {
        ALenum format;
        ChannelConfig chans;
        SampleType type;
    } fmtlist[] = {
        { AL_FORMAT_MONO16,   ChannelConfig_Mono,   SampleType_Int16 },
        { AL_FORMAT_MONO8,    ChannelConfig_Mono,   SampleType_UInt8 },
        { AL_FORMAT_STEREO16, ChannelConfig_Stereo, SampleType_Int16 },
        { AL_FORMAT_STEREO8,  ChannelConfig_Stereo, SampleType_UInt8 },
    };
    static const size_t fmtlistsize = sizeof(fmtlist)/sizeof(fmtlist[0]);

    for(size_t i = 0;i < fmtlistsize;i++)
    {
        if(fmtlist[i].chans == chans && fmtlist[i].type == type)
            return fmtlist[i].format;
    }
    fail(std::string("Unsupported sound format (")+getChannelConfigName(chans)+", "+getSampleTypeName(type)+")");
    return AL_NONE;
}

//
// A streaming OpenAL sound.
//
class OpenAL_SoundStream : public Sound
{
    static const ALuint sNumBuffers = 6;
    static const ALfloat sBufferLength;

    OpenAL_Output &mOutput;

    ALuint mSource;
    ALuint mBuffers[sNumBuffers];

    ALenum mFormat;
    ALsizei mSampleRate;
    ALuint mBufferSize;

    DecoderPtr mDecoder;

    volatile bool mIsFinished;

    OpenAL_SoundStream(const OpenAL_SoundStream &rhs);
    OpenAL_SoundStream& operator=(const OpenAL_SoundStream &rhs);

public:
    OpenAL_SoundStream(OpenAL_Output &output, ALuint src, DecoderPtr decoder);
    virtual ~OpenAL_SoundStream();

    virtual void stop();
    virtual bool isPlaying();
    virtual void setVolume(float volume);
    virtual void update(const float *pos);

    void play();
    bool process();
};

const ALfloat OpenAL_SoundStream::sBufferLength = 0.125f;

//
// A background streaming thread (keeps active streams processed)
//
struct OpenAL_Output::StreamThread {
    typedef std::vector<OpenAL_SoundStream*> StreamVec;
    StreamVec mStreams;
    boost::mutex mMutex;
    boost::thread mThread;

    StreamThread()
      : mThread(boost::ref(*this))
    {
    }
    ~StreamThread()
    {
        mThread.interrupt();
    }

    // boost::thread entry point
    void operator()()
    {
        while(1)
        {
            mMutex.lock();
            StreamVec::iterator iter = mStreams.begin();
            while(iter != mStreams.end())
            {
                if((*iter)->process() == false)
                    iter = mStreams.erase(iter);
                else
                    iter++;
            }
            mMutex.unlock();
            boost::this_thread::sleep(boost::posix_time::milliseconds(50));
        }
    }

    void add(OpenAL_SoundStream *stream)
    {
        mMutex.lock();
        if(std::find(mStreams.begin(), mStreams.end(), stream) == mStreams.end())
            mStreams.push_back(stream);
        mMutex.unlock();
    }

    void remove(OpenAL_SoundStream *stream)
    {
        mMutex.lock();
        StreamVec::iterator iter = std::find(mStreams.begin(), mStreams.end(), stream);
        if(iter != mStreams.end())
            mStreams.erase(iter);
        mMutex.unlock();
    }

    void removeAll()
    {
        mMutex.lock();
        mStreams.clear();
        mMutex.unlock();
    }

private:
    StreamThread(const StreamThread &rhs);
    StreamThread& operator=(const StreamThread &rhs);
};


OpenAL_SoundStream::OpenAL_SoundStream(OpenAL_Output &output, ALuint src, DecoderPtr decoder)
  : mOutput(output), mSource(src), mDecoder(decoder), mIsFinished(true)
{
    throwALerror();

    alGenBuffers(sNumBuffers, mBuffers);
    throwALerror();
    try
    {
        int srate;
        ChannelConfig chans;
        SampleType type;

        mDecoder->getInfo(&srate, &chans, &type);
        mFormat = getALFormat(chans, type);
        mSampleRate = srate;

        mBufferSize = static_cast<ALuint>(sBufferLength*srate);
        mBufferSize = framesToBytes(mBufferSize, chans, type);
    }
    catch(std::exception &e)
    {
        mOutput.mFreeSources.push_back(mSource);
        alDeleteBuffers(sNumBuffers, mBuffers);
        alGetError();
        throw;
    }
}
OpenAL_SoundStream::~OpenAL_SoundStream()
{
    mOutput.mStreamThread->remove(this);

    alSourceStop(mSource);
    alSourcei(mSource, AL_BUFFER, 0);

    mOutput.mFreeSources.push_back(mSource);
    alDeleteBuffers(sNumBuffers, mBuffers);
    alGetError();

    mDecoder->close();
}

void OpenAL_SoundStream::play()
{
    std::vector<char> data(mBufferSize);

    alSourceStop(mSource);
    alSourcei(mSource, AL_BUFFER, 0);
    throwALerror();

    for(ALuint i = 0;i < sNumBuffers;i++)
    {
        size_t got;
        got = mDecoder->read(data.data(), data.size());
        alBufferData(mBuffers[i], mFormat, data.data(), got, mSampleRate);
    }
    throwALerror();

    alSourceQueueBuffers(mSource, sNumBuffers, mBuffers);
    alSourcePlay(mSource);
    throwALerror();

    mIsFinished = false;
    mOutput.mStreamThread->add(this);
}

void OpenAL_SoundStream::stop()
{
    mOutput.mStreamThread->remove(this);
    mIsFinished = true;

    alSourceStop(mSource);
    alSourcei(mSource, AL_BUFFER, 0);
    throwALerror();

    mDecoder->rewind();
}

bool OpenAL_SoundStream::isPlaying()
{
    ALint state;

    alGetSourcei(mSource, AL_SOURCE_STATE, &state);
    throwALerror();

    if(state == AL_PLAYING)
        return true;
    return !mIsFinished;
}

void OpenAL_SoundStream::setVolume(float volume)
{
    alSourcef(mSource, AL_GAIN, volume*mBaseVolume);
    throwALerror();
    mVolume = volume;
}

void OpenAL_SoundStream::update(const float *pos)
{
    alSource3f(mSource, AL_POSITION, pos[0], pos[2], -pos[1]);
    alSource3f(mSource, AL_DIRECTION, 0.0f, 0.0f, 0.0f);
    alSource3f(mSource, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    throwALerror();
}

bool OpenAL_SoundStream::process()
{
    bool finished = mIsFinished;
    ALint processed, state;

    alGetSourcei(mSource, AL_SOURCE_STATE, &state);
    alGetSourcei(mSource, AL_BUFFERS_PROCESSED, &processed);
    throwALerror();

    if(processed > 0)
    {
        std::vector<char> data(mBufferSize);
        do {
            ALuint bufid;
            size_t got;

            alSourceUnqueueBuffers(mSource, 1, &bufid);
            processed--;

            if(finished)
                continue;

            got = mDecoder->read(data.data(), data.size());
            finished = (got < data.size());
            if(got > 0)
            {
                alBufferData(bufid, mFormat, data.data(), got, mSampleRate);
                alSourceQueueBuffers(mSource, 1, &bufid);
            }
        } while(processed > 0);
        throwALerror();
    }

    if(state != AL_PLAYING && state != AL_PAUSED)
    {
        ALint queued;

        alGetSourcei(mSource, AL_BUFFERS_QUEUED, &queued);
        throwALerror();
        if(queued > 0)
        {
            alSourcePlay(mSource);
            throwALerror();
        }
    }

    mIsFinished = finished;
    return !finished;
}

//
// A regular OpenAL sound
//
class OpenAL_Sound : public Sound
{
    OpenAL_Output &mOutput;

    ALuint mSource;
    ALuint mBuffer;

    OpenAL_Sound(const OpenAL_Sound &rhs);
    OpenAL_Sound& operator=(const OpenAL_Sound &rhs);

public:
    OpenAL_Sound(OpenAL_Output &output, ALuint src, ALuint buf);
    virtual ~OpenAL_Sound();

    virtual void stop();
    virtual bool isPlaying();
    virtual void setVolume(float volume);
    virtual void update(const float *pos);
};

OpenAL_Sound::OpenAL_Sound(OpenAL_Output &output, ALuint src, ALuint buf)
  : mOutput(output), mSource(src), mBuffer(buf)
{
}
OpenAL_Sound::~OpenAL_Sound()
{
    alSourceStop(mSource);
    alSourcei(mSource, AL_BUFFER, 0);

    mOutput.mFreeSources.push_back(mSource);
    mOutput.bufferFinished(mBuffer);
}

void OpenAL_Sound::stop()
{
    alSourceStop(mSource);
    throwALerror();
}

bool OpenAL_Sound::isPlaying()
{
    ALint state;

    alGetSourcei(mSource, AL_SOURCE_STATE, &state);
    throwALerror();

    return state==AL_PLAYING;
}

void OpenAL_Sound::setVolume(float volume)
{
    alSourcef(mSource, AL_GAIN, volume*mBaseVolume);
    throwALerror();
    mVolume = volume;
}

void OpenAL_Sound::update(const float *pos)
{
    alSource3f(mSource, AL_POSITION, pos[0], pos[2], -pos[1]);
    alSource3f(mSource, AL_DIRECTION, 0.0f, 0.0f, 0.0f);
    alSource3f(mSource, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    throwALerror();
}


//
// An OpenAL output device
//
std::vector<std::string> OpenAL_Output::enumerate()
{
    std::vector<std::string> devlist;
    const ALCchar *devnames;

    if(alcIsExtensionPresent(NULL, "ALC_ENUMERATE_ALL_EXT"))
        devnames = alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER);
    else
        devnames = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
    while(devnames && *devnames)
    {
        devlist.push_back(devnames);
        devnames += strlen(devnames)+1;
    }
    return devlist;
}

void OpenAL_Output::init(const std::string &devname)
{
    if(mDevice || mContext)
        fail("Device already open");

    mDevice = alcOpenDevice(devname.c_str());
    if(!mDevice)
    {
        if(devname.empty())
            fail("Failed to open default device");
        else
            fail("Failed to open \""+devname+"\"");
    }
    if(alcIsExtensionPresent(mDevice, "ALC_ENUMERATE_ALL_EXT"))
        std::cout << "Opened \""<<alcGetString(mDevice, ALC_ALL_DEVICES_SPECIFIER)<<"\"" << std::endl;
    else
        std::cout << "Opened \""<<alcGetString(mDevice, ALC_DEVICE_SPECIFIER)<<"\"" << std::endl;

    mContext = alcCreateContext(mDevice, NULL);
    if(!mContext || alcMakeContextCurrent(mContext) == ALC_FALSE)
        fail(std::string("Failed to setup context: ")+alcGetString(mDevice, alcGetError(mDevice)));

    alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
    throwALerror();

    ALCint maxmono=0, maxstereo=0;
    alcGetIntegerv(mDevice, ALC_MONO_SOURCES, 1, &maxmono);
    alcGetIntegerv(mDevice, ALC_STEREO_SOURCES, 1, &maxstereo);
    throwALCerror(mDevice);

    try
    {
        ALCuint maxtotal = std::min<ALCuint>(maxmono+maxstereo, 256);
        for(size_t i = 0;i < maxtotal;i++)
        {
            ALuint src = 0;
            alGenSources(1, &src);
            throwALerror();
            mFreeSources.push_back(src);
        }
    }
    catch(std::exception &e)
    {
        std::cout <<"Error: "<<e.what()<<", trying to continue"<< std::endl;
    }
    if(mFreeSources.empty())
        fail("Could not allocate any sources");
}

void OpenAL_Output::deinit()
{
    mStreamThread->removeAll();

    while(!mFreeSources.empty())
    {
        alDeleteSources(1, &mFreeSources.front());
        mFreeSources.pop_front();
    }

    mBufferRefs.clear();
    mUnusedBuffers.clear();
    while(!mBufferCache.empty())
    {
        alDeleteBuffers(1, &mBufferCache.begin()->second);
        mBufferCache.erase(mBufferCache.begin());
    }

    alcMakeContextCurrent(0);
    if(mContext)
        alcDestroyContext(mContext);
    mContext = 0;
    if(mDevice)
        alcCloseDevice(mDevice);
    mDevice = 0;
}


ALuint OpenAL_Output::getBuffer(const std::string &fname)
{
    ALuint buf = 0;

    NameMap::iterator iditer = mBufferCache.find(fname);
    if(iditer != mBufferCache.end())
    {
        buf = iditer->second;
        if(mBufferRefs[buf]++ == 0)
        {
            IDDq::iterator iter = std::find(mUnusedBuffers.begin(),
                                            mUnusedBuffers.end(), buf);
            if(iter != mUnusedBuffers.end())
                mUnusedBuffers.erase(iter);
        }

        return buf;
    }
    throwALerror();

    std::vector<char> data;
    ChannelConfig chans;
    SampleType type;
    ALenum format;
    int srate;

    DecoderPtr decoder = mManager.getDecoder();
    try
    {
        decoder->open(fname);
    }
    catch(Ogre::FileNotFoundException &e)
    {
        std::string::size_type pos = fname.rfind('.');
        if(pos == std::string::npos)
            throw;
        decoder->open(fname.substr(0, pos)+".mp3");
    }

    decoder->getInfo(&srate, &chans, &type);
    format = getALFormat(chans, type);

    decoder->readAll(data);
    decoder->close();

    alGenBuffers(1, &buf);
    throwALerror();

    alBufferData(buf, format, data.data(), data.size(), srate);
    mBufferCache[fname] = buf;
    mBufferRefs[buf] = 1;

    ALint bufsize = 0;
    alGetBufferi(buf, AL_SIZE, &bufsize);
    mBufferCacheMemSize += bufsize;

    // NOTE: Max buffer cache: 15MB
    while(mBufferCacheMemSize > 15*1024*1024)
    {
        if(mUnusedBuffers.empty())
        {
            std::cout <<"No more unused buffers to clear!"<< std::endl;
            break;
        }

        ALuint oldbuf = mUnusedBuffers.front();
        mUnusedBuffers.pop_front();

        NameMap::iterator nameiter = mBufferCache.begin();
        while(nameiter != mBufferCache.end())
        {
            if(nameiter->second == oldbuf)
                mBufferCache.erase(nameiter++);
            else
                nameiter++;
        }

        bufsize = 0;
        alGetBufferi(oldbuf, AL_SIZE, &bufsize);
        alDeleteBuffers(1, &oldbuf);
        mBufferCacheMemSize -= bufsize;
    }
    return buf;
}

void OpenAL_Output::bufferFinished(ALuint buf)
{
    if(mBufferRefs.at(buf)-- == 1)
    {
        mBufferRefs.erase(mBufferRefs.find(buf));
        mUnusedBuffers.push_back(buf);
    }
}


SoundPtr OpenAL_Output::playSound(const std::string &fname, float volume, float pitch, bool loop)
{
    throwALerror();

    boost::shared_ptr<OpenAL_Sound> sound;
    ALuint src=0, buf=0;

    if(mFreeSources.empty())
        fail("No free sources");
    src = mFreeSources.front();
    mFreeSources.pop_front();

    try
    {
        buf = getBuffer(fname);
        sound.reset(new OpenAL_Sound(*this, src, buf));
    }
    catch(std::exception &e)
    {
        mFreeSources.push_back(src);
        if(buf && alIsBuffer(buf))
            bufferFinished(buf);
        alGetError();
        throw;
    }

    alSource3f(src, AL_POSITION, 0.0f, 0.0f, 0.0f);
    alSource3f(src, AL_DIRECTION, 0.0f, 0.0f, 0.0f);
    alSource3f(src, AL_VELOCITY, 0.0f, 0.0f, 0.0f);

    alSourcef(src, AL_REFERENCE_DISTANCE, 1.0f);
    alSourcef(src, AL_MAX_DISTANCE, 1000.0f);
    alSourcef(src, AL_ROLLOFF_FACTOR, 0.0f);

    alSourcef(src, AL_GAIN, volume);
    alSourcef(src, AL_PITCH, pitch);

    alSourcei(src, AL_SOURCE_RELATIVE, AL_TRUE);
    alSourcei(src, AL_LOOPING, (loop?AL_TRUE:AL_FALSE));
    throwALerror();

    alSourcei(src, AL_BUFFER, buf);
    alSourcePlay(src);
    throwALerror();

    return sound;
}

SoundPtr OpenAL_Output::playSound3D(const std::string &fname, const float *pos, float volume, float pitch,
                                    float min, float max, bool loop)
{
    throwALerror();

    boost::shared_ptr<OpenAL_Sound> sound;
    ALuint src=0, buf=0;

    if(mFreeSources.empty())
        fail("No free sources");
    src = mFreeSources.front();
    mFreeSources.pop_front();

    try
    {
        buf = getBuffer(fname);
        sound.reset(new OpenAL_Sound(*this, src, buf));
    }
    catch(std::exception &e)
    {
        mFreeSources.push_back(src);
        if(buf && alIsBuffer(buf))
            bufferFinished(buf);
        alGetError();
        throw;
    }

    alSource3f(src, AL_POSITION, pos[0], pos[2], -pos[1]);
    alSource3f(src, AL_DIRECTION, 0.0f, 0.0f, 0.0f);
    alSource3f(src, AL_VELOCITY, 0.0f, 0.0f, 0.0f);

    alSourcef(src, AL_REFERENCE_DISTANCE, min);
    alSourcef(src, AL_MAX_DISTANCE, max);
    alSourcef(src, AL_ROLLOFF_FACTOR, 1.0f);

    alSourcef(src, AL_GAIN, volume);
    alSourcef(src, AL_PITCH, pitch);

    alSourcei(src, AL_SOURCE_RELATIVE, AL_FALSE);
    alSourcei(src, AL_LOOPING, (loop?AL_TRUE:AL_FALSE));
    throwALerror();

    alSourcei(src, AL_BUFFER, buf);
    alSourcePlay(src);
    throwALerror();

    return sound;
}


SoundPtr OpenAL_Output::streamSound(const std::string &fname, float volume, float pitch)
{
    throwALerror();

    boost::shared_ptr<OpenAL_SoundStream> sound;
    ALuint src;

    if(mFreeSources.empty())
        fail("No free sources");
    src = mFreeSources.front();
    mFreeSources.pop_front();

    try
    {
        DecoderPtr decoder = mManager.getDecoder();
        decoder->open(fname);
        sound.reset(new OpenAL_SoundStream(*this, src, decoder));
    }
    catch(std::exception &e)
    {
        mFreeSources.push_back(src);
        throw;
    }

    alSource3f(src, AL_POSITION, 0.0f, 0.0f, 0.0f);
    alSource3f(src, AL_DIRECTION, 0.0f, 0.0f, 0.0f);
    alSource3f(src, AL_VELOCITY, 0.0f, 0.0f, 0.0f);

    alSourcef(src, AL_REFERENCE_DISTANCE, 1.0f);
    alSourcef(src, AL_MAX_DISTANCE, 1000.0f);
    alSourcef(src, AL_ROLLOFF_FACTOR, 0.0f);

    alSourcef(src, AL_GAIN, volume);
    alSourcef(src, AL_PITCH, pitch);

    alSourcei(src, AL_SOURCE_RELATIVE, AL_TRUE);
    alSourcei(src, AL_LOOPING, AL_FALSE);
    throwALerror();

    sound->play();
    return sound;
}

SoundPtr OpenAL_Output::streamSound3D(const std::string &fname, const float *pos, float volume, float pitch,
                                      float min, float max)
{
    throwALerror();

    boost::shared_ptr<OpenAL_SoundStream> sound;
    ALuint src;

    if(mFreeSources.empty())
        fail("No free sources");
    src = mFreeSources.front();
    mFreeSources.pop_front();

    try
    {
        DecoderPtr decoder = mManager.getDecoder();
        decoder->open(fname);
        sound.reset(new OpenAL_SoundStream(*this, src, decoder));
    }
    catch(std::exception &e)
    {
        mFreeSources.push_back(src);
        throw;
    }

    alSource3f(src, AL_POSITION, pos[0], pos[2], -pos[1]);
    alSource3f(src, AL_DIRECTION, 0.0f, 0.0f, 0.0f);
    alSource3f(src, AL_VELOCITY, 0.0f, 0.0f, 0.0f);

    alSourcef(src, AL_REFERENCE_DISTANCE, min);
    alSourcef(src, AL_MAX_DISTANCE, max);
    alSourcef(src, AL_ROLLOFF_FACTOR, 1.0f);

    alSourcef(src, AL_GAIN, volume);
    alSourcef(src, AL_PITCH, pitch);

    alSourcei(src, AL_SOURCE_RELATIVE, AL_FALSE);
    alSourcei(src, AL_LOOPING, AL_FALSE);
    throwALerror();

    sound->play();
    return sound;
}


void OpenAL_Output::updateListener(const float *pos, const float *atdir, const float *updir)
{
    float orient[6] = {
        atdir[0], atdir[2], -atdir[1],
        updir[0], updir[2], -updir[1]
    };

    alListener3f(AL_POSITION, pos[0], pos[2], -pos[1]);
    alListenerfv(AL_ORIENTATION, orient);
    throwALerror();
}


OpenAL_Output::OpenAL_Output(SoundManager &mgr)
  : Sound_Output(mgr), mDevice(0), mContext(0), mBufferCacheMemSize(0),
    mStreamThread(new StreamThread)
{
}

OpenAL_Output::~OpenAL_Output()
{
    deinit();
}

}
