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
    virtual ~INodeComponent() = default;

    virtual void setDrawable(render::DrawablePtr drawable) = 0;
    virtual std::string& getComponentType() = 0;
    virtual void update(float timeStep) = 0;

    virtual bool isActivate() = 0;
    virtual void setActivate(bool flag) = 0;
};

typedef std::shared_ptr<INodeComponent> NodeComponentPtr;

}
}

#endif //ELFBOX_NODECOMPONENT_H
