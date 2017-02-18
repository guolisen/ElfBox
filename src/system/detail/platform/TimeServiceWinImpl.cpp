//
// Created by Lewis on 2017/2/17.
//
#include <windows.h>
#include <algorithm>
#include "TimeServiceWinImpl.h"

namespace elfbox
{
namespace system
{
namespace detail
{

TimeServiceWinImpl::TimeServiceWinImpl(common::ContextPtr context) :
    context_(context)
{
}

bool TimeServiceWinImpl::initialize()
{

    return true;
}

bool TimeServiceWinImpl::SetOption(const std::string& strKey, const void* pValue)
{
    if ( strKey == "QueryAffinityMask" )
    {
        // Telling timer what core to use for a timer read
        DWORD newTimerMask = * static_cast < const DWORD * > ( pValue );

        // Get the current process core mask
        DWORD_PTR procMask;
        DWORD_PTR sysMask;
        GetProcessAffinityMask(GetCurrentProcess(), &procMask, &sysMask);

        // If new mask is 0, then set to default behavior, otherwise check
        // to make sure new timer core mask overlaps with process core mask
        // and that new timer core mask is a power of 2 (i.e. a single core)
        int tmp = (newTimerMask & (newTimerMask-1));
        if( ( newTimerMask == 0 ) ||
            ( ( ( newTimerMask & procMask ) != 0 ) && (tmp == 0) ) )
        {
            mTimerMask = newTimerMask;
            return true;
        }
    }

    return false;
}
/** Resets timer */
void TimeServiceWinImpl::Reset()
{
    // Get the current process core mask
    DWORD_PTR procMask;
    DWORD_PTR sysMask;
    GetProcessAffinityMask(GetCurrentProcess(), &procMask, &sysMask);

    // If procMask is 0, consider there is only one core available
    // (using 0 as procMask will cause an infinite loop below)
    if (procMask == 0)
        procMask = 1;

    // Find the lowest core that this process uses
    if( mTimerMask == 0 )
    {
        mTimerMask = 1;
        while( ( mTimerMask & procMask ) == 0 )
        {
            mTimerMask <<= 1;
        }
    }

    HANDLE thread = GetCurrentThread();

    // Set affinity to the first core
    DWORD_PTR oldMask = SetThreadAffinityMask(thread, mTimerMask);

    // Get the constant frequency
    QueryPerformanceFrequency(&mFrequency);

    // Query the timer
    QueryPerformanceCounter(&mStartTime);
    mStartTick = GetTickCount();

    // Reset affinity
    SetThreadAffinityMask(thread, oldMask);

    mLastTime = 0;
    mZeroClock = clock();
}
/** Returns milliseconds since initialisation or last reset */
uint32_ TimeServiceWinImpl::GetMilliseconds()
{
    LARGE_INTEGER curTime;

    HANDLE thread = GetCurrentThread();

    // Set affinity to the first core
    DWORD_PTR oldMask = SetThreadAffinityMask(thread, mTimerMask);

    // Query the timer
    QueryPerformanceCounter(&curTime);

    // Reset affinity
    SetThreadAffinityMask(thread, oldMask);

    LONGLONG newTime = curTime.QuadPart - mStartTime.QuadPart;

    // scale by 1000 for milliseconds
    unsigned long newTicks = (unsigned long) (1000 * newTime / mFrequency.QuadPart);

    // detect and compensate for performance counter leaps
    // (surprisingly common, see Microsoft KB: Q274323)
    unsigned long check = GetTickCount() - mStartTick;
    signed long msecOff = (signed long)(newTicks - check);
    if (msecOff < -100 || msecOff > 100)
    {
        // We must keep the timer running forward :)
        LONGLONG adjust = (std::min)(msecOff * mFrequency.QuadPart / 1000, newTime - mLastTime);
        mStartTime.QuadPart += adjust;
        newTime -= adjust;

        // Re-calculate milliseconds
        newTicks = (unsigned long) (1000 * newTime / mFrequency.QuadPart);
    }

    // Record last time for adjust
    mLastTime = newTime;

    return (uint32_)newTicks;
}
/** Returns microseconds since initialisation or last reset */
uint32_ TimeServiceWinImpl::GetMicroseconds()
{
    LARGE_INTEGER curTime;

    HANDLE thread = GetCurrentThread();

    // Set affinity to the first core
    DWORD_PTR oldMask = SetThreadAffinityMask(thread, mTimerMask);

    // Query the timer
    QueryPerformanceCounter(&curTime);

    // Reset affinity
    SetThreadAffinityMask(thread, oldMask);

    LONGLONG newTime = curTime.QuadPart - mStartTime.QuadPart;

    // get milliseconds to check against GetTickCount
    unsigned long newTicks = (unsigned long) (1000 * newTime / mFrequency.QuadPart);

    // detect and compensate for performance counter leaps
    // (surprisingly common, see Microsoft KB: Q274323)
    unsigned long check = GetTickCount() - mStartTick;
    signed long msecOff = (signed long)(newTicks - check);
    if (msecOff < -100 || msecOff > 100)
    {
        // We must keep the timer running forward :)
        LONGLONG adjust = (std::min)(msecOff * mFrequency.QuadPart / 1000, newTime - mLastTime);
        mStartTime.QuadPart += adjust;
        newTime -= adjust;
    }

    // Record last time for adjust
    mLastTime = newTime;

    // scale by 1000000 for microseconds
    unsigned long newMicro = (unsigned long) (1000000 * newTime / mFrequency.QuadPart);

    return (uint32_)newMicro;
}
/** Returns milliseconds since initialisation or last reset, only CPU time measured */
uint32_ TimeServiceWinImpl::GetMillisecondsCPU()
{
    clock_t newClock = clock();
    return (uint32_)((float)(newClock - mZeroClock) / ((float)CLOCKS_PER_SEC / 1000.0));
}
/** Returns microseconds since initialisation or last reset, only CPU time measured */
uint32_ TimeServiceWinImpl::GetMicrosecondsCPU()
{
    clock_t newClock = clock();
    return (uint32_)((float)(newClock - mZeroClock) / ((float)CLOCKS_PER_SEC / 1000000.0));
}

void TimeServiceWinImpl::sleep(unsigned int tick)
{
    ::Sleep(tick);
}

}
}
}