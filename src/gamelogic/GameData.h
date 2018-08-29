//
// Created by Lewis on 2018/8/27.
//

#ifndef ELFBOX_GAMEDATA_H
#define ELFBOX_GAMEDATA_H

#include <common/IObject.h>
#include <common/Context.h>
#include <gamelogic/IGameData.h>

namespace elfbox
{
namespace gamelogic
{
class GameData : public IGameData
{
ELF_OBJECT(GameData, IGameData);
public:
    GameData(common::ContextPtr context);
    virtual ~GameData() = default;

private:
    common::ContextPtr context_;
};
}
}

#endif //ELFBOX_GAMEDATA_H
