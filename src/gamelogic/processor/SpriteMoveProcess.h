//
// Created by Lewis on 2018/8/29.
//

#ifndef ELFBOX_SPRITEMOVEPROCESS_H
#define ELFBOX_SPRITEMOVEPROCESS_H

#include <common/IObject.h>
#include <common/Context.h>
#include <gamelogic/IGameProcess.h>
#include <gamelogic/scene/ISceneNode.h>

namespace elfbox
{
namespace gamelogic
{
class SpriteMoveProcess : public IGameProcess
{
ELF_OBJECT(SpriteMoveProcess, IGameProcess);
public:
    SpriteMoveProcess(common::ContextPtr context, scene::SceneNodePtr sceneNode);
    virtual ~SpriteMoveProcess() = default;

    virtual void setUp() override;
    virtual void tearDown() override;
    virtual void update(float timeStep) override;
    virtual void kill() override;
    virtual bool isActive() const override {return isActive_;}
    virtual ProcessState getState() const override {return processState_;}

    virtual void move(const Vector2DFloat& moveVector, float walkSpeed);

private:
    common::ContextPtr context_;
    scene::SceneNodePtr sceneNode_;
    bool isActive_;
    Point2DFloat targetPoint_;
    Point2DFloat moveVector_;
    float elapsedTime_;
    float moveStepTime_;
    float moveStepPixel_;
};
}
}

#endif //ELFBOX_SPRITEMOVEPROCESS_H
