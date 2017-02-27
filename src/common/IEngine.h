#ifndef common_IElfBoxEngine
#define common_IElfBoxEngine

#include <common/IObject.h>

namespace elfbox
{
namespace common
{
class IEngine : public IObject
{
ELF_OBJECT(IEngine, IObject);
public:
    IEngine()
    {};

    virtual ~IEngine()
    {};

    virtual bool initialize() = 0;
    virtual void run() = 0;
};
}
}
#endif