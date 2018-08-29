//
// Created by Lewis on 2018/8/26.
//

#ifndef ELFBOX_IGAMEINTERFACE_H
#define ELFBOX_IGAMEINTERFACE_H

#include <common/IObject.h>
#include <common/Context.h>
#include <gamelogic/scene/IScene.h>

namespace elfbox
{
namespace gamelogic
{
class IGameManager : public common::IObject
{
ELF_OBJECT(IGameManager, common::IObject);
public:
    virtual ~IGameManager() = default;
    virtual void setCurrentScene(scene::ScenePtr newScene) = 0;
    virtual scene::ScenePtr sceneFactory() = 0;
private:
    common::ContextPtr context_;
};

typedef std::shared_ptr<IGameManager> GameManagerPtr;

}
}

#endif //ELFBOX_IGAMEINTERFACE_H
