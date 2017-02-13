#ifndef System_Detail_Thread
#define System_Detail_Thread

#include <functional>
#include <common/IObject.h>
#include <system/detail/IThread.h>

namespace elfbox
{
namespace system
{
namespace detail
{

class Thread: public IThread
{
ELF_OBJECT(Thread, IThread)
public:
    Thread(const std::function<void()> &workFunc);
    virtual ~Thread();

    void ThreadFunction();

    virtual bool Run();
    virtual void Stop();
    virtual void SetPriority(int priority);

    virtual bool IsStarted() const
    { return handle_ != 0; }

    virtual ThreadID GetCurrentThreadID();
    virtual bool IsMainThread();

protected:
    void *handle_;
    volatile bool shouldRun_;
    const std::function<void()> workFunc_;
    ThreadID mainThreadID_;
};

}
}
}

#endif
