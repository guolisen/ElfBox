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

void State::onEntry()
{
    //std::cout << stateName_ << " onEntry " << std::endl;
    runScriptFunction(onEntryFunc_);
}

void State::onExit()
{
    //std::cout << stateName_ << " onExit " << std::endl;
    runScriptFunction(onExitFunc_);
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

void State::onUpdate()
{
    //std::cout << stateName_ << " onUpdate " << std::endl;
    runScriptFunction(onUpdateFunc_);
}

}
}