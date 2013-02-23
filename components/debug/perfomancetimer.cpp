#include "perfomancetimer.hpp"
#include <iostream>

#include <time.h>
#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __MACH__
#include <sys/time.h>
#endif

class PerfomanceTimerData
{
public:
#ifdef _WIN32
    LARGE_INTEGER mStartTime;
#else
    timespec mStartTime;
#endif
    std::string mName;
    int mMarkNo;
    double mMinimalTime;
    double mFrequency; ///< clocks frequency
};

namespace {

#ifdef _WIN32
    double getClocksFrequency()
    {
        LARGE_INTEGER freq;
        QueryPerformanceFrequency(&freq);
        return freq.QuadPart;
    }

    LARGE_INTEGER getCurrentTime()
    {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        return li;
    }

    double updateCurrentTime(LARGE_INTEGER &ts, double frequency)
    {
        LARGE_INTEGER current = getCurrentTime();
        const double delta = current.QuadPart - ts.QuadPart;
        ts = current;
        return delta / frequency;
    }

#else
    double getClocksFrequency()
    {
        return 1.0;
    }

#ifdef __MACH__
    timespec getCurrentTime()
    {
        timespec ts;
        timeval tv;
        gettimeofday(&tv, NULL);
        ts.tv_sec = now.tv_sec;
        ts.tv_nsec = now.tv_usec * 1000;
        return ts;
    }
#else
    timespec getCurrentTime()
    {
        timespec ts;
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
        return ts;
    }
#endif

    /// Updates timespec and returns elapsed time
    double updateCurrentTime(timespec &ts, double frequency)
    {
        (void)frequency;
        timespec current = getCurrentTime();
        timespec delta;
        delta.tv_sec = current.tv_sec - ts.tv_sec;
        delta.tv_nsec = current.tv_nsec - ts.tv_nsec;
        ts = current;

        if (delta.tv_nsec < 0) {
            delta.tv_sec -= 1;
            delta.tv_nsec += 1000 * 1000 * 1000;
        }
        return delta.tv_sec * 1e-9 * delta.tv_nsec;
    }
#endif
}

PerfomanceTimer::PerfomanceTimer(const std::string &name)
    : d(new PerfomanceTimerData())
{
    d->mFrequency = getClocksFrequency();
    d->mStartTime = getCurrentTime();
    d->mName = name;
    d->mMinimalTime = 1e-6;
    d->mMarkNo = 0;
}

void PerfomanceTimer::mark(const std::string &markName)
{
    const double elapsed = updateCurrentTime(d->mStartTime, d->mFrequency);
    ++d->mMarkNo;
    if (elapsed < d->mMinimalTime)
        return;

    std::cerr << "@timer " << d->mName;
    if (markName.empty())
        std::cerr << "(no. " << d->mMarkNo << ")";
    else
        std::cerr << "(" << markName << ")";

    const int oldPrecision = std::cerr.precision();
    std::cerr.precision(6);
    std::cerr.setf(std::ios::fixed, std::ios::floatfield);
    std::cerr << " elapsed: " << elapsed << "s.";
    std::cerr.unsetf(std::ios::fixed);
    std::cerr.precision(oldPrecision);

    std::cerr << std::endl;
}

void PerfomanceTimer::setMinimalTime(double time) const
{
    d->mMinimalTime = time;
}

