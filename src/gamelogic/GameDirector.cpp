//
// Created by Lewis on 2018/8/26.
//

#include "GameDirector.h"

namespace elfbox
{
namespace gamelogic
{

GameDirector::GameDirector(common::ContextPtr context) : context_(context)
{
}

bool GameDirector::initialize(const std::string &gameDescriptionFile)
{
    return false;
}

bool GameDirector::update(float timeStep)
{
    return false;
}

int GameDirector::attach(const IGameProcess &process)
{
    return 0;
}

void GameDirector::detach(int processId)
{
}
}
}