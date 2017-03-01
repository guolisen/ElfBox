//
// Created by Lewis on 2017/3/1.
//

#ifndef ELFBOX_SYSTEMEVENTPROCESSIMPL_H
#define ELFBOX_SYSTEMEVENTPROCESSIMPL_H

#include <SDL.h>
#include <common/IObject.h>
#include <common/Context.h>
#include <common/IMessageBroadcaster.h>
#include "../ISystemEventProcess.h"

namespace elfbox
{
namespace system
{
namespace detail
{

class SystemEventProcessImpl : public ISystemEventProcess
{
ELF_OBJECT(SystemEventProcessImpl, ISystemEventProcess);
public:
    SystemEventProcessImpl(common::ContextPtr context);
    virtual ~SystemEventProcessImpl() = default;

    void run();
private:
    void process(const SDL_Event* event);
    common::ContextPtr context_;
    common::MessageBroadcasterPtr messageBroadcaster_;
};
}
}
}

#endif //ELFBOX_SYSTEMEVENTPROCESSIMPL_H
