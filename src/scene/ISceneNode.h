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
class ISceneNode : public common::IObject
{
ELF_OBJECT(ISceneNode, common::IObject);
public:
    virtual ~ISceneNode() = default;

    virtual bool initialize() = 0;
    virtual void update(float timeStep) = 0;
    virtual void startToDraw() = 0;
    virtual void translate() = 0;
    virtual void rotate() = 0;
    virtual void scale(float scale) = 0;

    virtual void translateTo() = 0;
    virtual void rotateTo() = 0;
    virtual void scaleTo(float scale) = 0;

    virtual void setVisiable(bool flag) = 0;
    virtual bool isVisiable() = 0;
    virtual std::string getNodeName() = 0;

    virtual void addChild(std::shared_ptr<ISceneNode> childNode) = 0;
};

typedef std::shared_ptr<ISceneNode> SceneNodePtr;
}
}

#endif //ELFBOX_ISCENENODE_H
