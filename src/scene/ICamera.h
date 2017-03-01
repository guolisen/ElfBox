//
// Created by Lewis on 2017/3/1.
//

#ifndef ELFBOX_ICAMERA_H
#define ELFBOX_ICAMERA_H

#include <memory>
#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace scene
{
class ICamera : public common::IObject
{
ELF_OBJECT(ICamera, common::IObject);
public:
    virtual ~ICamera() = default;

    virtual Point2DFloat worldToCamera(Point2DFloat worldPosition) = 0;
    virtual RectFloat worldToCamera(RectFloat worldPosition) = 0;

    virtual RectFloat getCameraViewRect() = 0;
    virtual Point2DFloat getCameraCenter() = 0;
    virtual bool isInView(Point2DFloat point) = 0;
    virtual bool isInView(RectFloat rect) = 0;

    virtual void setPosition(const Point2DFloat& cameraPosition) = 0;
    virtual void setAspectRatio(float aspectRatio) = 0;

    virtual void moveCamera(float xStep, float yStep) = 0;
    virtual void setCameraZoom(float zoom) = 0;
    virtual float getCameraZoom() = 0;
};

typedef std::shared_ptr<ICamera> CameraPtr;

}
}

#endif //ELFBOX_ICAMERA_H
