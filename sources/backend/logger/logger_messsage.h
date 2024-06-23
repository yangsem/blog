#ifndef __LOGGER_MESSAGE_H
#define __LOGGER_MESSAGE_H

#include "common.h"
#include <unordered_map>

namespace logger
{
    class CLoggerMessage
    {
    public:
        CLoggerMessage() = default;
        ~CLoggerMessage() = default;

        int32_t LoadLogMessgae(const char *lpLogMessage = nullptr);

        const char *GetLogMessage(int32_t nErrorNo)
        {
            auto iter = m_umapErrorMsg.find(nErrorNo);
            if (iter == m_umapErrorMsg.end())
            {
                return "Undefined error";
            }
            else
            {
                return iter->second.c_str();
            }
        }

    private:
        std::unordered_map<int32_t, std::string> m_umapErrorMsg;
    };
}
#endif //__LOGGER_MESSAGE_H
