//
// Created by Lewis on 2017/2/24.
//

#ifndef ELFBOX_SCENENODE_H
#define ELFBOX_SCENENODE_H

#include <memory>
#include <list>
#include <map>
#include <common/IObject.h>
#include <common/Context.h>
#include <render/IDrawable.h>
#include "ISceneNode.h"

namespace elfbox
{
namespace scene
{

typedef std::map<std::string, NodeComponentPtr> ComponentMap;

class SceneNode : public ISceneNode
{
ELF_OBJECT(SceneNode, ISceneNode);
public:
    SceneNode() = default;
    SceneNode(common::ContextPtr context,
              const std::string& nodeName,
              render::DrawablePtr drawable);
    virtual ~SceneNode() = default;

    virtual bool initialize();
    virtual void update(float timeStep);
    virtual void startToDraw();

    virtual RectFloat getNodeRect();
    virtual void translate(Vector2DFloat moveDelta);
    virtual void rotate();
    virtual void scale(float scale);

    virtual void translateTo(Vector2DFloat directVec, int speed);
    virtual void rotateTo();
    virtual void scaleTo(float scale);

    virtual void setVisiable(bool flag);
    virtual bool isVisiable();

    virtual std::string getNodeName()
    {
        return nodeName_;
    }

    virtual void addChild(std::shared_ptr<ISceneNode> childNode)
    {
        //childNode->setParentNode(this);
        childList_.push_back(childNode);
    }

    virtual void addComponent(const std::string& componentName,
                              NodeComponentPtr component)
    {
        component->setDrawable(drawable_);
        component->setActivate(true);
        component->startup();
        componentMap_.insert(std::make_pair(componentName, component));
    }

private:
    common::ContextPtr context_;
    std::string nodeName_;
    render::DrawablePtr drawable_;
    Vector2DFloat worldVec_;
    std::list<std::shared_ptr<ISceneNode>> childList_;
    ComponentMap componentMap_;
};
}
}

#endif //ELFBOX_SCENENODE_H
