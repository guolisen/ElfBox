//
// Created by Lewis on 2017/3/30.
//

#include "Sprite.h"

namespace elfbox
{
namespace scene
{

Sprite::Sprite(common::ContextPtr context, SceneNodePtr node) :
    context_(context), node_(node)
{
}

void Sprite::move(Point2DFloat destinationPoint, int speed)
{
    //RectFloat currentRect = node_->getNodeRect();
    //Point2DFloat currentPosition = currentRect.getPosition();
    //Vector2DFloat vec = (Point2DFloat)(destinationPoint - currentPosition);

    targetPosition_.push_back(destinationPoint);
}

bool Sprite::setAnimation(const std::string animationName)
{
    return false;
}

void Sprite::update(float timeStep)
{
    if (targetPosition_.empty())
        return;

    Point2DFloat nextPosition = targetPosition_[0];
    float move = 5.0f * timeStep;
    RectFloat currentRect = node_->getNodeRect();
    Point2DFloat currentPosition = currentRect.getPosition();

    Vector2DFloat vec = nextPosition - currentPosition;
    float distance = vec.length();
    if (move > distance)
        move = distance;

    //jackNode_->Translate(Vector3::FORWARD * move);
    node_->translate(vec * move);
    if (distance < 0.1f)
        targetPosition_.clear();
}

RectFloat Sprite::getNodeRect()
{
    return elfbox::RectFloat();
}

void Sprite::startToDraw()
{
}

void Sprite::translate(Vector2DFloat moveDelta)
{
}

void Sprite::rotate()
{
}

void Sprite::scale(float scale)
{
}

void Sprite::translateTo(Vector2DFloat directVec, int speed)
{
}

void Sprite::rotateTo()
{
}

void Sprite::scaleTo(float scale)
{
}

void Sprite::setVisiable(bool flag)
{
}

bool Sprite::isVisiable()
{
    return false;
}

std::string Sprite::getNodeName()
{
    return std::string();
}

void Sprite::addChild(std::shared_ptr<ISceneNode> childNode)
{
}

void Sprite::addComponent(const std::string &componentName, NodeComponentPtr component)
{
}

bool Sprite::initialize()
{
    return false;
}

}
}