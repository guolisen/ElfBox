//
// Created by Lewis on 2017/2/23.
//

#include <system/ITimeService.h>
#include "ResourceWrapper.h"

namespace elfbox
{
namespace system
{
namespace detail
{
ResourceWrapper::ResourceWrapper(common::ContextPtr context,
                                 common::IObjectPtr resource) :
    context_(context), timeService_(
    context_->getComponent<ITimeService>(nullptr)), resource_(resource),
    startTick(timeService_->getMicroseconds()) {}

uint32_ ResourceWrapper::getElapsed()
{
    system::TimeServicePtr time =
        context_->getComponent<ITimeService>(nullptr);

    return time->getMicroseconds() - startTick;
}
}
}
}