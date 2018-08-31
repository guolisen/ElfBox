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
                                     isActive_(true),
                                     targetPoint_(Point2DFloat(0.0, 0.0)),
                                     moveVector_(Vector2DFloat(0.0, 0.0)),
                                     elapsedTime_(0.0),
                                     moveStepTime_(0.0),
                                     moveStepPixel_(0.0) {}

void SpriteMoveProcess::update(float timeStep)
{
    elapsedTime_ += timeStep * 1000;
    if (elapsedTime_ <= moveStepTime_)
    {
        return;
    }
    elapsedTime_ = 0.0;

    float moveStep = moveStepPixel_ * timeStep;
    RectFloat currentRect = sceneNode_->getNodeRect();
    Point2DFloat currentPosition = currentRect.getPosition();

    Vector2DFloat moveStepVec(moveVector_.x, moveVector_.y) ;
    moveStepVec.normalize();
    moveStepVec = moveStepVec * moveStep;
    
    Vector2DFloat vec = currentPosition - targetPoint_;
    float distance = vec.length();
    if (moveStep > distance)
    {
        moveStep = distance;
        kill();
    }
    //jackNode_->Translate(Vector3::FORWARD * move);
    sceneNode_->translate(moveStepVec);
}

void SpriteMoveProcess::kill()
{
    processState_ = ProcessFinish;
}

void SpriteMoveProcess::move(const Vector2DFloat& moveVector, float speed)
{
    moveVector_ = moveVector;
    moveStepPixel_ = speed;
    moveStepTime_  = speed;
}

void SpriteMoveProcess::tearDown()
{
}

void SpriteMoveProcess::setUp()
{
    RectFloat currentRect = sceneNode_->getNodeRect();
    Point2DFloat currentPosition = currentRect.getPosition();
    targetPoint_ = currentPosition + moveVector_;
    processState_ = ProcessUpdate;
}

}
}