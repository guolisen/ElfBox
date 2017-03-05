//
// Created by Lewis on 2017/3/4.
//

#ifndef ELFBOX_STATEMACHINE_H
#define ELFBOX_STATEMACHINE_H

#include <vector>
#include <functional>
#include <common/IObject.h>
#include <common/Context.h>
#include "IState.h"
#include "IStateEvent.h"
#include "IStateMachine.h"

namespace elfbox
{
namespace sm
{

class StateMachine : public IStateMachine
{
ELF_OBJECT(StateMachine, IStateMachine);
public:
    StateMachine(StateMachinePtr impl): impl_(impl) {}
    virtual ~StateMachine() = default;

    virtual bool load(const std::string& fileName)
    {
        return impl_->load(fileName);
    }

    virtual void addRow(const StateRow& stateRow)
    {
        return impl_->addRow(stateRow);
    }

    virtual bool prcessEvent(const StateEvent& event)
    {
        return impl_->prcessEvent(event);
    }

    virtual void update(float timeStep)
    {
        return impl_->update(timeStep);
    }

    virtual bool start()
    {
        return impl_->start();
    }

    virtual void setInitialState(StatePtr state)
    {
        return impl_->setInitialState(state);
    }

private:
    StateMachinePtr impl_;
};
}
}

#endif //ELFBOX_STATEMACHINE_H
