//
// Created by Lewis on 2017/3/15.
//

#ifndef ELFBOX_SMCOMPONENT_H
#define ELFBOX_SMCOMPONENT_H

#include <common/IObject.h>
#include <common/Context.h>
#include "../INodeComponent.h"

namespace elfbox
{
namespace scene
{
namespace component
{
class ScriptComponent : public common::IObject
{
ELF_OBJECT(ScriptComponent, INodeComponent);
public:
    ScriptComponent(common::ContextPtr context);
    virtual ~ScriptComponent() = default;

    virtual void update(float timeStep);
private:
    common::ContextPtr context_;
};
}
}
}
#endif //ELFBOX_SMCOMPONENT_H
