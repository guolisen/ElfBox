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

    winWidth_ = window->getWindowWidth();
    winHeight_ = window->getWindowHeight();

    Point2DFloat localCenterPoint(cameraWidth_ / 2.0f, cameraHeight_ / 2.0f);
    Point2DFloat windowsCenterPoint(winWidth_ / 2.0f, winHeight_ / 2.0f);

    return RectFloat(windowsCenterPoint.x - localCenterPoint.x,
                     windowsCenterPoint.y - localCenterPoint.y,
                     cameraWidth_, cameraHeight_);
}

RectFloat Camera::getCameraViewZoomRect()
{
    Point2DFloat localCenterPoint(cameraWidth_ / 2.0f, cameraHeight_ / 2.0f);
    float zoomWidth = cameraWidth_ * cameraZoom_;
    float zoomHeight = cameraHeight_ * cameraZoom_ * aspectRatio_;
    RectFloat zoomRect = {(localCenterPoint.x - zoomWidth * 0.5f),
                          (localCenterPoint.y - zoomHeight * 0.5f),
                          zoomWidth, zoomHeight};

    return zoomRect;
}

Point2DFloat Camera::getCameraCenter()
{
    return Point2DFloat(cameraPosition_.x + (cameraWidth_ / 2.0f),
                        cameraPosition_.y + (cameraHeight_ / 2.0f));
}

bool Camera::isInView(Point2DFloat point)
{
    Point2DFloat cameraPoint = worldToCamera(point);
    if (cameraPoint.x < 0 || cameraPoint.y < 0)
        return false;

    if (cameraPoint.x > (cameraPosition_.x + cameraWidth_) ||
         cameraPoint.y > (cameraPosition_.y + cameraHeight_))
        return false;

    return true;
}

bool Camera::isInView(RectFloat rect)
{
    Point2DFloat upperLeft = rect.getPosition();
    if (isInView(upperLeft))
        return true;
    Point2DFloat bottomLeft = rect.getBottomLeft();
    if (isInView(bottomLeft))
        return true;
    Point2DFloat bottomRight = rect.getBottomRight();
    if (isInView(bottomRight))
        return true;
    Point2DFloat upperRight = rect.getUpperRight();
    if (isInView(upperRight))
        return true;

    return false;
}

void Camera::moveCamera(float xStep, float yStep)
{
    cameraPosition_.x += xStep;
    cameraPosition_.y += yStep;
}

void Camera::setCameraZoom(float zoom)
{
    cameraZoom_ = zoom;
}

RectFloat Camera::getCameraPositionRect()
{
    return elfbox::RectFloat();
}
}
}