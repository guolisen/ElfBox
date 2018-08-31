//
// Created by Lewis on 2017/2/24.
//

#ifndef ELFBOX_ISCENENODE_H
#define ELFBOX_ISCENENODE_H

#include <memory>
#include <list>
#include <common/IObject.h>
#include "INodeComponent.h"

namespace elfbox
{
namespace scene
{

typedef std::function<void()> MoveCallBack;

class ISceneNode : public common::IObject
{
ELF_OBJECT(ISceneNode, common::IObject);
public:
    virtual ~ISceneNode() = default;

    virtual bool initialize() = 0;
    virtual void update(float timeStep) = 0;

    virtual RectFloat getNodeRect() = 0;
    virtual void startToDraw() = 0;
    virtual void translate(Vector2DFloat moveDelta) = 0;
    virtual void rotate() = 0;
    virtual void scale(float scale) = 0;

    virtual void translateTo(Vector2DFloat directVec, int speed) = 0;
    virtual void rotateTo() = 0;
    virtual void scaleTo(float scale) = 0;

    virtual void setVisiable(bool flag) = 0;
    virtual bool isVisiable() = 0;
    virtual std::string getNodeName() = 0;

    virtual void addChild(std::shared_ptr<ISceneNode> childNode) = 0;
    virtual void addComponent(const std::string& componentName,
                              NodeComponentPtr component) = 0;

    virtual void setParentNode(std::shared_ptr<ISceneNode> parentNode)
    {
        parentNode_ = parentNode;
    }
    virtual void move(Vector2DFloat moveVector,
                      float pixelStep, float stepTime,
                      MoveCallBack callBack) = 0;
protected:
    std::shared_ptr<ISceneNode> parentNode_;
};

typedef std::shared_ptr<ISceneNode> SceneNodePtr;
}
}

#endif //ELFBOX_ISCENENODE_H
