//
// Created by Lewis on 2018/8/26.
//

#ifndef ELFBOX_IGAMEINTERFACE_H
#define ELFBOX_IGAMEINTERFACE_H

#include <common/IObject.h>
#include <common/Context.h>
#include <gamelogic/IGameSprite.h>
#include <gamelogic/scene/IScene.h>
#include <gamelogic/scene/ISceneNode.h>


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
    virtual GameSpritePtr getSprite(const std::string& spriteName) = 0;
    virtual void registerSprite(const std::string& spriteName,
                                scene::SceneNodePtr spriteNode) = 0;
private:
    common::ContextPtr context_;
};

typedef std::shared_ptr<IGameManager> GameManagerPtr;

}
}

#endif //ELFBOX_IGAMEINTERFACE_H
