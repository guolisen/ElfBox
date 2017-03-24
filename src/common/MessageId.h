//
// Created by Lewis on 2017/2/15.
//

#ifndef ELFBOX_MESSAGEID_H
#define ELFBOX_MESSAGEID_H

namespace elfbox
{
namespace common
{
//TODO: using XML to define the message ID
enum MessageId
{
    TEST_MESSAGE = 0,
    TIMER_TIME_OUT,
    SYSTEM_EVENT_KEYDOWN,
    SYSTEM_EVENT_KEYUP
};


}
}

#endif //ELFBOX_MESSAGEID_H
