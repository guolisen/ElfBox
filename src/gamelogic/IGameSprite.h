//
// Created by Lewis on 2018/8/29.
//

#ifndef ELFBOX_IGAMESPRITE_H
#define ELFBOX_IGAMESPRITE_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace gamelogic
{
class IGameSprite : public common::IObject
{
ELF_OBJECT(IGameSprite, common::IObject);
public:
    virtual ~IGameSprite() = default;

    virtual void move(int processLineId, float X, float Y, float speed) = 0;
private:
    common::ContextPtr context_;
};

typedef std::shared_ptr<IGameSprite> GameSpritePtr;

}
}

#endif //ELFBOX_IGAMESPRITE_H
