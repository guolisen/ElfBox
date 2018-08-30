//
// Created by Lewis on 2018/8/26.
//

#include "GameDirector.h"

namespace elfbox
{
namespace gamelogic
{

class ProcessPause
{
public:
    ProcessPause(GameDirector* gameDirector) :
        gameDirector_(gameDirector)
    {
        gameDirector_->pauseProcess();
    }

    ~ProcessPause()
    {
        gameDirector_->resumeProcess();
    }

    GameDirector* gameDirector_;
};

GameDirector::GameDirector(common::ContextPtr context) : context_(context),
                                                         currentProcessNum_(0),
                                                         isPause_(false)
{
}

bool GameDirector::initialize(const std::string &gameDescriptionFile)
{
    return false;
}

void GameDirector::update(float timeStep)
{
    if (isPause_)
        return;
    for (auto processLine : processQueue_)
    {
        auto process = processLine.second.begin();
        for (;!processLine.second.empty();)
        {
            process = processLine.second.begin();
            if (!(*process)->isFinished())
                break;
            processLine.second.pop_front();
        }
        if (processLine.second.empty())
            continue;

        if (!(*process)->isActive())
           continue;

        (*process)->update(timeStep);
    }
}

int GameDirector::createProcessLine()
{
    processQueue_.insert(std::make_pair(currentProcessNum_, std::list<GameProcessPtr>()));
    return currentProcessNum_++;
}

int GameDirector::attach(int processLineNum, GameProcessPtr process)
{
    ProcessPause pp(this);
    auto iter = processQueue_.find(processLineNum);
    if (iter == processQueue_.end())
        return -1;

    iter->second.push_back(process);
    return 0;
}

void GameDirector::detach(int processLineNum, int processId)
{
    ProcessPause pp(this);
}


}
}