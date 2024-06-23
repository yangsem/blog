#ifndef __LOGGER_STRING_H
#define __LOGGER_STRING_H

#include <common.h>

class CLoggerString
{
public:
    CLoggerString() =default;
    ~CLoggerString() = default;

    CLoggerString &operator << (const char *lpStr)
    {
        return Append(lpStr);
    }

    CLoggerString& Append(const char *lpStr);

    int32_t Reserve(uint32_t nSize);

private:
    
};

#endif //__LOGGER_STRING_H
