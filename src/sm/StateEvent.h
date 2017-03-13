//
// Created by Lewis on 2017/3/4.
//

#ifndef ELFBOX_STATEEVENT_H
#define ELFBOX_STATEEVENT_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace sm
{
class StateEvent :  public common::IObject
{
ELF_OBJECT(StateEvent, common::IObject);
public:
    StateEvent():eventName_("") {}
    StateEvent(const std::string& eventName);
    virtual ~StateEvent() = default;

    virtual void setEventName(const std::string& eventName)
    {
        eventName_ = eventName;
    }

    virtual const std::string& getEventName() const
    {
        return eventName_;
    }


private:
    std::string eventName_;
};
}
}

#endif //ELFBOX_STATEEVENT_H
