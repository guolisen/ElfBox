#ifndef common_IElfBoxEngine
#define common_IElfBoxEngine

#include <common/IObject.h>

namespace elfbox
{
    class IElfBoxEngine :public IObject
    {
        ELF_OBJECT(IElfBoxEngine, IObject);
    public:
        IElfBoxEngine() {};
        virtual ~IElfBoxEngine() {};
        virtual void run() = 0;
    };
}
#endif