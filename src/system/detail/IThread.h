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
#ifndef _WIN32
#include <pthread.h>
typedef pthread_t ThreadID;
#else
typedef unsigned ThreadID;
#endif

class IThread: public common::IObject
{
    ELF_OBJECT(IThread, common::IObject)
public:
    typedef std::function<std::shared_ptr<IThread>(const std::function<void()>&)> Factory;

    virtual ~IThread() = default;

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
