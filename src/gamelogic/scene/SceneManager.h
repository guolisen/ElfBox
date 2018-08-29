//
// Created by Lewis on 2018/8/27.
//

#ifndef ELFBOX_SCENEMANAGER_H
#define ELFBOX_SCENEMANAGER_H

#include <common/IObject.h>
#include <common/Context.h>
#include <gamelogic/scene/ISceneManager.h>
#include <gamelogic/scene/IScene.h>

namespace elfbox
{
namespace scene
{
class SceneManager : public ISceneManager
{
ELF_OBJECT(SceneManager, ISceneManager);
public:
    SceneManager(common::ContextPtr context);
    virtual ~SceneManager() = default;

    virtual bool initialize() override;
    virtual void update(float timeStep) override;
    virtual void transitionToNewScene(scene::ScenePtr newScene) override;
    virtual void setCurrentScene(scene::ScenePtr newScene) override;
private:
    common::ContextPtr context_;
    scene::ScenePtr currentScene_;
};
}
}

#endif //ELFBOX_SCENEMANAGER_H
