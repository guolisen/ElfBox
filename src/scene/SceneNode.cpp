//
// Created by Lewis on 2017/2/24.
//

#include "SceneNode.h"

namespace elfbox
{
namespace scene
{

SceneNode::SceneNode(common::ContextPtr context,
                     const std::string& nodeName,
                     render::DrawablePtr drawable) :
    context_(context), nodeName_(nodeName),
    drawable_(drawable) {}

bool SceneNode::initialize()
{
    return false;
}

void SceneNode::update(float timeStep)
{
}

void SceneNode::translate()
{
}

void SceneNode::rotate()
{
}

void SceneNode::scale(float scale)
{
}

void SceneNode::translateTo()
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

}
}