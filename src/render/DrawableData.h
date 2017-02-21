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
    IRenderMaterial::Factory materialFactory;
};

struct SingleMaterialType
{
    RenderMaterialPtr material;
    SingleMaterialType(common::ContextPtr context):
        material(std::make_shared<RenderMaterial>(
            std::make_shared<detail::RenderMaterialImpl>(context, std::string(""))
        )) {}
};

template <class MaterialStorgeType,
    class WorldType,
    class SourceType>
struct DrawableData: public MaterialStorgeType,
                     public WorldType, public SourceType
{
    DrawableData(common::ContextPtr context):
        MaterialStorgeType(context) {}
    int zorder;
};

}
}

#endif //ELFBOX_DRAWABLEDATA_H
