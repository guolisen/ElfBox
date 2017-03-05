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
    context_(context), stateName_("")
{
}

void State::onEntry()
{
    std::cout << "onEntry: " << stateName_ << std::endl;
}

void State::onExit()
{
    std::cout << "onExit: " << stateName_ << std::endl;
}
}
}