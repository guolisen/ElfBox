//
// Created by Lewis on 2017/3/1.
//

#include "SystemEventProcessImpl.h"

namespace elfbox
{
namespace system
{
namespace detail
{

SystemEventProcessImpl::SystemEventProcessImpl(common::ContextPtr context) : context_(context), messageBroadcaster_(
    context_->getComponent<common::IMessageBroadcaster>(nullptr))
{
}

void SystemEventProcessImpl::run()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        process(&event);
    }
}

void SystemEventProcessImpl::process(const SDL_Event* event)
{
    if (event->type == SDL_QUIT)
    {
        //OnExit();
    }
    else if (event->type == SDL_KEYDOWN)
    {
        common::MessageData data;
        data["KEY"] = event->key.keysym.sym;
        messageBroadcaster_->sendMessage(common::SYSTEM_EVENT_KEYDOWN, data);
    }
    else if (event->type == SDL_KEYUP)
    {
        common::MessageData data;
        data["KEY"] = event->key.keysym.sym;
        messageBroadcaster_->sendMessage(common::SYSTEM_EVENT_KEYUP, data);
    }

}
}
}
}