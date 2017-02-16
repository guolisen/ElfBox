//
// Created by Lewis on 2017/2/14.
//
#include <windows.h>
#include <algorithm>
#include <system/IThreadPool.h>
#include "MessageBroadcaster.h"

namespace elfbox
{
namespace common
{
struct IsSubscribedExist
        : std::unary_function<SubscriptionMap::value_type const&, bool>
{
    explicit IsSubscribedExist(const MessageHandler& handler)
            : handler_(handler) {}

    bool operator()(const SubscriptionMap::value_type& arg) const
    {
        return arg.second.target<void(MessageData)>() ==
                handler_.target<void(MessageData)>();
    }

private:
    MessageHandler handler_;
};

struct CallHandler :
        std::unary_function<SubscriptionMap::value_type&, void>
{
    explicit CallHandler(MessageData data)
            : data_(data) {}

    void operator()(SubscriptionMap::value_type& arg) const
    {
        arg.second(data_);
    }

private:
    MessageData data_;
};

MessageBroadcaster::MessageBroadcaster(common::ContextPtr context):
        context_(context) {}

bool MessageBroadcaster::isAlreadySubscribed(const Subscription& subscription)
{
    std::lock_guard<std::recursive_mutex> hold(subscribersMutex_);
    if (subscribers_.empty())
        return false;
    auto range = subscribers_.equal_range(subscription.messageId);
    auto it = std::find_if(range.first, range.second,
        IsSubscribedExist(subscription.handler));
    return it != range.second ? true : false;
}

bool MessageBroadcaster::initialize()
{
    system::ThreadPoolPtr threadPool =
            context_->getComponent<system::IThreadPool>(nullptr);

    threadPool->attach(std::bind(&MessageBroadcaster::notifyMessage,
        this, std::placeholders::_1), -1);

    return true;
}

Subscription MessageBroadcaster::subscribe(MessageId id, MessageHandler handler)
{
    Subscription subscription(id, handler);
    {
        std::lock_guard<std::recursive_mutex> guard(subscribersMutex_);

        if (isAlreadySubscribed(subscription))
            return subscription;
        subscribers_.insert(std::make_pair(id, handler));
    }
    return Subscription(id, handler);
}

void MessageBroadcaster::unsubscribe(Subscription subHandler)
{
//TODO: will impl when use it...
}

void MessageBroadcaster::sendMessage(MessageId id, MessageData data)
{
    {
        std::lock_guard<std::mutex> guard(eventQueueMutex_);
        eventQueue_.push_back(std::make_shared<Event>(id, data));
    }
}

void MessageBroadcaster::notifyByMessageId(MessageId id, MessageData data)
{
    printf("notifyByMessageId %d\n", id);
    std::lock_guard<std::recursive_mutex> hold(subscribersMutex_);
    auto range = subscribers_.equal_range(id);
    std::for_each(range.first, range.second, CallHandler(data));
}

void MessageBroadcaster::notifyMessage(unsigned threadId)
{
    while (true)
    {
        EventPtr event = nullptr;
        {
            std::lock_guard<std::mutex> guard(eventQueueMutex_);
            if (eventQueue_.empty())
            {
                ::Sleep(1);
                continue;
            }
            printf("have message %d\n", eventQueue_.size());
            event = eventQueue_.front();
            eventQueue_.pop_front();
        }
        notifyByMessageId(event->messageId, event->data);
        ::Sleep(1);
    }
}

}
}