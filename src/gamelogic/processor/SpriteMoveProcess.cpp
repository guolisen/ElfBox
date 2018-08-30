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
    elapsedTime_ += timeStep * 1000;
    if (elapsedTime_ <= animationSpeedTime_)
    {
        return;
    }

    elapsedTime_ = 0.0;

    float moveStep = 300.0f * timeStep;
    RectFloat currentRect = sceneNode_->getNodeRect();
    Point2DFloat currentPosition = currentRect.getPosition();

    Vector2DFloat moveStepVec(moveVec_.x, moveVec_.y) ;
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
    isFinished_ = true;
}

void SpriteMoveProcess::move(Point2DFloat destinationPoint, float speed)
{
    moveVec_ = destinationPoint;

    RectFloat currentRect = sceneNode_->getNodeRect();
    Point2DFloat currentPosition = currentRect.getPosition();

    targetPoint_ = currentPosition + moveVec_;
    walkSpeed_ = speed;
}

}
}