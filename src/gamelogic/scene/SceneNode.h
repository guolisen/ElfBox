//
// Created by Lewis on 2017/2/24.
//

#ifndef ELFBOX_SCENENODE_H
#define ELFBOX_SCENENODE_H

#include <functional>
#include <memory>
#include <list>
#include <vector>
#include <map>
#include <common/IObject.h>
#include <common/Context.h>
#include <render/IDrawable.h>
#include "ISceneNode.h"

namespace elfbox
{
namespace scene
{

typedef std::map<std::string, AnimationPtr> AnimationMap;

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

    virtual void addAnimation(const std::string &animationName,
                              AnimationPtr animation)
    {
        animation->setDrawable(drawable_);
        animation->startup();
        animationMap_.insert(std::make_pair(animationName, animation));
    }

    virtual void move(Vector2DFloat moveVector,
                      float pixelStep, float stepTime,
                      MoveCallBack callBack);

    //virtual bool setAnimation(const std::string animationName);
private:
    virtual void moveUpdate(float timeStep);

    common::ContextPtr context_;
    std::string nodeName_;
    render::DrawablePtr drawable_;
    Vector2DFloat worldVec_;
    std::list<std::shared_ptr<ISceneNode>> childList_;
    AnimationMap animationMap_;

    bool isMoveFinish_;
    float elapsedTime_;
    float moveStepTime_;
    float moveStepPixel_;
    Vector2DFloat moveVector_;
    Point2DFloat  targetPoint_;
    MoveCallBack  callBack_;
};
}
}

#endif //ELFBOX_SCENENODE_H
