//
// Created by Lewis on 2018/8/26.
//

#ifndef ELFBOX_IGAMEDATA_H
#define ELFBOX_IGAMEDATA_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace gamelogic
{
class IGameData : public common::IObject
{
ELF_OBJECT(IGameData, common::IObject);
public:
    virtual ~IGameData() = default;

private:
    common::ContextPtr context_;
};

typedef std::shared_ptr<IGameData> GameDataPtr;

}
}

#endif //ELFBOX_IGAMEDATA_H
