#include <windows.h>

#include <system/detail/Thread.h>
#include <system/ThreadPool.h>

namespace elfbox
{
namespace system
{

ThreadPool::ThreadPool(detail::IThread::Factory factory) :
        shutDown_(false),
        paused_(false),
        tolerance_(2),
        threadFactory_(factory)
{
}

ThreadPool::~ThreadPool()
{
    shutDown_ = true;
    resume();

    for (unsigned i = 0; i < threads_.size(); ++i)
        threads_[i]->stop();
}

void ThreadPool::createThreads(unsigned numThreads)
{
    if (!threads_.empty())
        return;

    // Start threads in paused mode
    pause();

    for (unsigned i = 0; i < numThreads; ++i)
    {
        std::shared_ptr<detail::IThread> thread = threadFactory_(
                std::bind(&ThreadPool::processItems, this, i + 1));
        thread->run();
        threads_.push_back(thread);
    }
}

WorkItemPtr ThreadPool::getFreeItem()
{
    if (poolItems_.size() > 0)
    {
        WorkItemPtr item = poolItems_.front();
        poolItems_.pop_front();

        return item;
    }

    return std::make_shared<WorkItem>();
}

void ThreadPool::addWorkItem(WorkItemPtr item)
{
    // Check for duplicate items.
    //assert(!workItems_.Contains(item));
    workItems_.push_back(item);
    item->completed_ = false;

    {
        std::lock_guard<std::mutex> guard(queueMutex_);
        if (queue_.empty())
        {
            queue_.push_back(item);
        } else
        {
            for (std::list<WorkItemPtr>::iterator i = queue_.begin(); i != queue_.end(); ++i)
            {
                if ((*i)->priority_ <= item->priority_)
                {
                    queue_.insert(i, item);
                    break;
                }
            }
        }
    }

    if (threads_.size())
        resume();
}

WorkItemPtr ThreadPool::attach(std::function<void(unsigned)> function, unsigned priority)
{
    auto workItem = getFreeItem();
    workItem->priority_ = -1;
    workItem->workFunction_ = function;
    addWorkItem(workItem);

    return workItem;
}

void ThreadPool::waitForJob(WorkItemPtr item)
{
    while (true)
    {
        if (item->completed_)
            break;
        ::Sleep(1);
    }
}

bool ThreadPool::isPause()
{
    std::lock_guard<std::mutex> guard(pauseMutex_);
    return paused_;
}

void ThreadPool::pause()
{
    std::lock_guard<std::mutex> guard(pauseMutex_);
    if (!paused_)
    {
        paused_ = true;
    }
}

void ThreadPool::resume()
{
    std::lock_guard<std::mutex> guard(pauseMutex_);
    if (paused_)
    {
        paused_ = false;
    }
}

void ThreadPool::complete(unsigned priority)
{
    if (threads_.size())
    {
        resume();

        while (true)
        {
            WorkItemPtr item = nullptr;
            {
                std::lock_guard<std::mutex> guard(queueMutex_);
                if (queue_.empty() || queue_.front()->priority_ < priority)
                    break;

                item = queue_.front();
                queue_.pop_front();
            }

            item->workFunction_(0);
            item->completed_ = true;
        }

        while (!isCompleted(priority))
        {
            ::Sleep(1);
        }

        {
            std::lock_guard<std::mutex> guard(queueMutex_);
            if (queue_.empty())
                pause();
        }
    } else
    {
        // No worker threads: ensure all high-priority items are completed in the main thread
        while (!queue_.empty() && queue_.front()->priority_ >= priority)
        {
            WorkItemPtr item = queue_.front();
            queue_.pop_front();
            item->workFunction_(0);
            item->completed_ = true;
        }
    }

    cacheProcess();
}

bool ThreadPool::isCompleted(unsigned priority) const
{
    for (std::list<WorkItemPtr>::const_iterator i = workItems_.begin(); i != workItems_.end(); ++i)
    {
        if ((*i)->priority_ >= priority && !(*i)->completed_)
            return false;
    }

    return true;
}

void ThreadPool::processItems(unsigned threadIndex)
{
    while (true)
    {
        if (shutDown_)
            return;

        if (isPause())
        {
            ::Sleep(1);
            continue;
        }

        WorkItemPtr item = nullptr;
        {
            std::lock_guard<std::mutex> guard(queueMutex_);
            if (queue_.empty())
            {
                pause();
                continue;
            }

            item = queue_.front();
            queue_.pop_front();
        }

        item->workFunction_(threadIndex);
        item->completed_ = true;
    }
}

void ThreadPool::cacheProcess()
{
    for (std::list<WorkItemPtr>::iterator i = workItems_.begin(); i != workItems_.end();)
    {
        if ((*i)->completed_)
        {
            returnToCache(*i);
            i = workItems_.erase(i);
        } else
            ++i;
    }

    arrangeCache();
}

void ThreadPool::arrangeCache()
{
    unsigned currentSize = poolItems_.size();
    if (currentSize < tolerance_)
        return;

    int overflowSize = currentSize - tolerance_;

    for (unsigned i = 0; poolItems_.size() > 0 && i < (unsigned) overflowSize; i++)
        poolItems_.pop_front();
}

void ThreadPool::returnToCache(WorkItemPtr item)
{
    //item->workFunction_ = 0;
    item->priority_ = -1;
    item->completed_ = false;

    poolItems_.push_back(item);
}

}
}