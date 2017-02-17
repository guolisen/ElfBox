//
// Created by Lewis on 2017/2/16.
//

#ifndef ELFBOX_TIMESERVICE_H
#define ELFBOX_TIMESERVICE_H

#include <common/IObject.h>
#include <common/Context.h>
#include "ITimeService.h"

namespace elfbox
{
namespace system
{

class TimeService : public ITimeService
{
ELF_OBJECT(TimeService, ITimeService);
public:
    TimeService(std::shared_ptr<ITimeService> impl);
    virtual ~TimeService() = default;

    virtual bool SetOption(const std::string& strKey, const void* pValue);
    virtual void Reset();
    virtual uint32_ GetMilliseconds();
    virtual uint32_ GetMicroseconds();
    virtual uint32_ GetMillisecondsCPU();
    virtual uint32_ GetMicrosecondsCPU();

    virtual void sleep(unsigned int tick);
private:
    std::shared_ptr<ITimeService> impl_;
};

}
}

#endif //ELFBOX_TIMESERVICE_H
