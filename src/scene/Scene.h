//
// Created by Lewis on 2017/2/25.
//

#ifndef ELFBOX_SCENE_H
#define ELFBOX_SCENE_H

#include <common/IObject.h>
#include <common/Context.h>
#include <common/IMessageBroadcaster.h>
#include <common/IObjectFactory.h>
#include <render/IRenderDevice.h>

#include "ISceneNode.h"
#include "ICamera.h"
#include "IScene.h"

namespace elfbox
{
namespace scene
{
class Scene : public IScene
{
ELF_OBJECT(Scene, IScene);
public:
    Scene() = default;
    Scene(common::ContextPtr context);
    virtual ~Scene() = default;

    virtual bool initialize();
    virtual void update(float timeStep);
    virtual bool load(const std::string& fileName);

    virtual void startToDraw()
    {
        rootNode_->startToDraw();
    }

    static common::IObjectPtr getFactory()
    {
        return std::make_shared<common::ObjectFactoryWrapper<Scene>>();
    }
private:
    void keyHandler(common::MessageData data);
    void keyUpHandler(common::MessageData data);

    common::ContextPtr context_;
    common::MessageBroadcasterPtr messageBroadcaster_;
    render::RenderDevicePtr renderDevice_;
    SceneNodePtr rootNode_;
    CameraPtr camera_;
    int key_;
};


}
}

#endif //ELFBOX_SCENE_H
