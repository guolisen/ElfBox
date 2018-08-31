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
        for (;!processLine.second.empty();)
        {
            auto process = processLine.second.begin();
            if ((*process)->getState() == ProcessStart)
                (*process)->setUp();
            if ((*process)->getState() == ProcessUpdate)
            {
                if (!(*process)->isActive())
                    break;
                (*process)->update(timeStep);
            }
            if ((*process)->getState() == ProcessFinish)
            {
                (*process)->tearDown();
                processLine.second.pop_front();
                continue;
            }
            break;
        }
    }
}

int GameDirector::createProcessLine()
{
    processQueue_.insert(std::make_pair(currentProcessNum_, std::list<GameProcessPtr>()));
    return currentProcessNum_++;
}

int GameDirector::attach(int processLineNum, GameProcessPtr process)
{
    //ProcessPause pp(this);
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