//
// Created by Lewis on 2017/3/4.
//

#ifndef ELFBOX_STATEMACHINEIMPL_H
#define ELFBOX_STATEMACHINEIMPL_H

#include <map>
#include <vector>
#include <functional>
#include <common/IObject.h>
#include <common/Context.h>
#include <common/IObjectFactory.h>
#include <script/IScriptCenter.h>
#include "../IState.h"
#include "../StateEvent.h"
#include "../IStateMachine.h"

namespace elfbox
{
namespace sm
{
namespace detail
{
class StateMachineImpl : public IStateMachine
{
ELF_OBJECT(StateMachineImpl, IStateMachine);
public:
    StateMachineImpl(common::ContextPtr context);
    virtual ~StateMachineImpl() = default;

    virtual bool load(const std::string &fileName);
    virtual void addRow(const StateRow &stateRow);
    virtual bool prcessEvent(const StateEvent& event);
    virtual void update(float timeStep);

    virtual bool start();
    virtual void setInitialState(StatePtr state);

private:
    void runScriptFunction(const std::string& action);

    common::ContextPtr context_;
    common::ObjectFactoryPtr objectFactory_;
    script::ScriptCenterPtr scriptCenter_;
    std::vector<StateRow> stateTable_;
    std::map<std::string, StatePtr> stateMap_;
    StatePtr currentState_;
};
}
}
}
#endif //ELFBOX_STATEMACHINEIMPL_H
