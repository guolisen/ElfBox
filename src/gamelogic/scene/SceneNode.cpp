//
// Created by Lewis on 2017/2/24.
//

#include "SceneNode.h"
#include <render/IRenderDevice.h>

namespace elfbox
{
namespace scene
{

SceneNode::SceneNode(common::ContextPtr context,
                     const std::string& nodeName,
                     render::DrawablePtr drawable) :
    context_(context), nodeName_(nodeName),
    drawable_(drawable), worldVec_(0,0), isMoveFinish_(true), elapsedTime_(0.0), moveStepTime_(100.0),
    moveStepPixel_(100.0), moveVector_(Vector2DFloat(0.0, 0.0)), targetPoint_(Point2DFloat(0.0, 0.0))
    {}

bool SceneNode::initialize()
{
    return false;
}

void SceneNode::update(float timeStep)
{
    moveUpdate(timeStep);
    for (auto& animation : animationMap_)
    {
        if (animation.second->isActivate())
            animation.second->update(timeStep);
    }

    for (auto& childNode : childList_)
    {
		if (childNode)
			childNode->update(timeStep);
    }
}

void SceneNode::translate(Vector2DFloat moveDelta)
{
    Point2DFloat position = drawable_->getData().worldRect.getPosition();

    position = position + moveDelta;

    drawable_->getData().worldRect.setPosition(position);
}

void SceneNode::rotate()
{
}

void SceneNode::scale(float scale)
{
}

void SceneNode::translateTo(Vector2DFloat directVec, int speed)
{
}

void SceneNode::rotateTo()
{
}

void SceneNode::scaleTo(float scale)
{
}

bool SceneNode::isVisiable()
{
    return false;
}

void SceneNode::setVisiable(bool flag)
{
}

void SceneNode::startToDraw()
{
    render::RenderDevicePtr renderDevice =
        context_->getComponent<render::IRenderDevice>(nullptr);

    if (drawable_)
        renderDevice->addDrawable(drawable_);

    for (auto& childNode : childList_)
    {
		if (childNode)
			childNode->startToDraw();
    }
}

RectFloat SceneNode::getNodeRect()
{
    return drawable_->getData().worldRect;
}

void SceneNode::move(Vector2DFloat moveVector,
                     float pixelStep, float stepTime,
                     MoveCallBack callBack)
{
    if (!isMoveFinish_)
        return;

    moveStepTime_  = stepTime;
    moveStepPixel_ = pixelStep;
    callBack_ = callBack;
    moveVector_ = moveVector;

    RectFloat currentRect = getNodeRect();
    Point2DFloat currentPosition = currentRect.getPosition();

    targetPoint_ = currentPosition + moveVector_;
    isMoveFinish_ = false;
}

void SceneNode::moveUpdate(float timeStep)
{
    if (isMoveFinish_)
        return;

    elapsedTime_ += timeStep * 1000;
    if (elapsedTime_ <= moveStepTime_)
    {
        return;
    }
    elapsedTime_ = 0.0;

    float moveStep = moveStepPixel_ * timeStep;
    RectFloat currentRect = getNodeRect();
    Point2DFloat currentPosition = currentRect.getPosition();

    Vector2DFloat moveStepVecDelta = moveVector_;
    moveStepVecDelta.normalize();
    moveStepVecDelta = moveStepVecDelta * moveStep;

    Vector2DFloat vec = currentPosition - targetPoint_;
    float distance = vec.length();
    if (moveStep > distance)
    {
        moveStep = distance;
        isMoveFinish_ = true;
		if(callBack_)
			callBack_();
    }

    //jackNode_->Translate(Vector3::FORWARD * move);
    translate(moveStepVecDelta);
}

}
}