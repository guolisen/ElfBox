//
// Created by Lewis on 2017/2/20.
//

#ifndef ELFBOX_RENDERDEVICEIMPL_H
#define ELFBOX_RENDERDEVICEIMPL_H

#include <list>
#include <common/IObject.h>
#include <common/Context.h>
#include <graphics/IGraphics.h>

#include "../IDrawable.h"
#include "../IRenderDevice.h"

namespace elfbox
{
namespace render
{
namespace detail
{
class RenderDeviceImpl : public IRenderDevice
{
ELF_OBJECT(RenderDeviceImpl, IRenderDevice);
public:
    RenderDeviceImpl(common::ContextPtr context);
    virtual ~RenderDeviceImpl() = default;

    void render(float timeStep);
    void addDrawable(DrawablePtr drawable);
private:
    void update(float dt)
    {
        static float _total_frames = 0.0f;
        static float _total_time = 0.0f;
        ++_total_frames;
        _total_time += dt;
        fps_ = _total_frames/_total_time;

        printf("!!!fps: %f frames: %f time: %f dt: %f\n",
               fps_, _total_frames, _total_time, dt);
    }

    common::ContextPtr context_;
    std::list<DrawablePtr> drawableList_;
    graphics::RendererHandle handle_;
    float fps_;
};
}
}
}

#endif //ELFBOX_RENDERDEVICEIMPL_H
