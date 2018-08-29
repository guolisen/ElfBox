//
// Created by Lewis on 2017/2/27.
//

#include "SceneNodeFactory.h"

namespace elfbox
{
namespace scene
{

SceneNodePtr SceneNodeFactory::createNode(
    render::IDrawable::Factory drawableFactory, const std::string& nodeName,
    const std::string& resFileName, const RectFloat& worldRect,
    const RectFloat& sourceRect, int zorder)
{
    std::shared_ptr<render::IDrawable> drawable = drawableFactory(context_);

    render::RenderMaterialPtr material =
        cache_->getResource<render::IRenderMaterial>(resFileName);
    if (!material)
    {
        printf("material read error(%s)!\n", resFileName.c_str());
        return SceneNodePtr();
    }
    drawable->setMaterial(material);

    drawable->getData().worldRect = worldRect;
    drawable->getData().sourceRect = sourceRect;
    drawable->getData().zorder = zorder;

    return std::make_shared<SceneNode>(context_, nodeName, drawable);
}

}
}