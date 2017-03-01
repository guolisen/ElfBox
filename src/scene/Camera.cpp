//
// Created by Lewis on 2017/3/1.
//

#include "Camera.h"
#include <system/IWindow.h>

namespace elfbox
{
namespace scene
{

Camera::Camera(common::ContextPtr context,
               const Point2DFloat& cameraPosition,
               float cameraZoom, float cameraHeight,
               float aspectRatio) :
    context_(context), cameraPosition_(cameraPosition),
    cameraZoom_(cameraZoom), aspectRatio_(aspectRatio),
    cameraHeight_(cameraHeight),
    cameraWidth_(cameraHeight * aspectRatio_)
{
}

RectFloat Camera::worldToCamera(RectFloat worldPosition)
{
    Point2DFloat inCameraPosition = worldToCamera(worldPosition.getPosition());
    return RectFloat(inCameraPosition.x, inCameraPosition.y,
                     worldPosition.w, worldPosition.h);
}

Point2DFloat Camera::worldToCamera(Point2DFloat worldPosition)
{
    return Point2DFloat(worldPosition.x - cameraPosition_.x,
                        worldPosition.y - cameraPosition_.y);
}

RectFloat Camera::getCameraViewRect()
{
    system::WindowPtr window =
        context_->getComponent<system::IWindow>(nullptr);

    int winWidth = window->getWindowWidth();
    int winHeight = window->getWindowHeight();

    Point2DFloat localCenterPoint(cameraWidth_ / 2.0f, cameraHeight_ / 2.0f);
    Point2DFloat windowsCenterPoint(winWidth / 2.0f, winHeight / 2.0f);

    return RectFloat(windowsCenterPoint.x - localCenterPoint.x,
                     windowsCenterPoint.y - localCenterPoint.y,
                     cameraWidth_, cameraHeight_);
}

Point2DFloat Camera::getCameraCenter()
{
    return Point2DFloat(cameraPosition_.x + (cameraWidth_ / 2.0f),
                        cameraPosition_.y + (cameraHeight_ / 2.0f));
}

bool Camera::isInView(Point2DFloat point)
{
    return true;
}

bool Camera::isInView(RectFloat rect)
{
    return true;
}
}
}