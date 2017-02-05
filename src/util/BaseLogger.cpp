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

    void BaseLogger::log(LogSeverityLevel level, const std::string& logStr)
    {
        char buffer[LOG_BUFFER_SIZE] = { 0 };
        
        if (!obj_)
        {
            _snprintf(buffer, LOG_BUFFER_SIZE, "[%d][Unknow]: %s\n", (int)level, logStr.c_str());
        }
        else
        {
            _snprintf(buffer, LOG_BUFFER_SIZE, "[%d][%s]: %s\n", (int)level, obj_->GetTypeName().c_str(), logStr.c_str());
        }
       
        printf(buffer);
    }
}

