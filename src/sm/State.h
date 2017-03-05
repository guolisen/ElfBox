//
// Created by Lewis on 2017/3/4.
//

#ifndef ELFBOX_STATE_H
#define ELFBOX_STATE_H

#include <common/IObject.h>
#include <common/Context.h>
#include <common/IObjectFactory.h>
#include "IState.h"

namespace elfbox
{
namespace sm
{
class State : public IState
{
ELF_OBJECT(State, IState);
public:
    State(common::ContextPtr context);
    virtual ~State() = default;

    virtual void setStateName(const std::string& stateName)
    {
        stateName_ = stateName;
    }

    virtual const std::string& getStateName() const
    {
        return stateName_;
    }

    static common::IObjectPtr getFactory()
    {
        return std::make_shared<common::ObjectFactoryWrapper<State>>();
    }

    virtual void onEntry();
    virtual void onExit();
private:
    common::ContextPtr context_;
    std::string stateName_;
};

}
}

#endif //ELFBOX_STATE_H
