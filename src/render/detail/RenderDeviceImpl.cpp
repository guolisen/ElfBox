//
// Created by Lewis on 2017/2/20.
//
#include <SDL.h>
#include <graphics/IGraphics.h>
#include "RenderDeviceImpl.h"

namespace elfbox
{
namespace render
{
namespace detail
{
RenderDeviceImpl::RenderDeviceImpl(common::ContextPtr context):
    context_(context), handle_(nullptr), fps_(0.0), backgroundTexture_(nullptr)
{
}

void RenderDeviceImpl::render(float timeStep)
{
    if (!handle_)
    {
        graphics::GraphicsPtr graphics =
            context_->getComponent<graphics::IGraphics>(nullptr);
        handle_ = graphics->getRendererHandle();

        backgroundTexture_ = SDL_CreateTexture(
            (SDL_Renderer*)handle_, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, 4000, 3000);
    }

    SDL_Rect viewRect = toSDLRect(camera_->getCameraViewRect());
    SDL_RenderSetClipRect((SDL_Renderer*)handle_, &viewRect);

    SDL_SetRenderTarget((SDL_Renderer*)handle_, backgroundTexture_);
    SDL_SetRenderDrawColor((SDL_Renderer*)handle_, 0x0, 0x0, 0x0, 0x0);
    SDL_RenderClear((SDL_Renderer*)handle_);
    //SDL_RenderSetViewport((SDL_Renderer*)handle_, &viewRect);

    //float zoom = camera_->getCameraZoom();
    //SDL_RenderSetScale((SDL_Renderer*)handle_, zoom, zoom);
    for (auto &drawable : drawableList_)
    {
        RectFloat worldToCameraRect =
            camera_->worldToCamera(drawable->getData().worldRect);
        SDL_Rect srcRect = toSDLRect(drawable->getData().sourceRect);
        SDL_Rect destRect = toSDLRect(worldToCameraRect);
        SDL_RenderCopy((SDL_Renderer*)handle_,
                       (SDL_Texture*)drawable->getData().material->getMaterial(),
                       &srcRect, &destRect);
    }
    SDL_SetRenderTarget((SDL_Renderer*)handle_, NULL);

    SDL_Rect zoomCameraRect = toSDLRect(camera_->getCameraViewZoomRect());
    SDL_SetRenderDrawColor((SDL_Renderer*)handle_, 0x0, 0x0, 0x0, 0x0);
    SDL_RenderClear((SDL_Renderer*)handle_);

    SDL_RenderCopy((SDL_Renderer*)handle_, backgroundTexture_, &zoomCameraRect, NULL);
    SDL_RenderPresent((SDL_Renderer*)handle_);

    update(timeStep);
}

void RenderDeviceImpl::addDrawable(DrawablePtr drawable)
{
    drawableList_.push_back(drawable);
}

}
}
}