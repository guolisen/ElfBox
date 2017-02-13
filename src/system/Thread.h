#ifndef System_Thread
#define System_Thread

#include <functional>
#include <common/IObject.h>

#ifndef _WIN32
#include <pthread.h>
typedef pthread_t ThreadID;
#else
typedef unsigned ThreadID;
#endif

namespace elfbox
{
namespace system
{
class Thread
{
public:
    Thread(const std::function<void()>& workFunc);
    virtual ~Thread();

    void ThreadFunction();

    bool Run();
    void Stop();
    void SetPriority(int priority);

    bool IsStarted() const { return handle_ != 0; }

    static void SetMainThread();
    static ThreadID GetCurrentThreadID();
    static bool IsMainThread();

protected:
    void* handle_;
    volatile bool shouldRun_;
    const std::function<void()> workFunc_;
    static ThreadID mainThreadID;
};

}
}

#endif
