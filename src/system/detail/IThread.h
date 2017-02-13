#ifndef System_Detail_IThread
#define System_Detail_IThread

#include <functional>
#include <common/IObject.h>

namespace elfbox
{
namespace system
{
namespace detail
{
class IThread
{
public:
    virtual ~IThread();

    virtual bool Run() = 0;
    virtual void Stop() = 0;
    virtual void SetPriority(int priority) = 0;

    virtual bool IsStarted() const = 0;

    virtual ThreadID GetCurrentThreadID() = 0;
    virtual bool IsMainThread() = 0;
};

}
}
}

#endif
