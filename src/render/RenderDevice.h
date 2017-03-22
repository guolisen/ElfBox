//
// Created by Lewis on 2017/2/20.
//

#ifndef ELFBOX_RENDERDEVICE_H
#define ELFBOX_RENDERDEVICE_H

#include <list>
#include <common/IObject.h>

#include "IDrawable.h"
#include "IRenderDevice.h"

namespace elfbox
{
namespace render
{
namespace detail
{
class RenderDeviceImpl;
}

class RenderDevice : public IRenderDevice
{
ELF_OBJECT(RenderDevice, IRenderDevice);
public:
    RenderDevice(RenderDevicePtr impl);
    virtual ~RenderDevice() = default;

    virtual bool initialize();
    virtual void render(float timeStep);
    virtual void addDrawable(DrawablePtr drawable);
    virtual void setCamera(scene::CameraPtr camera);
    virtual void clearDrawable();
private:
    std::list<DrawablePtr> drawableList_;
    RenderDevicePtr impl_;
};
}
}

#endif //ELFBOX_RENDERDEVICE_H
