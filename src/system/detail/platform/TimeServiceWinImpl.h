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

    virtual bool initialize();
    virtual bool setOption(const std::string &strKey, const void *pValue);
    virtual void reset();
    virtual uint32_ getMilliseconds();
    virtual uint32_ getMicroseconds();
    virtual uint32_ getMillisecondsCPU();
    virtual uint32_ getMicrosecondsCPU();

    virtual void sleep(unsigned int tick);
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
