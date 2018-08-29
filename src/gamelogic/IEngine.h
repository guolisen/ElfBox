#ifndef common_IElfBoxEngine
#define common_IElfBoxEngine

#include <common/IObject.h>

namespace elfbox
{
namespace gamelogic
{
class IEngine : public common::IObject
{
ELF_OBJECT(IEngine, common::IObject);
public:
    virtual ~IEngine() = default;

    virtual bool initialize() = 0;
    virtual void run() = 0;
    virtual void start() = 0;
};
}
}
#endif