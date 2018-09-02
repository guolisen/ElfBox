//
// Created by Lewis on 2017/3/15.
//

#ifndef ELFBOX_ANIMATIONCOMPONENT_H
#define ELFBOX_ANIMATIONCOMPONENT_H

#include <vector>
#include <common/IObject.h>
#include <common/Context.h>

#include "gamelogic/scene/IAnimation.h"
#include <render/IRenderMaterial.h>

namespace elfbox
{
namespace scene
{
namespace animation
{

class NodeAnimation : public IAnimation
{
ELF_OBJECT(NodeAnimation, common::IObject);
public:
    NodeAnimation(render::RenderMaterialPtr animationMaterial,
                       std::vector<RectFloat>&& frameVec,
                       int maxFrame,
                       int srcImageWidth, int srcImageHeight,
                       int frameWidth, int frameHeight,
                       float animationSpeedTime);
    virtual ~NodeAnimation() = default;

    virtual void startup();
    virtual void update(float timeStep);
    virtual void teardown();

    virtual void setCurrentFrame(int currentFrame)
    {
        currentFrame_ = currentFrame;
    }

    virtual void setMaxFrame(int maxFrame)
    {
        maxFrame_ = maxFrame;
    }

    virtual void setFrameWidth(int frameWidth)
    {
        frameWidth_ = frameWidth;
    }

    virtual void setFrameHeight(int frameHeight)
    {
        frameHeight_ = frameHeight;
    }

    virtual void setElapsedTime(float elapsedTime)
    {
        elapsedTime_ = elapsedTime;
    }

    virtual void setAnimationSpeedTime(float animationSpeedTime)
    {
        animationSpeedTime_ = animationSpeedTime;
    }

    virtual void setSrcImageWidth(int srcImageWidth)
    {
        srcImageWidth_ = srcImageWidth;
    }

    virtual void setSrcImageHeight(int srcImageHeight)
    {
        srcImageHeight_ = srcImageHeight;
    }

private:
    void updateFrame();

    render::RenderMaterialPtr animationMaterial_;
    render::RenderMaterialPtr backupMaterial_;
    std::vector<RectFloat> frameVec_;
    int currentFrame_;
    int maxFrame_;
    int srcImageWidth_;
    int srcImageHeight_;
    int srcFrameWidth_;
    int srcFrameHeight_;
    int frameWidth_;
    int frameHeight_;
    float elapsedTime_;
    float animationSpeedTime_;
};
}
}
}
#endif //ELFBOX_ANIMATIONCOMPONENT_H
