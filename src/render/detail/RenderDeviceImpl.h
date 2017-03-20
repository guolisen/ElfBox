//
// Created by Lewis on 2017/2/20.
//

#ifndef ELFBOX_RENDERDEVICEIMPL_H
#define ELFBOX_RENDERDEVICEIMPL_H

#include <SDL.h>
#include <list>
#include <common/IObject.h>
#include <common/Context.h>
#include <graphics/IGraphics.h>
#include <scene/ICamera.h>
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

    virtual void render(float timeStep);
    virtual void addDrawable(DrawablePtr drawable);
    virtual void setCamera(scene::CameraPtr camera)
    {
        camera_ = camera;
    }
    virtual void clearDrawable()
    {
        drawableList_.clear();
    }
private:
    void updateDrawable();
    RectFloat getPreLoadRect();

    void update(float dt)
    {
#if 0
        static float _total_frames = 0.0f;
        static float _total_time = 0.0f;
        ++_total_frames;
        _total_time += dt;
        fps_ = _total_frames/_total_time;

        printf("!!!fps: %f frames: %f time: %f dt: %f\n",
               fps_, _total_frames, _total_time, dt);

        if (_total_frames > 50)
        {
            _total_frames = _total_time = 0.0;
        }
#endif
    }

    template <class T>
    SDL_Rect toSDLRect(Rect<T> rect)
    {
        SDL_Rect sdlRect = {(int)rect.x, (int)rect.y, (int)rect.w, (int)rect.h};
        return sdlRect;
    }

    common::ContextPtr context_;
    std::list<DrawablePtr> drawableList_;
    graphics::RendererHandle handle_;
    float fps_;
    scene::CameraPtr camera_;
    SDL_Texture* backgroundTexture_;
    float preLoadRange_;
};
}
}
}

#endif //ELFBOX_RENDERDEVICEIMPL_H
