//
// Created by Lewis on 2018/8/27.
//

#include "SceneManager.h"

namespace elfbox
{
namespace scene
{

SceneManager::SceneManager(common::ContextPtr context) :
    context_(context)
{
}

bool SceneManager::initialize()
{
    return false;
}

void SceneManager::update(float timeStep)
{
    if(currentScene_)
        currentScene_->update(timeStep);
}

void SceneManager::transitionToNewScene(scene::ScenePtr newScene)
{
    if(currentScene_)
        currentScene_->terminate();
    currentScene_ = newScene;
    currentScene_->startToDraw();
}

void SceneManager::setCurrentScene(scene::ScenePtr newScene)
{
    transitionToNewScene(newScene);
}
}
}