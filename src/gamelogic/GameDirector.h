//
// Created by Lewis on 2018/8/26.
//

#ifndef ELFBOX_GAMEDIRECTOR_H
#define ELFBOX_GAMEDIRECTOR_H

#include <map>
#include <list>
#include <common/IObject.h>
#include <common/Context.h>
#include <gamelogic/IGameDirector.h>

namespace elfbox
{
namespace gamelogic
{

typedef std::map<int, std::list<GameProcessPtr>> ProcessQueue;

class GameDirector : public IGameDirector
{
ELF_OBJECT(GameDirector, IGameDirector);
public:
    explicit GameDirector(common::ContextPtr context);
    virtual ~GameDirector() = default;

    virtual bool initialize(const std::string& gameDescriptionFile) override;
    virtual void update(float timeStep) override;

    virtual void resumeProcess() { isPause_ = false; }
    virtual void pauseProcess() { isPause_ = true; }
    virtual int createProcessLine();
    virtual int attach(int processLineNum, GameProcessPtr process) override;
    virtual void detach(int processLineNum, int processId) override;

private:
    common::ContextPtr context_;
    int currentProcessNum_;
    ProcessQueue processQueue_;
    bool isPause_;
};
}
}

#endif //ELFBOX_GAMEDIRECTOR_H
