//
// Created by Lewis on 2017/3/1.
//

#ifndef ELFBOX_SYSTEMEVENTPROCESS_H
#define ELFBOX_SYSTEMEVENTPROCESS_H

#include <common/IObject.h>
#include <common/Context.h>
#include "ISystemEventProcess.h"

namespace elfbox
{
namespace system
{
class SystemEventProcess : public ISystemEventProcess
{
ELF_OBJECT(SystemEventProcess, ISystemEventProcess);
public:
    SystemEventProcess(SystemEventProcessPtr impl): impl_(impl) {}
    virtual ~SystemEventProcess() = default;

    virtual void run()
    {
        impl_->run();
    }

private:
    SystemEventProcessPtr impl_;
};
}
}

#endif //ELFBOX_SYSTEMEVENTPROCESS_H
