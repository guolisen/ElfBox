//
// Created by Lewis on 2018/8/27.
//

#ifndef ELFBOX_GAMEINTERFACE_H
#define ELFBOX_GAMEINTERFACE_H

#include <common/IObject.h>
#include <common/Context.h>
#include <gamelogic/IGameData.h>
#include <gamelogic/IGameDirector.h>
#include <gamelogic/IGameManager.h>
#include <gamelogic/IGameSprite.h>
#include <gamelogic/scene/IScene.h>
#include <gamelogic/scene/ISceneManager.h>
#include <gamelogic/scene/ISceneNode.h>
#include <common/IObjectFactory.h>

namespace elfbox
{
namespace gamelogic
{
class GameManager : public IGameManager
{
ELF_OBJECT(GameManager, IGameManager);
public:
    GameManager(common::ContextPtr context,
                  GameDirectorPtr gameDirector,
                  GameDataPtr gameData,
                  scene::SceneManagerPtr sceneManager);
    virtual ~GameManager() = default;

    virtual void setCurrentScene(scene::ScenePtr newScene) override;
    virtual scene::ScenePtr sceneFactory() override;
    virtual GameSpritePtr getSprite(const std::string& spriteName);
    virtual void registerSprite(const std::string& spriteName,
                                scene::SceneNodePtr spriteNode);
private:
    common::ContextPtr context_;
    common::ObjectFactoryPtr objFactory_;
    GameDirectorPtr gameDirector_;
    GameDataPtr gameData_;
    scene::SceneManagerPtr sceneMgr_;
    std::map<std::string, GameSpritePtr> spriteMap_;
};
}
}

#endif //ELFBOX_GAMEINTERFACE_H
