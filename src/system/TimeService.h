//
// Created by Lewis on 2017/2/16.
//

#ifndef ELFBOX_TIMESERVICE_H
#define ELFBOX_TIMESERVICE_H

#include <map>
#include <mutex>
#include <atomic>
#include <common/IObject.h>
#include <common/Context.h>
#include <common/IMessageBroadcaster.h>
#include "IThreadPool.h"
#include "ITimeService.h"

namespace elfbox
{
namespace system
{

struct TimerEntry
{
    TimerHandler handler;
    uint32_ interval;
    bool isRepeat;
    uint32_ startTick;
    std::atomic<bool> isEnable;

    TimerEntry(TimerHandler timerHandler, int timerInterval, bool timerIsRepeat):
        handler(timerHandler), interval(timerInterval), isRepeat(timerIsRepeat),
        startTick(0), isEnable(false)
    {}
};

typedef std::shared_ptr<TimerEntry> TimerEntryPtr;
typedef std::map<TimerId, TimerEntryPtr> TimerMap;

const std::string EventTimerId = "TimerId";

class TimeService : public ITimeService
{
ELF_OBJECT(TimeService, ITimeService);
public:
    TimeService(ThreadPoolPtr threadPool,
        common::MessageBroadcasterPtr messageBroadcaster,
                system::TimeServicePtr impl);
    virtual ~TimeService() = default;

    virtual bool initialize();
    virtual bool setOption(const std::string &strKey, const void *pValue);
    virtual void reset();
    virtual uint32_ getMilliseconds();
    virtual uint32_ getMicroseconds();
    virtual uint32_ getMillisecondsCPU();
    virtual uint32_ getMicrosecondsCPU();

    virtual void sleep(unsigned int tick);
    virtual TimerId createTimer(TimerHandler handler, int interval, bool isRepeat);
    virtual void timerLooper(unsigned);

    void timeOutHandler(common::MessageData data);

private:
    void sendTimeOutMessage(TimerId id);
    TimerId getTimerId() { return timerCounter++; }

    std::mutex tickMutex_;
    ThreadPoolPtr threadPool_;
    common::MessageBroadcasterPtr messageBroadcaster_;
    system::TimeServicePtr impl_;
    std::mutex timerMapMutex_;
    TimerMap timerMap_;
    int timerCounter;
};

}
}

#endif //ELFBOX_TIMESERVICE_H
