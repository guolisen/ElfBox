//
// Created by Lewis on 2017/2/17.
//

#ifndef ELFBOX_ITIMESERVICEIMPL_H
#define ELFBOX_ITIMESERVICEIMPL_H

#include <common/IObject.h>
#include <common/Context.h>
#include "../ITimeService.h"

#ifdef _WIN32
#include "platform/TimeServiceWinImpl.h"
#else
#include "platform/TimeServiceOtherImpl.h"
#endif

namespace elfbox
{
namespace system
{
namespace detail
{

#ifdef _WIN32
typedef TimeServiceWinImpl TimeServiceImpl;
#else
typedef TimeServiceOtherImpl TimeServiceImpl;
#endif

}
}
}
#endif //ELFBOX_TIMESERVICEIMPL_H
