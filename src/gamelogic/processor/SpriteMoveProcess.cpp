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
                                     walkSpeed_(0.0)
{
}

void SpriteMoveProcess::update(float timeStep)
{
    float moveStep = 5.0f * timeStep;
    RectFloat currentRect = sceneNode_->getNodeRect();
    Point2DFloat currentPosition = currentRect.getPosition();

    Vector2DFloat vec = targetPoint_ - currentPosition;
    float distance = vec.length();
    if (moveStep > distance)
    {
        moveStep = distance;
        kill();
    }

    //jackNode_->Translate(Vector3::FORWARD * move);
    sceneNode_->translate(vec * moveStep);
}

void SpriteMoveProcess::kill()
{
    isFinished_ = true;
}

void SpriteMoveProcess::move(Point2DFloat destinationPoint, float speed)
{
    targetPoint_ = destinationPoint;
    walkSpeed_ = speed;
}

}
}