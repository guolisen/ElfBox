//
// Created by Lewis on 2017/2/20.
//

#include "RenderDevice.h"
#include "detail/RenderMaterialImpl.h"

namespace elfbox
{
namespace render
{

RenderDevice::RenderDevice(RenderDevicePtr impl):
    impl_(impl)
{
}

void RenderDevice::render(float timeStep)
{
    impl_->render(timeStep);
}

void RenderDevice::addDrawable(DrawablePtr drawable)
{
    impl_->addDrawable(drawable);
}

void RenderDevice::setCamera(scene::CameraPtr camera)
{
    impl_->setCamera(camera);
}
}
}