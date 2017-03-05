//
// Created by Lewis on 2017/3/4.
//

#ifndef ELFBOX_ISTATEEVENT_H
#define ELFBOX_ISTATEEVENT_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace sm
{
class IStateEvent : public common::IObject
{
ELF_OBJECT(IStateEvent, common::IObject);
public:
    virtual ~IStateEvent() = default;
    virtual void setEventName(const std::string& eventName) = 0;
    virtual const std::string& getEventName() const = 0;
};

typedef std::shared_ptr<IStateEvent> StateEventPtr;

}
}

#endif //ELFBOX_STATEEVENT_H
