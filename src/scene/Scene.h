//
// Created by Lewis on 2017/2/25.
//

#ifndef ELFBOX_SCENE_H
#define ELFBOX_SCENE_H

#include <common/IObject.h>
#include <common/Context.h>
#include "ISceneNode.h"
#include "ICamera.h"
#include <common/IMessageBroadcaster.h>

namespace elfbox
{
namespace scene
{
class Scene : public common::IObject
{
ELF_OBJECT(Scene, common::IObject);
public:
    Scene(common::ContextPtr context);
    virtual ~Scene() = default;

    virtual bool initialize();
    virtual void update(float timeStep);
    virtual bool load(const std::string& fileName);

    void keyHandler(common::MessageData data);
private:
    common::ContextPtr context_;
    common::MessageBroadcasterPtr messageBroadcaster_;
    SceneNodePtr rootNode_;
    CameraPtr camera_;
};
}
}

#endif //ELFBOX_SCENE_H
