//
// Created by Lewis on 2017/2/27.
//

#ifndef ELFBOX_SCENENODEFACTORY_H
#define ELFBOX_SCENENODEFACTORY_H

#include <common/IObject.h>
#include <common/Context.h>
#include <render/IDrawable.h>
#include "SceneNode.h"
#include <render/ImageDrawable.h>
#include <system/IResourceCache.h>

namespace elfbox
{
namespace scene
{
class ISceneNodeFactory : public common::IObject
{
ELF_OBJECT(ISceneNodeFactory, common::IObject);
public:
    virtual ~ISceneNodeFactory() = default;

    virtual std::shared_ptr<ISceneNode> createNode(render::IDrawable::Factory drawableFactory,
                                           const std::string& nodeName,
                                           const std::string& resFileName,
                                           const Point2DFloat& worldPostion,
                                           int zorder) = 0;

    template <class NodeType>
    std::shared_ptr<ISceneNode> createNode(const std::string& nodeName,
                                           const std::string& resFileName,
                                           const Point2DFloat& worldPostion,
                                           int zorder)
    {
        return createNode(render::ImageDrawable::getFactory(),
                          nodeName, resFileName, worldPostion, zorder);
    }

};

}
}

#endif //ELFBOX_SCENENODEFACTORY_H
