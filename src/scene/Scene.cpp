//
// Created by Lewis on 2017/2/25.
//
#include "SceneTmxParser.h"
#include "detail/SceneTmxParserImpl.h"
#include "SceneNodeFactory.h"
#include "Scene.h"
#include "Camera.h"
#include <render/IRenderDevice.h>
#include <common/IMessageBroadcaster.h>

namespace elfbox
{
namespace scene
{

Scene::Scene(common::ContextPtr context) :
    context_(context),
    messageBroadcaster_(context_->getComponent<common::IMessageBroadcaster>(nullptr)),
    renderDevice_(context_->getComponent<render::IRenderDevice>(nullptr)),
    camera_(std::make_shared<Camera>(
    context, Point2DFloat(0.0f, 0.0f), 1.0f, 768.0f, 4.0f / 3.0f))
{
}

void Scene::update(float timeStep)
{
    int speedInt = 300;
    if (key_ == 'w')
    {
        camera_->moveCamera(0, -1 * speedInt * timeStep);
    }
    if (key_ == 's')
    {
        camera_->moveCamera(0, 1 * speedInt * timeStep);
    }
    if (key_ == 'a')
    {
        camera_->moveCamera(-1 * speedInt * timeStep, 0);
    }
    if (key_ == 'd')
    {
        camera_->moveCamera(1 * speedInt * timeStep, 0);
    }

    static float zoom = 1.0;
    if (key_ == 't')
    {
        zoom += 0.1 * timeStep;
        camera_->setCameraZoom(zoom);
    }

    if (key_ == 'g')
    {
        zoom -= 0.1 * timeStep;
        camera_->setCameraZoom(zoom);
    }

    for (auto layer : layerList_)
        layer->update(timeStep);
}

bool Scene::load(const std::string& fileName)
{
    SceneTmxParserPtr sceneTmxParser =
        std::make_shared<SceneTmxParser>(
            context_, std::make_shared<detail::SceneTmxParserImpl>(
                context_, std::make_shared<SceneNodeFactory>(context_)));

    sceneTmxParser->loadTmxFile(fileName);
    layerList_ = sceneTmxParser->Parser();
    return true;
}

bool Scene::initialize()
{
    camera_->setPosition(Point2DFloat(0.0f, 0.0f));
    renderDevice_->setCamera(camera_);

    messageBroadcaster_->subscribe(
        common::SYSTEM_EVENT_KEYDOWN,
        std::bind(&Scene::keyHandler, this, std::placeholders::_1));

    messageBroadcaster_->subscribe(
        common::SYSTEM_EVENT_KEYUP,
        std::bind(&Scene::keyUpHandler, this, std::placeholders::_1));


    return true;
}

void Scene::keyUpHandler(common::MessageData data)
{
    //printf("KEY UP!!!!!!!!\n");
    key_ = -1;
}

void Scene::keyHandler(common::MessageData data)
{
    printf("KEY!!!!!!!!\n");
    int key = data["KEY"];
    key_ = data["KEY"];
}

}
}