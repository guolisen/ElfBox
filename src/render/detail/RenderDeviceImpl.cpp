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
    context_(context), handle_(nullptr), fps_(0.0)
{

}

void RenderDeviceImpl::render(float timeStep)
{
    if (!handle_)
    {
        graphics::GraphicsPtr graphics =
            context_->getComponent<graphics::IGraphics>(nullptr);
        handle_ = graphics->getRendererHandle();
    }

    SDL_SetRenderDrawColor((SDL_Renderer*)handle_, 0x0, 0x0, 0x0, 0x0);
    SDL_RenderClear((SDL_Renderer*)handle_);
    for (auto &drawable : drawableList_)
    {
        SDL_Rect srcRect = toSDLRect(drawable->getData().sourceRect);
        SDL_Rect destRect = toSDLRect(drawable->getData().worldRect);
        SDL_RenderCopy((SDL_Renderer*)handle_,
                       (SDL_Texture*)drawable->getData().material->getMaterial(),
                       &srcRect, &destRect);
    }

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