//
// Created by Lewis on 2017/2/16.
//

#include "TimeService.h"

namespace elfbox
{
namespace system
{

TimeService::TimeService(std::shared_ptr<ITimeService> impl): impl_(impl)
{
}

bool TimeService::SetOption(const std::string& strKey, const void* pValue)
{
    return impl_->SetOption(strKey, pValue);
}

void TimeService::Reset()
{
    return impl_->Reset();
}

uint32_ TimeService::GetMilliseconds()
{
    return impl_->GetMilliseconds();
}

uint32_ TimeService::GetMicroseconds()
{
    return impl_->GetMicroseconds();
}

uint32_ TimeService::GetMillisecondsCPU()
{
    return impl_->GetMillisecondsCPU();
}

uint32_ TimeService::GetMicrosecondsCPU()
{
    return impl_->GetMicrosecondsCPU();
}
}
}