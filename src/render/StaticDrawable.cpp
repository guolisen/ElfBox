//
// Created by Lewis on 2017/2/20.
//
#include <SDL.h>
#include <graphics/IGraphics.h>
#include "StaticDrawable.h"

namespace elfbox
{
namespace render
{

void StaticDrawable::update()
{

}

void StaticDrawable::render()
{
    graphics::GraphicsPtr graphics =
        context_->getComponent<graphics::IGraphics>(nullptr);
    graphics::RendererHandle handle = graphics->getRendererHandle();

    SDL_Rect srcRect = {sourceRect.x, sourceRect.y, sourceRect.w, sourceRect.h};
    SDL_Rect destRect = {worldRect.x, worldRect.y, worldRect.w, worldRect.h};
    SDL_RenderCopy((SDL_Renderer*)handle, (SDL_Texture*)material->getMaterial(),
                   &srcRect, &destRect);
}

}
}