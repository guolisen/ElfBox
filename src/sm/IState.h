//
// Created by Lewis on 2017/3/4.
//

#ifndef ELFBOX_ISTATE_H
#define ELFBOX_ISTATE_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace sm
{
class IState : public common::IObject
{
ELF_OBJECT(IState, common::IObject);
public:
    virtual ~IState() = default;
    virtual void setStateName(const std::string& stateName) = 0;
    virtual void setOnEntry(const std::string& onEntryName) = 0;
    virtual void setOnUpdate(const std::string& onEntryName) = 0;
    virtual void setOnExit(const std::string& onExitName) = 0;
    virtual const std::string& getStateName() const = 0;

    virtual void onEntry() = 0;
    virtual void onUpdate() = 0;
    virtual void onExit() = 0;
};

typedef std::shared_ptr<IState> StatePtr;

}
}

#endif //ELFBOX_STATE_H
