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
    drawable_(drawable), worldVec_(0,0) {}

bool SceneNode::initialize()
{
    return false;
}

void SceneNode::update(float timeStep)
{
    moveUpdate(timeStep);
    for (auto& component : componentMap_)
    {
        if (component.second->isActivate())
            component.second->update(timeStep);
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

void SceneNode::move(Point2DFloat destinationPoint, int speed)
{
    //RectFloat currentRect = node_->getNodeRect();
    //Point2DFloat currentPosition = currentRect.getPosition();
    //Vector2DFloat vec = (Point2DFloat)(destinationPoint - currentPosition);

    targetPosition_.push_back(destinationPoint);
}

void SceneNode::moveUpdate(float timeStep)
{
    if (targetPosition_.empty())
        return;

    Point2DFloat nextPosition = targetPosition_[0];
    float move = 5.0f * timeStep;
    RectFloat currentRect = getNodeRect();
    Point2DFloat currentPosition = currentRect.getPosition();

    Vector2DFloat vec = nextPosition - currentPosition;
    float distance = vec.length();
    if (move > distance)
        move = distance;

    //jackNode_->Translate(Vector3::FORWARD * move);
    translate(vec * move);
    if (distance < 0.1f)
        targetPosition_.clear();
}

}
}