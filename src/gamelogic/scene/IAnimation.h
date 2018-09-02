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

class IAnimation : public common::IObject
{
ELF_OBJECT(IAnimation, common::IObject);
public:
    IAnimation(): activate_(false) {}
    virtual ~IAnimation() = default;

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

typedef std::shared_ptr<IAnimation> AnimationPtr;

}
}

#endif //ELFBOX_NODECOMPONENT_H
