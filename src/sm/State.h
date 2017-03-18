//
// Created by Lewis on 2017/3/4.
//

#ifndef ELFBOX_STATE_H
#define ELFBOX_STATE_H

#include <common/IObject.h>
#include <common/Context.h>
#include <common/IObjectFactory.h>
#include <script/IScriptCenter.h>
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
    virtual void setOnEntry(const std::string& onEntryName)
    {
        onEntryFunc_ = onEntryName;
    }
    virtual void setOnUpdate(const std::string& onUpdateName)
    {
        onUpdateFunc_ = onUpdateName;
    }
    virtual void setOnExit(const std::string& onExitName)
    {
        onExitFunc_ = onExitName;
    }

    virtual const std::string& getStateName() const
    {
        return stateName_;
    }

    static common::IObjectPtr getFactory()
    {
        return std::make_shared<common::ObjectFactoryWrapper<State>>();
    }

    virtual void onEntry(void* sm);
    virtual void onUpdate(float timeStep, void* sm);
    virtual void onExit(void* sm);
private:
    void runScriptFunction(const std::string& action);

    common::ContextPtr context_;
    script::ScriptCenterPtr scriptCenter_;
    std::string stateName_;
    std::string onEntryFunc_;
    std::string onUpdateFunc_;
    std::string onExitFunc_;
};

}
}

#endif //ELFBOX_STATE_H
