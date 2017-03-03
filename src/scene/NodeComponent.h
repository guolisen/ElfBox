//
// Created by Lewis on 2017/3/3.
//

#ifndef ELFBOX_NODECOMPONENT_H
#define ELFBOX_NODECOMPONENT_H

#include <common/IObject.h>
#include <common/Context.h>
#include "INodeComponent.h"

namespace elfbox
{
namespace scene
{
class NodeComponent : public INodeComponent
{
ELF_OBJECT(NodeComponent, INodeComponent);
public:
    NodeComponent(common::ContextPtr context,
                  const std::string& nodeType);
    virtual ~NodeComponent() = default;

    virtual void setDrawable(render::DrawablePtr drawable)
    {
        drawable_ = drawable;
    }

    virtual std::string& getComponentType()
    {
        return nodeType_;
    }

private:
    common::ContextPtr context_;
    render::DrawablePtr drawable_;
    std::string nodeType_;
};
}
}

#endif //ELFBOX_NODECOMPONENT_H
