//
// Created by Lewis on 2017/2/16.
//

#include "TimeService.h"

namespace elfbox
{
namespace system
{

TimeService::TimeService(ThreadPoolPtr threadPool,
                         common::MessageBroadcasterPtr messageBroadcaster,
                         std::shared_ptr<ITimeService> impl):
    threadPool_(threadPool), messageBroadcaster_(messageBroadcaster),
    impl_(impl), timerCounter(0)
{
}

bool TimeService::setOption(const std::string &strKey, const void *pValue)
{
    std::lock_guard<std::mutex> guard(tickMutex_);
    return impl_->setOption(strKey, pValue);
}

void TimeService::reset()
{
    std::lock_guard<std::mutex> guard(tickMutex_);
    return impl_->reset();
}

uint32_ TimeService::getMilliseconds()
{
    std::lock_guard<std::mutex> guard(tickMutex_);
    return impl_->getMilliseconds();
}

uint32_ TimeService::getMicroseconds()
{
    std::lock_guard<std::mutex> guard(tickMutex_);
    return impl_->getMicroseconds();
}

uint32_ TimeService::getMillisecondsCPU()
{
    std::lock_guard<std::mutex> guard(tickMutex_);
    return impl_->getMillisecondsCPU();
}

uint32_ TimeService::getMicrosecondsCPU()
{
    std::lock_guard<std::mutex> guard(tickMutex_);
    return impl_->getMicrosecondsCPU();
}

void TimeService::sleep(unsigned int tick)
{
    return impl_->sleep(tick);
}

bool TimeService::initialize()
{
    reset();
    messageBroadcaster_->subscribe(
        common::TIMER_TIME_OUT, std::bind(&TimeService::timeOutHandler,
                                          this, std::placeholders::_1));
    threadPool_->attach(std::bind(&TimeService::timerLooper, this, std::placeholders::_1), -1);
    impl_->initialize();

    return true;
}

TimerId TimeService::createTimer(
    TimerHandler handler, int interval, bool isRepeat)
{
    TimerId id = getTimerId();
    TimerEntryPtr timer = std::make_shared<TimerEntry>(
        handler, interval * 1000, isRepeat);
    timer->startTick = getMicroseconds();
    timer->isEnable = true;
    {
        std::lock_guard<std::mutex> guard(timerMapMutex_);
        timerMap_.insert(std::make_pair(id, timer));
    }
    return id;
}

void TimeService::sendTimeOutMessage(TimerId id)
{
    printf("sendTimeOutMessage %d\n", id);
    common::MessageData data;
    data[EventTimerId] = id;
    messageBroadcaster_->sendMessage(common::TIMER_TIME_OUT, data);
}

void TimeService::timeOutHandler(common::MessageData data)
{
    TimerId id = data[EventTimerId];

    TimerHandler handler;
    {
        std::lock_guard<std::mutex> guard(timerMapMutex_);
        auto it = timerMap_.find(id);
        if (it == timerMap_.end())
            return;

        handler = it->second->handler;

        if (!it->second->isRepeat)
        {
            timerMap_.erase(it);
        }
        else
            it->second->isEnable = true;
    }

    handler(id);
}

void TimeService::timerLooper(unsigned threadId)
{
    while (true)
    {
        {
            std::lock_guard<std::mutex> guard(timerMapMutex_);
            if (timerMap_.empty())
            {
                sleep(100);
                continue;
            }
            //printf("have message %d\n", timerMap_.size());
            uint32_ currentTick = getMicroseconds();
            for(auto timerIt : timerMap_)
            {
                uint32_ diff = currentTick - timerIt.second->startTick;
                //printf("timeDiff %d\n", diff);
                if (diff > timerIt.second->interval)
                {
                    if (timerIt.second->isEnable)
                    {
                        sendTimeOutMessage(timerIt.first);
                        timerIt.second->isEnable = false;
                    }

                    if (timerIt.second->isRepeat)
                    {
                        timerIt.second->startTick = getMicroseconds();
                    }
                }
            }
        }

        sleep(1);
    }
}

}
}