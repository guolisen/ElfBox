#ifndef common_IElfBoxEngine
#define common_IElfBoxEngine

#include <common/IObject.h>

namespace elfbox
{
namespace common
{
class IElfBoxEngine : public IObject
{
ELF_OBJECT(IElfBoxEngine, IObject);
public:
    IElfBoxEngine()
    {};

    virtual ~IElfBoxEngine()
    {};

    virtual bool initialize() = 0;
    virtual void run() = 0;
};
}
}
#endif