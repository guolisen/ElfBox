//
// Created by Lewis on 2017/2/16.
//

#ifndef ELFBOX_ITIMESERVICE_H
#define ELFBOX_ITIMESERVICE_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace system
{
class ITimeService : public common::IObject
{
ELF_OBJECT(ITimeService, common::IObject);
public:
    virtual ~ITimeService() = default;

    virtual bool SetOption(const std::string& strKey, const void* pValue) = 0;
    virtual void Reset() = 0;
    virtual uint32_ GetMilliseconds() = 0;
    virtual uint32_ GetMicroseconds() = 0;
    virtual uint32_ GetMillisecondsCPU() = 0;
    virtual uint32_ GetMicrosecondsCPU() = 0;

    virtual void sleep(unsigned int tick) = 0;
};

typedef std::shared_ptr<ITimeService> TimeServicePtr;

}
}

#endif //ELFBOX_TIMESERVICE_H
