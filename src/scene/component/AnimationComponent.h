//
// Created by Lewis on 2017/3/15.
//

#ifndef ELFBOX_ANIMATIONCOMPONENT_H
#define ELFBOX_ANIMATIONCOMPONENT_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace
{
class AnimationComponent : public common::IObject
{
ELF_OBJECT(AnimationComponent, common::IObject);
public:
    AnimationComponent(common::ContextPtr context);
    virtual ~AnimationComponent() = default;

private:
    common::ContextPtr context_;
};
}
}

#endif //ELFBOX_ANIMATIONCOMPONENT_H
