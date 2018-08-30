//
// Created by Lewis on 2018/8/29.
//

#include <gamelogic/processor/SpriteMoveProcess.h>
#include "GameSprite.h"

namespace elfbox
{
namespace gamelogic
{

GameSprite::GameSprite(common::ContextPtr context,
                       scene::SceneNodePtr spriteNode) :
    context_(context), spriteNode_(spriteNode),
    gameDirector_(context_->getComponent<IGameDirector>(nullptr))
{
}

void GameSprite::move(int processLineId, Point2DFloat targetPoint, float speed)
{
    std::shared_ptr<SpriteMoveProcess> moveProcess =
        std::make_shared<SpriteMoveProcess>(context_, spriteNode_);
    moveProcess->move(targetPoint, speed);
    gameDirector_->attach(processLineId, moveProcess);
}

}
}