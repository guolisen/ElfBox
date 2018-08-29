//
// Created by Lewis on 2017/3/30.
//

#ifndef ELFBOX_SPRITE_H
#define ELFBOX_SPRITE_H

#include <vector>
#include <common/IObject.h>
#include <common/Context.h>
#include "ISceneNode.h"

namespace elfbox
{
namespace scene
{
class Sprite : public ISceneNode
{
ELF_OBJECT(Sprite, common::IObject);
public:
    Sprite(common::ContextPtr context, SceneNodePtr node);
    virtual ~Sprite() = default;

    virtual bool initialize();
    virtual void update(float timeStep);

    virtual RectFloat getNodeRect();
    virtual void startToDraw();
    virtual void translate(Vector2DFloat moveDelta);
    virtual void rotate();
    virtual void scale(float scale);

    virtual void translateTo(Vector2DFloat directVec, int speed);
    virtual void rotateTo();
    virtual void scaleTo(float scale);

    virtual void setVisiable(bool flag);
    virtual bool isVisiable();
    virtual std::string getNodeName();

    virtual void addChild(std::shared_ptr<ISceneNode> childNode);
    virtual void addComponent(const std::string& componentName,
                              NodeComponentPtr component);


    virtual void move(Point2DFloat destinationPoint, int speed);
    virtual bool setAnimation(const std::string animationName);
private:
    common::ContextPtr context_;
    SceneNodePtr node_;

    std::vector<Point2DFloat> targetPosition_;
};
}
}

#endif //ELFBOX_SPRITE_H
