//
// Created by Lewis on 2017/2/27.
//

#ifndef ELFBOX_SCENENODEFACTORY_H
#define ELFBOX_SCENENODEFACTORY_H

#include <common/IObject.h>
#include <common/Context.h>
#include "SceneNode.h"
#include <render/ImageDrawable.h>
#include <system/IResourceCache.h>

namespace elfbox
{
namespace scene
{
class SceneNodeFactory : public common::IObject
{
ELF_OBJECT(SceneNodeFactory, common::IObject);
public:
    SceneNodeFactory(common::ContextPtr context):
        cache_(context_->getComponent<elfbox::system::IResourceCache>(nullptr)) {}
    virtual ~SceneNodeFactory() = default;

    virtual std::shared_ptr<ISceneNode> createNode(render::IDrawable::Factory drawableFactory,
                                                   const std::string& nodeName,
                                                   const std::string& resFileName,
                                                   const Point2DFloat& worldPostion,
                                                   int zorder);
private:
    common::ContextPtr context_;
    system::ResourceCachePtr cache_;
};

}
}

#endif //ELFBOX_SCENENODEFACTORY_H
