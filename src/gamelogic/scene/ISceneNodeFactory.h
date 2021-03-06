//
// Created by Lewis on 2017/2/27.
//

#ifndef ELFBOX_ISCENENODEFACTORY_H
#define ELFBOX_ISCENENODEFACTORY_H

#include <memory>
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

    virtual SceneNodePtr createNode(render::IDrawable::Factory drawableFactory,
                                           const std::string& nodeName,
                                           const std::string& resFileName,
                                           const RectFloat& worldRect,
                                           const RectFloat& sourceRect,
                                           int zorder) = 0;

    template <class NodeType>
    SceneNodePtr createNode(const std::string& nodeName,
                                           const std::string& resFileName,
                                           const RectFloat& worldRect,
                                           const RectFloat& sourceRect,
                                           int zorder)
    {
        return createNode(NodeType::getFactory(),
                          nodeName, resFileName, worldRect, sourceRect, zorder);
    }

};

typedef std::shared_ptr<ISceneNodeFactory> SceneNodeFactoryPtr;

}
}

#endif //ELFBOX_SCENENODEFACTORY_H
