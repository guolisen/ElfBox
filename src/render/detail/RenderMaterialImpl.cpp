//
// Created by Lewis on 2017/2/20.
//

#include "RenderMaterialImpl.h"

namespace elfbox
{
namespace render
{
namespace detail
{
RenderMaterialImpl::RenderMaterialImpl(const std::string fileName) : fileName_(fileName), materialWidth_(0), materialHeight_(0),
                                                             isLoad_(false)
{
}

bool RenderMaterialImpl::LoadMaterial()
{
    if (isLoad_)
        return true;
    isLoad_ = true;

    return true;
}
}
}
}