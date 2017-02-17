
#ifndef System_ThreadPool
#define System_ThreadPool

#include <vector>
#include <list>
#include <memory>
#include <functional>
#include <mutex>
#include <atomic>

#include <common/IObject.h>
#include <system/IThreadPool.h>
#include <system/detail/Thread.h>

namespace elfbox
{
namespace system
{

class ThreadPool : public IThreadPool
{
ELF_OBJECT(ThreadPool, IThreadPool);

public:
    ThreadPool(detail::IThread::Factory factory);
    virtual ~ThreadPool();

    virtual void createThreads(unsigned numThreads);
    virtual WorkItemPtr attach(std::function<void(unsigned)> function, unsigned priority);
    virtual void pause();
    virtual void resume();
    virtual void complete(unsigned priority);
    virtual void waitForJob(WorkItemPtr item);
    virtual bool isCompleted(unsigned priority) const;
    virtual bool isPause();

private:
    WorkItemPtr getFreeItem();
    void addWorkItem(WorkItemPtr item);
    void processItems(unsigned threadIndex);
    void cacheProcess();
    void arrangeCache();
    void returnToCache(WorkItemPtr item);

    std::vector<std::shared_ptr<detail::IThread>> threads_;
    std::list<WorkItemPtr> poolItems_;
    std::list<WorkItemPtr> workItems_;
    std::list<WorkItemPtr> queue_;
    std::mutex queueMutex_;
    std::mutex pauseMutex_;
    std::atomic<bool> shutDown_;
    std::atomic<bool> paused_;
    int tolerance_;
    detail::IThread::Factory threadFactory_;
};
}
}

#endif
