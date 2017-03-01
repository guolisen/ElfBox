//
// Created by Lewis on 2017/3/1.
//

#ifndef ELFBOX_CAMERA_H
#define ELFBOX_CAMERA_H

#include <common/IObject.h>
#include <common/Context.h>
#include "ICamera.h"

namespace elfbox
{
namespace scene
{
class Camera : public ICamera
{
ELF_OBJECT(Camera, ICamera);
public:
    Camera(common::ContextPtr context,
           const Point2DFloat& cameraPosition, float cameraZoom,
           float cameraHeight, float aspectRatio);
    virtual ~Camera() = default;

    virtual Point2DFloat worldToCamera(Point2DFloat worldPosition);
    virtual RectFloat worldToCamera(RectFloat worldPosition);
    virtual RectFloat getCameraViewRect();
    virtual Point2DFloat getCameraCenter();
    virtual bool isInView(Point2DFloat point);
    virtual bool isInView(RectFloat rect);

    virtual void setPosition(const Point2DFloat& cameraPosition)
    {
        cameraPosition_ = cameraPosition;
    }
    virtual void setAspectRatio(float aspectRatio)
    {
        aspectRatio_ = aspectRatio;
    }

    virtual void moveCamera(float xStep, float yStep);
    virtual void setCameraZoom(float zoom);
    virtual float getCameraZoom()
    {
        return cameraZoom_;
    }

private:
    common::ContextPtr context_;
    Point2DFloat cameraPosition_;
    float cameraZoom_;
    float aspectRatio_;
    float cameraHeight_;
    float cameraWidth_;
};
}
}

#endif //ELFBOX_CAMERA_H
