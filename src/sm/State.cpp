//
// Created by Lewis on 2017/3/4.
//
#include <iostream>
#include "State.h"

namespace elfbox
{
namespace sm
{

State::State(common::ContextPtr context) :
    context_(context),
    scriptCenter_(context_->getComponent<script::IScriptCenter>(nullptr)),
    stateName_("")
{
}

void State::onEntry(void* sm)
{
    //std::cout << stateName_ << " onEntry " << std::endl;
    elfbox::script::ScriptFunctionPtr func =
        scriptCenter_->getFunction(onEntryFunc_);
    if (func && func->beginCall())
    {
        func->pushUserType(sm, "IStateMachine");
        func->endCall();
        return;
    }

    printf("State::runScriptFunction() get action(%s) Error!", onEntryFunc_.c_str());

}

void State::onExit(void* sm)
{
    //std::cout << stateName_ << " onExit " << std::endl;
    elfbox::script::ScriptFunctionPtr func =
        scriptCenter_->getFunction(onExitFunc_);
    if (func && func->beginCall())
    {
        func->pushUserType(sm, "IStateMachine");
        func->endCall();
        return;
    }

    printf("State::runScriptFunction() get action(%s) Error!", onExitFunc_.c_str());
}

void State::runScriptFunction(const std::string &scriptFunc)
{
    elfbox::script::ScriptFunctionPtr func =
        scriptCenter_->getFunction(scriptFunc);
    if (func && func->beginCall())
    {
        func->endCall();
        return;
    }

    printf("State::runScriptFunction() get action(%s) Error!", scriptFunc.c_str());
}

void State::onUpdate(float timeStep, void* sm)
{
    //std::cout << stateName_ << " onUpdate " << std::endl;
    elfbox::script::ScriptFunctionPtr func =
        scriptCenter_->getFunction(onUpdateFunc_);
    if (func && func->beginCall())
    {
        func->pushUserType(sm, "IStateMachine");
        func->pushFloat(timeStep);
        func->endCall();
        return;
    }
}

}
}