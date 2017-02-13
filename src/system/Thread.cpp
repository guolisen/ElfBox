#include <system/Thread.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

namespace elfbox
{
namespace system
{
#ifdef _WIN32

DWORD WINAPI ThreadFunctionStatic(void* data)
{
    Thread* thread = static_cast<Thread*>(data);
    thread->ThreadFunction();
    return 0;
}

#else

void *ThreadFunctionStatic(void *data)
{
    Thread *thread = static_cast<Thread *>(data);
    thread->ThreadFunction();
    pthread_exit((void *) 0);
    return 0;
}

#endif

ThreadID Thread::mainThreadID;

Thread::Thread(const std::function<void()> &workFunc) :
        handle_(0),
        shouldRun_(false),
        workFunc_(workFunc)
{
}

Thread::~Thread()
{
    Stop();
}

void Thread::ThreadFunction()
{
    workFunc_();
}

bool Thread::Run()
{
    if (handle_)
        return false;

    shouldRun_ = true;
#ifdef _WIN32
    handle_ = CreateThread(0, 0, ThreadFunctionStatic, this, 0, 0);
#else
    handle_ = new pthread_t;
    pthread_attr_t type;
    pthread_attr_init(&type);
    pthread_attr_setdetachstate(&type, PTHREAD_CREATE_JOINABLE);
    pthread_create((pthread_t *) handle_, &type, ThreadFunctionStatic, this);
#endif
    return handle_ != 0;
}

void Thread::Stop()
{
    if (!handle_)
        return;

    shouldRun_ = false;
#ifdef _WIN32
    WaitForSingleObject((HANDLE)handle_, INFINITE);
    CloseHandle((HANDLE)handle_);
#else
    pthread_t *thread = (pthread_t *) handle_;
    if (thread)
        pthread_join(*thread, 0);
    delete thread;
#endif
    handle_ = 0;
}

void Thread::SetPriority(int priority)
{
#ifdef _WIN32
    if (handle_)
        SetThreadPriority((HANDLE)handle_, priority);
#endif
#if defined(__linux__) && !defined(__ANDROID__) && !defined(__EMSCRIPTEN__)
    pthread_t* thread = (pthread_t*)handle_;
    if (thread)
        pthread_setschedprio(*thread, priority);
#endif
}

void Thread::SetMainThread()
{
    mainThreadID = GetCurrentThreadID();
}

ThreadID Thread::GetCurrentThreadID()
{
#ifdef _WIN32
    return GetCurrentThreadId();
#else
    return pthread_self();
#endif
}

bool Thread::IsMainThread()
{
    return GetCurrentThreadID() == mainThreadID;
}

}
}

