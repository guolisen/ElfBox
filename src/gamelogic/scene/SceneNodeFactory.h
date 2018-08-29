//
// Created by Lewis on 2017/2/27.
//

#ifndef ELFBOX_SCENENODEFACTORY_H
#define ELFBOX_SCENENODEFACTORY_H

#include <common/IObject.h>
#include <common/Context.h>
#include <render/ImageDrawable.h>
#include <system/IResourceCache.h>
#include "SceneNode.h"
#include "ISceneNodeFactory.h"

namespace elfbox
{
namespace scene
{
class SceneNodeFactory : public ISceneNodeFactory
{
ELF_OBJECT(SceneNodeFactory, ISceneNodeFactory);
public:
    SceneNodeFactory(common::ContextPtr context) : context_(context),
        cache_(context_->getComponent<elfbox::system::IResourceCache>(nullptr)) {}
    virtual ~SceneNodeFactory() = default;

    virtual SceneNodePtr createNode(render::IDrawable::Factory drawableFactory,
                                                   const std::string& nodeName,
                                                   const std::string& resFileName,
                                                   const RectFloat& worldRect,
                                                   const RectFloat& sourceRect,
                                                   int zorder);
private:
    common::ContextPtr context_;
    system::ResourceCachePtr cache_;
};

}
}

#endif //ELFBOX_SCENENODEFACTORY_H
