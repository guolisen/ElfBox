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

    void render(float timeStep);
    void addDrawable(DrawablePtr drawable);

private:
    std::list<DrawablePtr> drawableList_;
    RenderDevicePtr impl_;
};
}
}

#endif //ELFBOX_RENDERDEVICE_H
