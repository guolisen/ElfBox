//
// Created by Lewis on 2017/3/3.
//

#ifndef ELFBOX_INODECOMPONENT_H
#define ELFBOX_INODECOMPONENT_H

#include <common/IObject.h>
#include <common/Context.h>
#include <render/IDrawable.h>

namespace elfbox
{
namespace scene
{

class INodeComponent : public common::IObject
{
ELF_OBJECT(INodeComponent, common::IObject);
public:
    INodeComponent(const std::string& componentType):
        componentType_(componentType), activate_(false) {}
    virtual ~INodeComponent() = default;

    virtual void startup() = 0;
    virtual void update(float timeStep) = 0;
    virtual void teardown() = 0;

    virtual bool isActivate()
    {
        return activate_;
    }

    virtual void setActivate(bool flag)
    {
        activate_ = flag;
    }

    virtual void setDrawable(render::DrawablePtr drawable)
    {
        drawable_ = drawable;
    }

    virtual std::string& getComponentType()
    {
        return componentType_;
    }

protected:
    render::DrawablePtr drawable_;
    std::string componentType_;
    bool activate_;
};

typedef std::shared_ptr<INodeComponent> NodeComponentPtr;

}
}

#endif //ELFBOX_NODECOMPONENT_H
