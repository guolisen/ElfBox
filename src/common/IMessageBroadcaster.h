//
// Created by Lewis on 2017/2/14.
//

#ifndef ELFBOX_IMESSAGEBROADCASTER_H
#define ELFBOX_IMESSAGEBROADCASTER_H

#include <unordered_map>
#include <list>
#include <mutex>
#include <common/IObject.h>
#include <common/Context.h>
#include <common/MessageId.h>
#include <common/detail/MessageVariant.h>

namespace elfbox
{
namespace common
{

typedef std::function<void(detail::MessageData)> MessageHandler;
typedef std::unordered_map<int, MessageHandler> SubscriptionMap;

struct Subscription
{
    MessageId messageId;
    MessageHandler handler;

    Subscription(MessageId id, MessageHandler messageHandler):
            messageId(id), handler(messageHandler) {}
};
typedef std::shared_ptr<Subscription> SubscriptionPtr;

struct Event
{
    MessageId messageId;
    detail::MessageData data;

    Event(MessageId id, detail::MessageData data):
            messageId(id), data(std::move(data)) {}
};
typedef std::shared_ptr<Event> EventPtr;

class IMessageBroadcaster : public common::IObject
{
ELF_OBJECT(IMessageBroadcaster, common::IObject);
public:
    virtual ~IMessageBroadcaster() = default;

    virtual bool initialize() = 0;
    virtual Subscription subscribe(MessageId id, MessageHandler handler) = 0;
    virtual void unsubscribe(Subscription subHandler) = 0;

    virtual void sendMessage(MessageId id, detail::MessageData data) = 0;
    virtual void notifyMessage(unsigned threadId) = 0;
};

typedef std::shared_ptr<IMessageBroadcaster> MessageBroadcasterPtr;

}
}

#endif //ELFBOX_IMESSAGEBROADCASTER_H
