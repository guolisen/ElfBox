//
// Created by Lewis on 2017/2/20.
//
#include <SDL.h>
#include <graphics/IGraphics.h>
#include "ImageDrawable.h"

namespace elfbox
{
namespace render
{
#if 0
void ImageDrawable::update()
{

}

void ImageDrawable::render()
{
    graphics::GraphicsPtr graphics =
        context_->getComponent<graphics::IGraphics>(nullptr);
    graphics::RendererHandle handle = graphics->getRendererHandle();

    SDL_Rect srcRect = {sourceRect.x, sourceRect.y, sourceRect.w, sourceRect.h};
    SDL_Rect destRect = {worldRect.x, worldRect.y, worldRect.w, worldRect.h};
    SDL_RenderCopy((SDL_Renderer*)handle, (SDL_Texture*)material->getMaterial(),
                   &srcRect, &destRect);
}
#endif
void ImageDrawable::loadMaterial()
{
    data_.material->loadMaterial();
    data_.sourceRect = data_.material->getRect();
    data_.worldRect = data_.material->getRect();
    data_.worldRect.x = 0;
    data_.worldRect.y = 0;
}
}
}