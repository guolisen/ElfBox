
#ifndef System_ThreadPool
#define System_ThreadPool

#include <vector>
#include <list>
#include <memory>
#include <functional>
#include <mutex>
#include <common/IObject.h>
#include <system/Thread.h>

namespace elfbox
{

struct WorkItem
{
    std::function<void(unsigned)> workFunction_;
    unsigned priority_;
    volatile bool completed_;

    WorkItem(): priority_(0),
        completed_(false) {}
};

typedef std::shared_ptr<WorkItem> WorkItemPtr;

class ThreadPool : public IObject
{
    ELF_OBJECT(ThreadPool, IObject);

public:
    ThreadPool();
    ~ThreadPool();

    void createThreads(unsigned numThreads);
    WorkItemPtr attach(std::function<void(unsigned)> function, unsigned priority);
    void pause();
    void resume();
    void complete(unsigned priority);
    void waitForJob(WorkItemPtr item);

    bool isCompleted(unsigned priority) const;
    bool isPause();

private:
    WorkItemPtr getFreeItem();
    void addWorkItem(WorkItemPtr item);
    void processItems(unsigned threadIndex);

    void cacheProcess();
    void arrangeCache();
    void returnToCache(WorkItemPtr item);

    std::vector<std::shared_ptr<Thread>> threads_;
    std::list<WorkItemPtr> poolItems_;
    std::list<WorkItemPtr> workItems_;
    std::list<WorkItemPtr> queue_;
    std::mutex queueMutex_;
    std::mutex pauseMutex_;
    volatile bool shutDown_;
    volatile bool pausing_;
    bool paused_;
    int tolerance_;
};
}

#endif
