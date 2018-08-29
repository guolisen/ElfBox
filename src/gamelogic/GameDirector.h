//
// Created by Lewis on 2018/8/26.
//

#ifndef ELFBOX_GAMEDIRECTOR_H
#define ELFBOX_GAMEDIRECTOR_H

#include <common/IObject.h>
#include <common/Context.h>
#include <gamelogic/IGameDirector.h>

namespace elfbox
{
namespace gamelogic
{
class GameDirector : public IGameDirector
{
ELF_OBJECT(GameDirector, IGameDirector);
public:
    explicit GameDirector(common::ContextPtr context);
    virtual ~GameDirector() = default;

    virtual bool initialize(const std::string& gameDescriptionFile) override;
    virtual bool update(float timeStep) override;

    virtual int attach(const IGameProcess& process) override;
    virtual void detach(int processId) override;

private:
    int currentProcessNum_;
    common::ContextPtr context_;
};
}
}

#endif //ELFBOX_GAMEDIRECTOR_H
