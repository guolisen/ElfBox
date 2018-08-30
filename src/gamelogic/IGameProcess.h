//
// Created by Lewis on 2018/8/26.
//

#ifndef ELFBOX_IGAMEPROCESS_H
#define ELFBOX_IGAMEPROCESS_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace
{
class IGameProcess : public common::IObject
{
ELF_OBJECT(IGameProcess, common::IObject);
public:
    virtual ~IGameProcess() = default;
    virtual void update(float timeStep) = 0;
    virtual void kill() = 0;
    virtual bool isActive() const = 0;
    virtual bool isFinished() const = 0;
private:
    common::ContextPtr context_;
};

typedef std::shared_ptr<IGameProcess> GameProcessPtr;

}
}

#endif //ELFBOX_IGAMEPROCESS_H
