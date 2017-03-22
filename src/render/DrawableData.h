//
// Created by Lewis on 2017/2/20.
//

#ifndef ELFBOX_DRAWABLEDATA_H
#define ELFBOX_DRAWABLEDATA_H

#include <string>
#include <common/IObject.h>
#include <common/Context.h>
#include <render/detail/RenderMaterialImpl.h>
#include "IRenderMaterial.h"
#include "RenderMaterial.h"
#include "detail/RenderMaterialImpl.h"

namespace elfbox
{
namespace render
{

template <class T>
struct NoThisFunction {};

template <class T>
struct MaterialPosition
{
    T x;
    T y;

    MaterialPosition():
        x(0), y(0) {}
    MaterialPosition(T posX, T posY):
        x(posX), y(posY) {}
    MaterialPosition(const MaterialPosition& other)
    {
        x = other.x;
        y = other.y;
    }
};
typedef MaterialPosition<unsigned int> MaterialPositionUint;

template <class T>
struct WorldRectPosition
{
    Rect<T> worldRect;

    WorldRectPosition():
        worldRect(0, 0, 0, 0) {}
    WorldRectPosition(T rx, T ry, T rw, T rh):
        worldRect(rx, ry, rw, rh) {}
};
typedef WorldRectPosition<int> WorldRectPositionInt;

template <class T>
struct SourceRectPosition
{
    Rect<T> sourceRect;

    SourceRectPosition():
        sourceRect(0, 0, 0, 0) {}
    SourceRectPosition(T rx, T ry, T rw, T rh):
        sourceRect(rx, ry, rw, rh) {}
};
typedef SourceRectPosition<int> SourceRectPositionInt;

struct MaterialFactoryType
{
    system::ResourceFactory materialFactory;

    MaterialFactoryType(common::ContextPtr context,
                        const std::string& fileName) {}
};

struct SingleMaterialType
{
    RenderMaterialPtr material;
    SingleMaterialType(common::ContextPtr context, const std::string& fileName):
        material(std::make_shared<RenderMaterial>(
            std::make_shared<detail::RenderMaterialImpl>(context, fileName)
        )) {}
};

enum DrawableState
{
    DrawableStateDrawing,
    DrawableStateDelete,
    DrawableStatePending
};

enum DrawableType
{
    DrawableTypeImage
};

template <class RectType = float>
struct DrawableData
{
    RenderMaterialPtr material;
    Rect<RectType> worldRect;
    Rect<RectType> sourceRect;
    int zorder;
    DrawableState drawableState;
    DrawableType drawableType;

    DrawableData(common::ContextPtr context,
                 Rect<RectType> worldRectParam, Rect<RectType> sourceRectParam):
        worldRect(worldRectParam),
        sourceRect(sourceRectParam), zorder(0), drawableState(DrawableStatePending),
    drawableType(DrawableTypeImage) {}

    DrawableData(common::ContextPtr context):
        zorder(0),  drawableState(DrawableStatePending),
        drawableType(DrawableTypeImage) {}

    typedef Rect<RectType> DataRectType;
};

}
}

#endif //ELFBOX_DRAWABLEDATA_H
