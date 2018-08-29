//
// Created by Lewis on 2018/8/27.
//

#include "GameManager.h"
#include <gamelogic/scene/Scene.h>


namespace elfbox
{
namespace gamelogic
{

GameManager::GameManager(common::ContextPtr context,
                             GameDirectorPtr gameDirector,
                             GameDataPtr gameData,
                             scene::SceneManagerPtr sceneManager) : context_(context),
    objFactory_(context_->getComponent<common::IObjectFactory>(nullptr)), gameDirector_(gameDirector),
    gameData_(gameData), sceneMgr_(sceneManager)
{
}

void GameManager::setCurrentScene(scene::ScenePtr newScene)
{
    sceneMgr_->setCurrentScene(newScene);
    printf("GameInterface::setCurrentScene Test!!!\n");
}

scene::ScenePtr GameManager::sceneFactory()
{
    return objFactory_->createObject<scene::IScene>(context_);
}
}
}