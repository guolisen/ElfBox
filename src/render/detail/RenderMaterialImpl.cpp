//
// Created by Lewis on 2017/2/20.
//
#include <SDL.h>
#include <SDL_image.h>
#include <graphics/IGraphics.h>
#include "RenderMaterialImpl.h"

namespace elfbox
{
namespace render
{
namespace detail
{
RenderMaterialImpl::RenderMaterialImpl(common::ContextPtr context,
                                       const std::string& fileName) :
    context_(context), fileName_(fileName), materialWidth_(0),
    materialHeight_(0), isLoad_(false), materialTextureHandle_(nullptr),
    materialSurfaceHandle_(nullptr) {}

bool RenderMaterialImpl::loadResource()
{
    if (isLoad_)
        return true;

    graphics::GraphicsPtr graphics =
        context_->getComponent<graphics::IGraphics>(nullptr);
    graphics::RendererHandle handle = graphics->getRendererHandle();

    std::string tmpStr = std::string("E:/code/ElfClion/ElfBox/res/") + fileName_;
    materialSurfaceHandle_ = (MaterialSurfaceHandle)IMG_Load(tmpStr.c_str());
    if (materialSurfaceHandle_ == nullptr)
    {
        printf("Cannot open res file: %s\n", fileName_.c_str());
        return false;
    }

    materialTextureHandle_ = SDL_CreateTextureFromSurface(
        (SDL_Renderer*)handle, (SDL_Surface*)materialSurfaceHandle_);
    if (materialTextureHandle_ == nullptr)
    {
        printf("Create Surface Error!\n");
        printf("SDL_CreateTextureFromSurface return %s\n", SDL_GetError());

        return false;
    }

    materialWidth_ = ((SDL_Surface*)materialSurfaceHandle_)->w;
    materialHeight_ = ((SDL_Surface*)materialSurfaceHandle_)->h;

    isLoad_ = true;
    return true;
}

bool RenderMaterialImpl::setFileName(const std::string& fileName)
{
    fileName_ = fileName;
    return true;
}

MaterialTextureHandle RenderMaterialImpl::getMaterial()
{
    return materialTextureHandle_;
}

}
}
}