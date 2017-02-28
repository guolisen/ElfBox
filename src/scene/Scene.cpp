//
// Created by Lewis on 2017/2/25.
//
#include "SceneTmxParser.h"
#include "detail/SceneTmxParserImpl.h"
#include "SceneNodeFactory.h"
#include "Scene.h"

namespace elfbox
{
namespace scene
{

Scene::Scene(common::ContextPtr context) : context_(context)
{
}

void Scene::update(float timeStep)
{
    rootNode_->startToDraw();
}

bool Scene::load(const std::string& fileName)
{
    SceneTmxParserPtr sceneTmxParser =
        std::make_shared<SceneTmxParser>(
            context_, std::make_shared<detail::SceneTmxParserImpl>(
                context_, std::make_shared<SceneNodeFactory>(context_)));

    sceneTmxParser->loadTmxFile(fileName);
    rootNode_ = sceneTmxParser->Parser();
    return true;
}
}
}