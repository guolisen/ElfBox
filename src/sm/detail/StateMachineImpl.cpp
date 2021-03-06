//
// Created by Lewis on 2017/3/4.
//
#include <iostream>
#include <tinyxml2.h>
#include "StateMachineImpl.h"
#include <util/BaseLogger.h>

namespace elfbox
{
namespace sm
{
namespace detail
{

StateMachineImpl::StateMachineImpl(common::ContextPtr context) :
    context_(context),
    objectFactory_(context_->getComponent<common::IObjectFactory>(nullptr)),
    scriptCenter_(context_->getComponent<script::IScriptCenter>(nullptr))
{
}

void StateMachineImpl::addRow(const StateRow &stateRow)
{
    stateTable_.push_back(stateRow);
}

bool StateMachineImpl::prcessEvent(const StateEvent& event)
{
    for (auto& row : stateTable_)
    {
        if ((row.currentState == currentState_) &&
            (row.transitionEvent == event.getEventName()))
        {
            row.currentState->onExit((void*)this);
            std::cout << "State: " << currentState_->getStateName() << " " << row.action << std::endl;
            runScriptFunction(row.action);
            currentState_ = row.nextState;
            row.nextState->onEntry((void*)this);
        }
    }

    return true;
}

void StateMachineImpl::update(float timeStep)
{
    if (!currentState_)
        return;

    currentState_->onUpdate(timeStep, (void*)this);
}

bool StateMachineImpl::load(const std::string &fileName)
{
    //TODO: empty pointer check
    tinyxml2::XMLDocument stateMachineXml;
    auto ret = stateMachineXml.LoadFile(fileName.c_str());
    if (ret)
    {
        //ELFBOX_LOGERROR(context_["ILogger"], "State Machine read xml error: %d", ret);
        return false;
    }

    tinyxml2::XMLElement* root = stateMachineXml.RootElement();

    const tinyxml2::XMLAttribute* scriptFile = root->FirstAttribute();
    if (scriptFile)
    {
        scriptCenter_->execute(scriptFile->Value());
    }

    tinyxml2::XMLElement* sm = root->FirstChildElement("stateSet");
    tinyxml2::XMLElement* state = sm->FirstChildElement("state");
    while (state)
    {
        const tinyxml2::XMLAttribute* stateNameAttribute = state->FirstAttribute();
        StatePtr stateObject = objectFactory_->createObject<IState>(context_);

        std::string stateName = stateNameAttribute->Value();
        stateObject->setStateName(stateName);

        const tinyxml2::XMLAttribute* initTag = stateNameAttribute->Next();
        if (initTag && std::string(initTag->Name()) == "InitialState")
        {
            currentState_ = stateObject;
        }

        tinyxml2::XMLElement* onOnEntryMethod = state->FirstChildElement("onEntry");
        if (onOnEntryMethod)
        {
            stateObject->setOnEntry(onOnEntryMethod->GetText());
        }
        tinyxml2::XMLElement* nextXml = onOnEntryMethod ? onOnEntryMethod : state;
        tinyxml2::XMLElement* onOnUpdateMethod = nextXml->NextSiblingElement("onUpdate");
        if (onOnUpdateMethod)
        {
            stateObject->setOnUpdate(onOnUpdateMethod->GetText());
        }
        nextXml = onOnUpdateMethod ? onOnUpdateMethod : onOnEntryMethod;
        tinyxml2::XMLElement* onOnExitMethod = nextXml->NextSiblingElement("onExit");
        if (onOnExitMethod)
        {
            stateObject->setOnExit(onOnExitMethod->GetText());
        }

        stateMap_.insert(std::make_pair(stateName, stateObject));
        state = state->NextSiblingElement();
    }

    tinyxml2::XMLElement* stateRow = sm->NextSiblingElement();
    tinyxml2::XMLElement* row = stateRow->FirstChildElement("row");
    while (row)
    {
        const tinyxml2::XMLAttribute* currentState = row->FirstAttribute();
        StatePtr currentStateObject = stateMap_[currentState->Value()];
        if (!currentStateObject)
            return false;

        const tinyxml2::XMLAttribute* stateEvent = currentState->Next();
        std::string transitionEvent = stateEvent->Value();

        const tinyxml2::XMLAttribute* nextState = stateEvent->Next();
        StatePtr nextStateObject = stateMap_[nextState->Value()];
        if (!nextStateObject)
            return false;

        const tinyxml2::XMLAttribute* action = nextState->Next();
        std::string actionString = action->Value();

        const tinyxml2::XMLAttribute* guard = action->Next();
        std::string guardString = guard->Value();

        stateTable_.emplace_back(StateRow(currentStateObject, transitionEvent,
                                       nextStateObject, actionString, guardString));

        row = row->NextSiblingElement();
    }

    return true;
}

bool StateMachineImpl::start()
{
    if (!currentState_)
        return false;

    currentState_->onEntry((void*)this);
    return true;
}

void StateMachineImpl::setInitialState(StatePtr state)
{
    currentState_ = state;
}

void StateMachineImpl::runScriptFunction(const std::string &action)
{
    elfbox::script::ScriptFunctionPtr actionFunc = scriptCenter_->getFunction(action);
    if (actionFunc && actionFunc->beginCall())
    {
        actionFunc->endCall();
        return;
    }

    printf("StateMachine get action(%s) Error!", action.c_str());
}

}
}
}