#ifndef COMPONENTS_DEBUG_PERFOMANCETIMER_H
#define COMPONENTS_DEBUG_PERFOMANCETIMER_H

#include <string>

class PerfomanceTimerData;

/**
 * Useful to find most expensive part of function that performs several actions
 */
class PerfomanceTimer
{
public:
    PerfomanceTimer(const std::string &name);

    /**
     * Print to stderr time elapsed since previous call or timer creation.
     */
    void mark(const std::string &markName = "");

    /**
     * No message will be printed if elapsed time < minimal time.
     * Default value 1e-6
     */
    void setMinimalTime(double time) const;

private:
    PerfomanceTimerData *d;
};

#endif
