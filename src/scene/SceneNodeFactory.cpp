//
// Created by Lewis on 2017/2/27.
//

#include "SceneNodeFactory.h"

namespace elfbox
{
namespace scene
{

std::shared_ptr<ISceneNode> SceneNodeFactory::createNode(
    render::IDrawable::Factory drawableFactory, const std::string& nodeName,
    const std::string& resFileName, const Point2DFloat& worldPostion,
    int zorder)
{
    std::shared_ptr<render::IDrawable> drawable = drawableFactory(context_);

    render::RenderMaterialPtr material =
        cache_->getResource<render::IRenderMaterial>(resFileName);
    if (!material)
    {
        // ELFBOX_LOGERROR(log_, "1.jpg read error!");
        return false;
    }
    drawable->setMaterial(material);

    return std::make_shared<SceneNode>(context_, nodeName, drawable);
}

}
}