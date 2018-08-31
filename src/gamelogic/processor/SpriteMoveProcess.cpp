//
// Created by Lewis on 2018/8/29.
//

#include "SpriteMoveProcess.h"

namespace elfbox
{
namespace gamelogic
{

SpriteMoveProcess::SpriteMoveProcess(common::ContextPtr context,
                                     scene::SceneNodePtr sceneNode) :
                                     context_(context),
                                     sceneNode_(sceneNode),
                                     isFinished_(false),
                                     isActive_(true),
                                     walkSpeed_(0.0),
                                     elapsedTime_(0.0),
                                     animationSpeedTime_(100.0)
{
}

void SpriteMoveProcess::update(float timeStep)
{

}

void SpriteMoveProcess::kill()
{
    isFinished_ = true;
}

void SpriteMoveProcess::move(const Vector2DFloat& destinationPoint, float speed)
{
    printf("SpriteMoveProcess::move!!!!!!!!!!!!\n");
    Vector2DFloat vec(destinationPoint.x, destinationPoint.y);
    sceneNode_->move(vec, speed, speed, [this](){this->kill();});
}

}
}