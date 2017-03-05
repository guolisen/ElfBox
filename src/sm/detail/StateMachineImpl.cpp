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
    objectFactory_(context_->getComponent<common::IObjectFactory>(nullptr))
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
            row.currentState->onExit();
            //row.action(e);
            std::cout << "State: " << currentState_->getStateName() << " " << row.action << std::endl;
            row.nextState->onEntry();
            currentState_ = row.nextState;
        }
    }

    return true;
}

void StateMachineImpl::update(float timeStep)
{
}

bool StateMachineImpl::load(const std::string &fileName)
{
    tinyxml2::XMLDocument stateMachineXml;
    auto ret = stateMachineXml.LoadFile(fileName.c_str());
    if (ret)
    {
        //ELFBOX_LOGERROR(context_["ILogger"], "State Machine read xml error: %d", ret);
        return false;
    }

    tinyxml2::XMLElement* root = stateMachineXml.RootElement();
    tinyxml2::XMLElement* state = root->FirstChildElement("state");
    while (state)
    {
        const tinyxml2::XMLAttribute* stateNameAttribute = state->FirstAttribute();
        StatePtr stateObject = objectFactory_->createObject<IState>(context_);

        std::string stateName = stateNameAttribute->Value();
        stateObject->setStateName(stateName);
        stateMap_.insert(std::make_pair(stateName, stateObject));

        const tinyxml2::XMLAttribute* initTag = stateNameAttribute->Next();
        if (initTag && std::string(initTag->Name()) == "InitialState")
        {
            currentState_ = stateObject;
        }

        state = state->NextSiblingElement();
    }

    tinyxml2::XMLElement* stateRow = root->NextSiblingElement();
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

    currentState_->onEntry();
    return true;
}

void StateMachineImpl::setInitialState(StatePtr state)
{
    currentState_ = state;
}

}
}
}