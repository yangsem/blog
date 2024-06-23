#include "logger_impl.h"
#include <errorno.h>

namespace logger
{
    static const char *kLogDir = "LogDir";
    static const char *kLogLevel = "LogLevel";
    static const char *kSyncLog = "IsSyncLog";

    static const char *LogLevelStr[] = {"DEBUG", "INFO ", "WARN ", "ERROR", "FATAL", "EVENT"};

    int32_t CLoggerImpl::Init(utility::IJsonObj *lpJsonConfig)
    {
        m_Status.SetStatus(utility::RunningStatus::Status::Init);
        if (lpJsonConfig == nullptr)
        {
            PRINT_WARN("%s", );
            return 0;
        }
        m_lpJsonConfig = lpJsonConfig;
        m_strLogDir = m_lpJsonConfig->GetString(kLogDir, m_strLogDir.c_str());
        m_eLevel = (LogLevel)m_lpJsonConfig->GetInt32(kLogLevel, (int32_t)m_eLevel);
        m_bSyncLog = m_lpJsonConfig->GetBool(kSyncLog, m_bSyncLog);

        try
        {
            m_Status.SetStatus(utility::RunningStatus::Status::Start);
            if (m_bSyncLog)
            {
                m_thLogger = std::thread(&CLoggerImpl::LogRun, this);
            }
        }
        catch(std::exception &e)
        {
            PRINT_ERROR("%s", e.what());
            return PUBLIC_CREATE_THREAD_FAILED;
        }

        m_Status.SetStatus(utility::RunningStatus::Status::Running);
        return 0;
    }

    LogLevel CLoggerImpl::GetLogLevel()
    {
        return m_eLevel;
    }
    
    int32_t CLoggerImpl::SetLogLevel(LogLevel eLevel)
    {
        m_eLevel = eLevel;
    }
    
    int32_t CLoggerImpl::Log(int32_t nErrorNo, LogLevel eLevel, const char **lppParams, bool bPrint = false)
    {

    }

    int32_t logger::CLoggerImpl::LogInternal()
    {

    }

    void logger::CLoggerImpl::LogRun()
    {

    }
}