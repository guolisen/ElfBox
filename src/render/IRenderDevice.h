//
// Created by Lewis on 2017/2/20.
//

#ifndef ELFBOX_IRENDER_H
#define ELFBOX_IRENDER_H

#include <list>
#include <common/IObject.h>
#include <common/Context.h>
#include <gamelogic/scene/ICamera.h>
#include "IDrawable.h"

namespace elfbox
{
namespace render
{
class IRenderDevice : public common::IObject
{
ELF_OBJECT(IRenderDevice, common::IObject);
public:
    virtual ~IRenderDevice() = default;

    virtual bool initialize() = 0;
    virtual void render(float timeStep) = 0;
    virtual void addDrawable(DrawablePtr drawable) = 0;
    virtual void setCamera(scene::CameraPtr camera) = 0;
    virtual void clearDrawable() = 0;
};

typedef std::shared_ptr<IRenderDevice> RenderDevicePtr;

}
}

#endif //ELFBOX_IRENDER_H
