//
// Created by Lewis on 2018/8/27.
//

#ifndef ELFBOX_ISCENEMANAGER_H
#define ELFBOX_ISCENEMANAGER_H

#include <common/IObject.h>
#include <common/Context.h>
#include <gamelogic/scene/IScene.h>

namespace elfbox
{
namespace scene
{
class ISceneManager : public common::IObject
{
ELF_OBJECT(ISceneManager, common::IObject);
public:
    virtual ~ISceneManager() = default;

    virtual bool initialize() = 0;
    virtual void update(float timeStep) = 0;
    virtual void transitionToNewScene(scene::ScenePtr newScene) = 0;
    virtual void setCurrentScene(scene::ScenePtr newScene) = 0;
private:
    common::ContextPtr context_;
};
typedef std::shared_ptr<ISceneManager> SceneManagerPtr;
}
}

#endif //ELFBOX_ISCENEMANAGER_H
