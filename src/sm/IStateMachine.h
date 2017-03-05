//
// Created by Lewis on 2017/3/4.
//

#ifndef ELFBOX_ISTATEMACHINE_H
#define ELFBOX_ISTATEMACHINE_H

#include <common/IObject.h>
#include <common/Context.h>
#include "IState.h"
#include "IStateEvent.h"

namespace elfbox
{
namespace sm
{

typedef std::function<void(StateEventPtr)> ActionType;

struct StateRow
{
    StatePtr currentState;
    std::string transitionEvent;
    StatePtr nextState;

    std::string action;
    std::string guard;

    StateRow(StatePtr cState, const std::string& tEvent,
             StatePtr nState, const std::string& actionStr,
             const std::string& guardStr)
    {
        currentState = cState;
        transitionEvent = tEvent;
        nextState = nState;
        action = actionStr;
        guard = guardStr;
    }
};

class IStateMachine : public common::IObject
{
ELF_OBJECT(IStateMachine, common::IObject);
public:
    virtual ~IStateMachine() = default;

    virtual bool load(const std::string& fileName) = 0;
    virtual void addRow(const StateRow& stateRow) = 0;
    virtual bool prcessEvent(const StateEvent& event) = 0;
    virtual void update(float timeStep) = 0;

    virtual bool start() = 0;
    virtual void setInitialState(StatePtr state) = 0;
};

typedef std::shared_ptr<IStateMachine> StateMachinePtr;

}
}

#endif //ELFBOX_STATEMACHINE_H
