
#ifndef System_IThreadPool
#define System_IThreadPool

#include <vector>
#include <list>
#include <memory>
#include <functional>
#include <mutex>
#include <atomic>
#include <common/IObject.h>
#include <system/detail/Thread.h>

namespace elfbox
{
namespace system
{

struct WorkItem
{
    std::function<void(unsigned)> workFunction_;
    unsigned priority_;
    std::atomic_bool completed_;

    WorkItem() : priority_(0),
                 completed_(false)
    {}
};

typedef std::shared_ptr<WorkItem> WorkItemPtr;

class IThreadPool : public common::IObject
{
ELF_OBJECT(IThreadPool, common::IObject);

public:
    virtual ~IThreadPool() = default;

    virtual void createThreads(unsigned numThreads) = 0;
    virtual WorkItemPtr attach(std::function<void(unsigned)> function, unsigned priority) = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void complete(unsigned priority) = 0;
    virtual void waitForJob(WorkItemPtr item) = 0;
    virtual bool isCompleted(unsigned priority) const = 0;
    virtual bool isPause() = 0;
};

typedef std::shared_ptr<IThreadPool> ThreadPoolPtr;

}
}

#endif
