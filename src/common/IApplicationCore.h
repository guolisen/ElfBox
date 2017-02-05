#ifndef common_IApplicationCore
#define common_IApplicationCore

#include <common/IObject.h>

namespace elfbox
{
    class IApplicationCore : public IObject
    {
        ELF_OBJECT(IApplicationCore, IObject);
    public:
        IApplicationCore() = default;
        virtual ~IApplicationCore() = default;

        virtual bool setup() = 0;
        virtual bool start() = 0;
        virtual bool terminat() = 0;

    };
}
#endif