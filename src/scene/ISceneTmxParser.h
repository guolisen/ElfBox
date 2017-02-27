//
// Created by Lewis on 2017/2/26.
//

#ifndef ELFBOX_ISCENETMXPARSER_H
#define ELFBOX_ISCENETMXPARSER_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace scene
{
class ISceneTmxParser : public common::IObject
{
ELF_OBJECT(ISceneTmxParser, common::IObject);
public:
    virtual ~ISceneTmxParser() = default;

};
}
}

#endif //ELFBOX_SCENETMXPARSER_H
