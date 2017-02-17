//
// Created by Lewis on 2017/2/17.
//

#ifndef ELFBOX_TIMESERVICEIMPL_H
#define ELFBOX_TIMESERVICEIMPL_H

#include <windows.h>
#include <time.h>
#include <common/IObject.h>
#include <common/Context.h>
#include "../../ITimeService.h"

namespace elfbox
{
namespace system
{
namespace detail
{

class TimeServiceWinImpl : public ITimeService
{
ELF_OBJECT(TimeServiceWinImpl, ITimeService);
public:
    TimeServiceWinImpl(common::ContextPtr context);
    virtual ~TimeServiceWinImpl() = default;

    virtual bool SetOption(const std::string& strKey, const void* pValue);
    virtual void Reset();
    virtual uint32_ GetMilliseconds();
    virtual uint32_ GetMicroseconds();
    virtual uint32_ GetMillisecondsCPU();
    virtual uint32_ GetMicrosecondsCPU();

private:
    common::ContextPtr context_;

    clock_t mZeroClock;
    DWORD mStartTick;
    LONGLONG mLastTime;
    LARGE_INTEGER mStartTime;
    LARGE_INTEGER mFrequency;

    DWORD_PTR mTimerMask;
};
}
}
}
#endif //ELFBOX_TIMESERVICEIMPL_H
