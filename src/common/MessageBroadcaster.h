//
// Created by Lewis on 2017/2/14.
//

#ifndef ELFBOX_MESSAGEBROADCASTER_H
#define ELFBOX_MESSAGEBROADCASTER_H

#include <unordered_map>
#include <list>
#include <mutex>
#include <common/IObject.h>
#include <common/Context.h>
#include <common/MessageId.h>
#include <common/detail/MessageVariant.h>
#include <common/IMessageBroadcaster.h>

namespace elfbox
{
namespace common
{

class MessageBroadcaster : public IMessageBroadcaster
{
ELF_OBJECT(MessageBroadcaster, IMessageBroadcaster);
public:
    MessageBroadcaster(common::ContextPtr context);
    virtual ~MessageBroadcaster() = default;

    virtual bool initialize();
    virtual Subscription subscribe(MessageId id, MessageHandler handler);
    virtual void unsubscribe(Subscription subHandler);

    virtual void sendMessage(MessageId id, detail::MessageData data);
    virtual void notifyMessage(unsigned threadId);

private:
    bool isAlreadySubscribed(const Subscription& subscription);
    void notifyByMessageId(MessageId id, detail::MessageData data);

    common::ContextPtr context_;
    std::recursive_mutex subscribersMutex_;
    SubscriptionMap subscribers_;
    std::mutex eventQueueMutex_;
    std::list<EventPtr> eventQueue_;
};

}
}


#if 0
void Test()
    {
        detail::MessageVariant var;
        var.setValue(12000);
        int ttt = var.getValue<int>();
        printf("dddddd %d\n", ttt);

        std::map<std::string, detail::MessageVariant> testMap;
        testMap.insert(std::make_pair("ttt", var));

        detail::MessageVariant var2;
        var2.setValue(11.222);
        float ttt2 = var2.getValue<float>();
        printf("dddddd %f\n", ttt2);
        testMap.insert(std::make_pair("ttt2", var2));

        detail::MessageVariant var3;
        var3 = 100;
        int ttt3 = var3.getValue<int>();
        printf("dddddd3 %d\n", ttt3);
        testMap.insert(std::make_pair("ttt3", var3));

        detail::MessageVariant var4 = 10234.2223;
        var4 = 10.211;
        float ttt4 = var4.getValue<float>();
        printf("dddddd4 %f\n", ttt4);
        testMap.insert(std::make_pair("ttt4", var4));

        int kkk = testMap["ttt"].getValue<int>();
        float kkk2 = testMap["ttt2"].getValue<float>();
        int kkk3 = testMap["ttt3"].getValue<int>();
        float kkk4 = testMap["ttt4"].getValue<float>();
        testMap["ttt5"] = 100;
        int kkk5 = testMap["ttt5"];
        std::string kkk6 = testMap["ttt6"];
        int kkk7 = testMap["ttt7"];
        printf("kkkkkkkkkk %d\n", kkk);
        printf("kkkkkkkkkk %f\n", kkk2);
        printf("kkkkkkkkkk %d\n", kkk3);
        printf("kkkkkkkkkk %f\n", kkk4);
        printf("kkkkkkkkkk %d\n", kkk5);
        printf("kkkkkkkkkk %s\n", kkk6.c_str());

        std::map<std::string, detail::MessageVariant> testMap2;
        testMap2 = std::move(testMap);

        printf("kkkkkkkkkk %d\n", kkk5);
    }
#endif

#endif //ELFBOX_MESSAGEBROADCASTER_H
