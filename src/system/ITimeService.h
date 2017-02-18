//
// Created by Lewis on 2017/2/16.
//

#ifndef ELFBOX_ITIMESERVICE_H
#define ELFBOX_ITIMESERVICE_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace system
{

typedef uint32_ TimerId;
typedef std::function<void(TimerId)> TimerHandler;

class ITimeService : public common::IObject
{
ELF_OBJECT(ITimeService, common::IObject);
public:
    virtual ~ITimeService() = default;

    virtual bool initialize() = 0;
    virtual bool setOption(const std::string &strKey, const void *pValue) = 0;
    virtual void reset() = 0;
    virtual uint32_ getMilliseconds() = 0;
    virtual uint32_ getMicroseconds() = 0;
    virtual uint32_ getMillisecondsCPU() = 0;
    virtual uint32_ getMicrosecondsCPU() = 0;

    virtual void sleep(unsigned int tick) = 0;
    virtual TimerId createTimer(TimerHandler handler,
                                int interval, bool isRepeat) { return 0; };

};

typedef std::shared_ptr<ITimeService> TimeServicePtr;

}
}

#endif //ELFBOX_TIMESERVICE_H
