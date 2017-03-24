//
// Created by Lewis on 2017/3/15.
//

#include "AnimationComponent.h"

namespace elfbox
{
namespace scene
{
namespace component
{

AnimationComponent::AnimationComponent(render::RenderMaterialPtr animationMaterial,
                                       int maxFrame,
                                       int srcImageWidth, int srcImageHeight,
                                       int frameWidth, int frameHeight,
                                       float animationSpeedTime) :
    INodeComponent("Animation"),
    animationMaterial_(animationMaterial),
    currentFrame_(0),
    maxFrame_(maxFrame),
    srcImageWidth_(srcImageWidth),
    srcImageHeight_(srcImageHeight),
    srcFrameWidth_(srcImageWidth / frameWidth),
    srcFrameHeight_(srcImageHeight / frameHeight),
    frameWidth_(frameWidth),
    frameHeight_(frameHeight),
    elapsedTime_(0.0f),
    animationSpeedTime_(animationSpeedTime)
{

}

void AnimationComponent::teardown()
{
    drawable_->getData().material = backupMaterial_;
}

void AnimationComponent::update(float timeStep)
{
    elapsedTime_ += timeStep * 100000;
    if (elapsedTime_ <= animationSpeedTime_)
    {
        return;
    }

    int numFramesToAdvance = (int)(elapsedTime_ / animationSpeedTime_);

    elapsedTime_ -= (numFramesToAdvance * animationSpeedTime_);

    int desiredFrame = currentFrame_ + numFramesToAdvance;

    //if ((false == m_LoopingAnim) && (desiredFrame >= GetFrameCount()))
    //{
    //    desiredFrame = GetFrameCount() - 1;	//Stay on last frame...
    //}

    currentFrame_ = desiredFrame % maxFrame_;

    updateFrame();
}

void AnimationComponent::startup()
{
    backupMaterial_ = drawable_->getData().material;
    drawable_->getData().material = animationMaterial_;
}

void AnimationComponent::updateFrame()
{
    float srcFrameX = (currentFrame_ % srcFrameWidth_) * frameWidth_;
    float srcFrameY = (currentFrame_ / srcFrameWidth_) * frameHeight_;
    RectFloat srcRect = { srcFrameX, srcFrameY, (float)frameWidth_, (float)frameHeight_ };
    drawable_->getData().sourceRect = srcRect;

    Point2DFloat worldCenter = drawable_->getData().worldRect.getCenter();
    RectFloat destRect = {worldCenter.x - frameWidth_ / 2.0f,
        worldCenter.y - frameHeight_ / 2.0f, (float)frameWidth_, (float)frameHeight_ };
    drawable_->getData().worldRect = destRect;
}

}
}
}