//
// Created by Lewis on 2017/2/17.
//
#include <unistd.h>
#include "TimeServiceOtherImpl.h"

namespace elfbox
{
namespace system
{
namespace detail
{

TimeServiceOtherImpl::TimeServiceOtherImpl(common::ContextPtr context) : context_(context)
{
    reset();
}

bool TimeServiceOtherImpl::initialize()
{
    return true;
}

bool TimeServiceOtherImpl::setOption(const std::string &strKey, const void *pValue)
{
    return true;
}

void TimeServiceOtherImpl::reset()
{
    zeroClock = clock();
    gettimeofday(&start, NULL);
}

uint32_ TimeServiceOtherImpl::getMilliseconds()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_sec-start.tv_sec)*1000+(now.tv_usec-start.tv_usec)/1000;
}

uint32_ TimeServiceOtherImpl::getMicroseconds()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_sec-start.tv_sec)*1000000+(now.tv_usec-start.tv_usec);

}

uint32_ TimeServiceOtherImpl::getMillisecondsCPU()
{
    clock_t newClock = clock();
    return (unsigned long)((float)(newClock-zeroClock) / ((float)CLOCKS_PER_SEC/1000.0)) ;
}

uint32_ TimeServiceOtherImpl::getMicrosecondsCPU()
{
    clock_t newClock = clock();
    return (unsigned long)((float)(newClock-zeroClock) / ((float)CLOCKS_PER_SEC/1000000.0)) ;
}

void TimeServiceOtherImpl::sleep(unsigned int tick)
{
    ::sleep(tick/1000);
}
}
}
}