//
// Created by Lewis on 2017/2/20.
//

#include <list>
#include <SDL.h>
#include <graphics/IGraphics.h>
#include <gamelogic/scene/Camera.h>
#include <system/IWindow.h>
#include <algorithm>
#include "RenderDeviceImpl.h"

namespace elfbox
{
namespace render
{
namespace detail
{

RenderDeviceImpl::RenderDeviceImpl(common::ContextPtr context):
    context_(context), handle_(nullptr), fps_(0.0),
    backgroundTexture_(nullptr), preLoadRange_(2048.0f),
    preLoadRect_(RectFloat(0, 0, preLoadRange_, preLoadRange_)),
    preLoadTrigerRect_(RectFloat(0, 0, preLoadRange_ * 0.8f, preLoadRange_ * 0.8f))
{
    system::WindowPtr window =
        context_->getComponent<system::IWindow>(nullptr);

    float winWidth = window->getWindowWidth();
    float winHeight = window->getWindowHeight();
    setCamera(std::make_shared<scene::Camera>(
        context_, Point2DFloat(0, 0), 1.0,
        winHeight, winWidth / winHeight));
}

void RenderDeviceImpl::render(float timeStep)
{
    if (!handle_)
    {
        graphics::GraphicsPtr graphics =
            context_->getComponent<graphics::IGraphics>(nullptr);
        handle_ = graphics->getRendererHandle();
        if (!handle_)
            return;

        backgroundTexture_ = SDL_CreateTexture(
            (SDL_Renderer*)handle_, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, 1024, 768);
    }

    //updatePreLoadRect();
    //updatePreLoadDrawable();
    updateCheckDrawable();

    SDL_Rect viewRect = toSDLRect(camera_->getCameraScreenRect());
    SDL_RenderSetClipRect((SDL_Renderer*)handle_, &viewRect);

    //set Texture
    SDL_SetRenderTarget((SDL_Renderer*)handle_, backgroundTexture_);
    SDL_SetRenderDrawColor((SDL_Renderer*)handle_, 0x0, 0x0, 0x0, 0x0);
    SDL_RenderClear((SDL_Renderer*)handle_);
    //SDL_RenderSetViewport((SDL_Renderer*)handle_, &viewRect);

    //float zoom = camera_->getCameraZoom();
    //SDL_RenderSetScale((SDL_Renderer*)handle_, zoom, zoom);
    for (auto &drawable : renderList_)
    {
        RectFloat worldToCameraRect =
            camera_->worldToCamera(drawable->getData().worldRect);
        //drawTestRect(worldToCameraRect);
        SDL_Rect srcRect = toSDLRect(drawable->getData().sourceRect);
        SDL_Rect destRect = toSDLRect(worldToCameraRect);
        SDL_RenderCopy((SDL_Renderer*)handle_,
                       (SDL_Texture*)drawable->getData().material->getMaterial(),
                       &srcRect, &destRect);
    }

    for (auto &drawable : drawableList_)
    {
       RectFloat worldToCameraRect =
          camera_->worldToCamera(drawable->getData().worldRect);
       //drawTestRect(worldToCameraRect);
    }
    SDL_SetRenderTarget((SDL_Renderer*)handle_, NULL);

    SDL_Rect zoomCameraRect = toSDLRect(camera_->getCameraViewZoomRect());
    SDL_SetRenderDrawColor((SDL_Renderer*)handle_, 0x0, 0x0, 0x0, 0x0);
    SDL_RenderClear((SDL_Renderer*)handle_);

    SDL_RenderCopy((SDL_Renderer*)handle_, backgroundTexture_, &zoomCameraRect, &viewRect);

    for (auto &drawable : drawableList_)
    {
        RectFloat worldToCameraRect =
            camera_->worldToCamera(drawable->getData().worldRect);
        drawTestRect(worldToCameraRect);
    }

    SDL_RenderPresent((SDL_Renderer*)handle_);

    update(timeStep);
}

void RenderDeviceImpl::addDrawable(DrawablePtr drawable)
{
    drawableList_.push_back(drawable);
}

void RenderDeviceImpl::updatePreLoadDrawable()
{
    int draw = 0;
    int rend = 0;
    int undraw = 0;
    renderList_.clear();
    for (auto &drawable : drawableList_)
    {
        if (!preLoadRect_.isIntersectionRect(drawable->getData().worldRect))
        {
            ++undraw;
            if (drawable->getData().material->isTextureLoad())
                drawable->getData().material->releaseFromTexture();
            drawable->getData().drawableState = DrawableStatePending;
            continue;
        }
        ++draw;
        if (!drawable->getData().material->loadToTexture())
        {
            printf("loadToTexture error!\n");
            return;
        }

        if (camera_->isInView(drawable->getData().worldRect))
        {
            ++rend;
            drawable->getData().drawableState = DrawableStateDrawing;
            renderList_.push_back(drawable);
        }
        int b = 10;
        b++;
    }

    int a = 10;
    a++;
}

void RenderDeviceImpl::updatePreLoadRect()
{
    RectFloat cameraRect = camera_->getCameraWorldRect();
    
    if (!preLoadTrigerRect_.isIncludeRect(cameraRect))
    {
        //printf("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n");
        Point2DFloat center = camera_->getCameraCenter();
        preLoadRect_.x = center.x - preLoadRange_ / 2.0f;
        preLoadRect_.y = center.y - preLoadRange_ / 2.0f;

        preLoadTrigerRect_.x = center.x - (preLoadRange_ * 0.8f) / 2.0f;
        preLoadTrigerRect_.y = center.y - (preLoadRange_ * 0.8f) / 2.0f;
    }
}

bool RenderDeviceImpl::initialize()
{
    return true;
}

void RenderDeviceImpl::drawTestRect(RectFloat rect)
{
    SDL_SetRenderDrawColor((SDL_Renderer*)handle_, 0xFF, 0xFF, 0xFF, 0xFF);

    Point2DFloat ul = rect.getUpperLeft();
    Point2DFloat ur = rect.getUpperRight();
    Point2DFloat bl = rect.getBottomLeft();
    Point2DFloat br = rect.getBottomRight();

    SDL_RenderDrawLine((SDL_Renderer*)handle_, (int)ul.x, (int)ul.y, (int)ur.x, (int)ur.y);
    SDL_RenderDrawLine((SDL_Renderer*)handle_, (int)ur.x, (int)ur.y, (int)br.x, (int)br.y);
    SDL_RenderDrawLine((SDL_Renderer*)handle_, (int)br.x, (int)br.y, (int)bl.x, (int)bl.y);
    SDL_RenderDrawLine((SDL_Renderer*)handle_, (int)bl.x, (int)bl.y, (int)ul.x, (int)ul.y);
}

void RenderDeviceImpl::updateCheckDrawable()
{
    struct cmpFunc
    {
        bool operator()(const DrawablePtr& lo, const DrawablePtr& ro) const
        {
            return (lo->getData().zorder < ro->getData().zorder);
        }
    };

    renderList_.clear();
    for (auto &drawable : drawableList_)
    {
        RectFloat worldToCameraRect =
            camera_->worldToCamera(drawable->getData().worldRect);
        //if (!camera_->isInView(worldToCameraRect))
        //    continue;
        //if (DrawableStatePending == drawable->getData().drawableState)
        //    continue;
        renderList_.push_back(drawable);
    }


	renderList_.sort(cmpFunc());
}

}
}
}