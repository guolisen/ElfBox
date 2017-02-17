//
// Created by Lewis on 2017/2/17.
//

#ifndef ELFBOX_TIMESERVICEIMPL_H
#define ELFBOX_TIMESERVICEIMPL_H

#include <time.h>
#include <sys/time.h>
#include <common/IObject.h>
#include <common/Context.h>
#include "../../ITimeService.h"

namespace elfbox
{
namespace system
{
namespace detail
{

class TimeServiceOtherImpl : public ITimeService
{
ELF_OBJECT(TimeServiceOtherImpl, ITimeService);
public:
    TimeServiceOtherImpl(common::ContextPtr context);
    virtual ~TimeServiceOtherImpl() = default;

    virtual bool SetOption(const std::string& strKey, const void* pValue);
    virtual void Reset();
    virtual uint32_ GetMilliseconds();
    virtual uint32_ GetMicroseconds();
    virtual uint32_ GetMillisecondsCPU();
    virtual uint32_ GetMicrosecondsCPU();

private:
    common::ContextPtr context_;
    struct timeval start;
    clock_t zeroClock;
};
}
}
}
#endif //ELFBOX_TIMESERVICEIMPL_H
