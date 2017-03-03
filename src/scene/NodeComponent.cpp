//
// Created by Lewis on 2017/3/3.
//

#include "NodeComponent.h"

namespace elfbox
{
namespace scene
{

NodeComponent::NodeComponent(common::ContextPtr context,
                             const std::string& nodeType) :
    context_(context), nodeType_(nodeType)
{
}
}
}