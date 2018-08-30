//
// Created by Lewis on 2018/8/26.
//

#ifndef ELFBOX_IGAMEDIRECTOR_H
#define ELFBOX_IGAMEDIRECTOR_H

#include <memory>
#include <string>
#include <common/IObject.h>
#include <common/Context.h>
#include <gamelogic/IGameProcess.h>

namespace elfbox
{
namespace gamelogic
{
class IGameDirector : public common::IObject
{
ELF_OBJECT(IGameDirector, common::IObject);
public:
    virtual ~IGameDirector() = default;

    virtual bool initialize(const std::string& gameDescriptionFile) = 0;
    virtual void update(float timeStep) = 0;
    virtual void pauseProcess() = 0;
    virtual void resumeProcess() = 0;
    virtual int createProcessLine() = 0;
    virtual int attach(int processLineNum, GameProcessPtr process) = 0;
    virtual void detach(int processLineNum, int processId) = 0;


private:
    common::ContextPtr context_;
};

typedef std::shared_ptr<IGameDirector> GameDirectorPtr;

}
}

#endif //ELFBOX_IGAMEDIRECTOR_H
