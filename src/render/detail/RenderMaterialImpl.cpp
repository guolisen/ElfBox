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
    materialHeight_(0), isLoad_(false), isTextureLoad_(false),
    materialTextureHandle_(nullptr),
    materialSurfaceHandle_(nullptr),
    renderHandle_(nullptr)
{
    graphics::GraphicsPtr graphics =
        context_->getComponent<graphics::IGraphics>(nullptr);
    renderHandle_ = (SDL_Renderer*)graphics->getRendererHandle();
}

bool RenderMaterialImpl::loadResource()
{
    if (isLoad_)
        return true;

    std::string tmpStr = std::string("E:/code/ElfClion/ElfBox/res/map3/") + fileName_;
    materialSurfaceHandle_ = (MaterialSurfaceHandle)IMG_Load(tmpStr.c_str());
    if (materialSurfaceHandle_ == nullptr)
    {
        printf("Cannot open res file: %s\n", fileName_.c_str());
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
    if (!isTextureLoad_)
        loadToTexture();
    return materialTextureHandle_;
}

bool RenderMaterialImpl::releaseResource()
{
    return true;
}

bool RenderMaterialImpl::loadToTexture()
{
    if (isTextureLoad_)
        return true;

    materialTextureHandle_ = SDL_CreateTextureFromSurface(
        renderHandle_, (SDL_Surface*)materialSurfaceHandle_);
    if (materialTextureHandle_ == nullptr)
    {
        printf("Create Texture Error!\n");
        printf("SDL_CreateTextureFromSurface return %s\n", SDL_GetError());

        return false;
    }

    isTextureLoad_ = true;
    return true;
}

bool RenderMaterialImpl::releaseFromTexture()
{
    SDL_DestroyTexture((SDL_Texture*)materialTextureHandle_);
    materialTextureHandle_ = nullptr;
    isTextureLoad_ = false;
    return true;
}
}
}
}