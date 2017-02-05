#include <memory>

#include <util/LoggerDomain.h>
#include <util/BaseLogger.h>

namespace elfbox
{
    std::string BaseLogger::ToString(const char* formatString, ...)
    {
        char buffer[LOG_BUFFER_SIZE] = { 0 };
       
        va_list args;
        va_start(args, formatString);
        vsnprintf(buffer, LOG_BUFFER_SIZE, formatString, args);
        va_end(args);

        return static_cast<std::string>(buffer);
    }

    void BaseLogger::log(const IObject* obj, LogSeverityLevel level, const std::string& logStr)
    {
        char buffer[LOG_BUFFER_SIZE] = { 0 };
        //TODO: _snprintf is only for Win32
        if (!obj)
        {
            _snprintf(buffer, LOG_BUFFER_SIZE, "[%d][Unknow]: %s\n", (int)level, logStr.c_str());
        }
        else
        {
            _snprintf(buffer, LOG_BUFFER_SIZE, "[%d][%s]: %s\n", (int)level, obj->GetTypeName().c_str(), logStr.c_str());
        }
       
        printf(buffer);
    }
}

