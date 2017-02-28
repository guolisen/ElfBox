//
// Created by Lewis on 2017/2/24.
//

#ifndef ELFBOX_SCENENODE_H
#define ELFBOX_SCENENODE_H

#include <memory>
#include <list>
#include <common/IObject.h>
#include <common/Context.h>
#include <render/IDrawable.h>
#include "ISceneNode.h"

namespace elfbox
{
namespace scene
{
class SceneNode : public ISceneNode
{
ELF_OBJECT(SceneNode, ISceneNode);
public:
    SceneNode(common::ContextPtr context,
              const std::string& nodeName,
              render::DrawablePtr drawable);
    virtual ~SceneNode() = default;

    virtual bool initialize();
    virtual void update(float timeStep);
    virtual void startToDraw();

    virtual void translate();
    virtual void rotate();
    virtual void scale(float scale);

    virtual void translateTo();
    virtual void rotateTo();
    virtual void scaleTo(float scale);

    virtual void setVisiable(bool flag);
    virtual bool isVisiable();

    virtual std::string getNodeName()
    {
        return nodeName_;
    }

    virtual bool addChild(std::shared_ptr<ISceneNode> childNode)
    {
        childList_.push_back(childNode);
        return true;
    }

private:
    common::ContextPtr context_;
    std::string nodeName_;
    render::DrawablePtr drawable_;
    Vector2DFloat worldVec_;
    std::list<std::shared_ptr<ISceneNode>> childList_;
};
}
}

#endif //ELFBOX_SCENENODE_H
