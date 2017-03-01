//
// Created by Lewis on 2017/3/1.
//

#ifndef ELFBOX_ISYSTEMEVENTPROCESS_H
#define ELFBOX_ISYSTEMEVENTPROCESS_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace system
{
class ISystemEventProcess : public common::IObject
{
ELF_OBJECT(ISystemEventProcess, common::IObject);
public:
    virtual ~ISystemEventProcess() = default;
    virtual void run() = 0;
};

typedef std::shared_ptr<ISystemEventProcess> SystemEventProcessPtr;

}
}

#endif //ELFBOX_SYSTEMEVENTPROCESS_H
