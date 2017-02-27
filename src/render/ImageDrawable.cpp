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

void ImageDrawable::setMaterial(RenderMaterialPtr material)
{
    data_.material = material;
    data_.sourceRect = material->getRect();
    data_.worldRect = data_.sourceRect;
}
}
}