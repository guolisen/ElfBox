//
// Created by Lewis on 2017/2/25.
//

#ifndef ELFBOX_SCENE_H
#define ELFBOX_SCENE_H

#include <functional>
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
    typedef std::function<scene::ScenePtr(common::ContextPtr context)> Factory;
public:
    Scene() = default;
    Scene(common::ContextPtr context);
    virtual ~Scene() = default;

    virtual bool initialize() override;
    virtual void update(float timeStep) override;
    virtual bool load(const std::string& fileName) override;

    virtual void startToDraw() override
    {
        for (auto layer : layerList_)
            layer->startToDraw();
    }
    virtual void terminate() override;

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
    std::list<SceneNodePtr> layerList_;
    std::list<common::Subscription> subscriptionList_;
    CameraPtr camera_;
    int key_;
};


}
}

#endif //ELFBOX_SCENE_H
