#ifndef util_BaseLogger
#define util_BaseLogger

#include <memory>
#include <cstdio>
#include <stdio.h>
#include <stdarg.h>

#include <common/IObject.h>
#include <util/LoggerDomain.h>

#define ELFBOX_LOGGING

namespace elfbox
{
    const int LOG_BUFFER_SIZE = 2048;

    enum LogSeverityLevel
    {
        LogSeverityLevel_Trace = 0,
        LogSeverityLevel_Debug = 1,
        LogSeverityLevel_Info = 2,
        LogSeverityLevel_Warning = 3,
        LogSeverityLevel_Error = 4,
        LogSeverityLevel_Vip = 5,
        LogSeverityLevel_UserDebug = 6,
        LogSeverityLevel_Invalid = 7
    };

    class ILogger
    {
    public:
        virtual ~ILogger() = default;

        virtual void log(LogSeverityLevel level, const std::string& logStr) = 0;
    };

    class BaseLogger: public ILogger
    {
    public:
        explicit BaseLogger(const IObject* obj) : obj_(obj) {};
        virtual ~BaseLogger() = default;

        static std::string ToString(const char* formatString, ...);
        virtual void log(LogSeverityLevel level, const std::string& logStr);
    private:
        const IObject* obj_;
    };

    typedef std::shared_ptr<ILogger> LoggerPtr;
}

#ifdef ELFBOX_LOGGING
#define ELFBOX_LOGTRACE(logObjPtr, format, ...) logObjPtr->log(LogSeverityLevel_Trace, BaseLogger::ToString(format, ##__VA_ARGS__))
#define ELFBOX_LOGDEBUG(logObjPtr, format, ...) logObjPtr->log(LogSeverityLevel_Debug, BaseLogger::ToString(format, ##__VA_ARGS__))
#define ELFBOX_LOGINFO(logObjPtr, format, ...) logObjPtr->log(LogSeverityLevel_Info, BaseLogger::ToString(format, ##__VA_ARGS__))
#define ELFBOX_LOGWARNING(logObjPtr, format, ...) logObjPtr->log(LogSeverityLevel_Warning, BaseLogger::ToString(format, ##__VA_ARGS__))
#define ELFBOX_LOGERROR(logObjPtr, format, ...) logObjPtr->log(LogSeverityLevel_Error, BaseLogger::ToString(format, ##__VA_ARGS__))
#define ELFBOX_LOGVIP(logObjPtr, format, ...) logObjPtr->log(LogSeverityLevel_Vip, BaseLogger::ToString(format, ##__VA_ARGS__))
#define ELFBOX_LOGUSERDEBUG(logObjPtr, format, ...) logObjPtr->log(LogSeverityLevel_UserDebug, BaseLogger::ToString(format, ##__VA_ARGS__))
#else
#define ELFBOX_LOGTRACE(...) ((void)0)
#define ELFBOX_LOGDEBUG(...) ((void)0)
#define ELFBOX_LOGINFO(...) ((void)0)
#define ELFBOX_LOGWARNING(...) ((void)0)
#define ELFBOX_LOGERROR(...) ((void)0)
#define ELFBOX_LOGVIP(...) ((void)0)
#define ELFBOX_LOGUSERDEBUG(...) ((void)0)
#endif

#endif