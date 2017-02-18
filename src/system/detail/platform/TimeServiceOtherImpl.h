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
    struct timeval start;
    clock_t zeroClock;
};
}
}
}
#endif //ELFBOX_TIMESERVICEIMPL_H
