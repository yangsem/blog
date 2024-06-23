#ifndef __LOGGER_IMPL_H
#define __LOGGER_IMPL_H

#include <logger.h>
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace logger
{
    class CLoggerImpl : public ILogger
    {
    public:
        CLoggerImpl() = default;
        ~CLoggerImpl() override = default;

        int32_t Init(utility::IJsonObj *lpJsonConfig) override;
        LogLevel GetLogLevel() override;
        int32_t SetLogLevel(LogLevel eLevel) override;
        int32_t Log(int32_t nErrorNo, LogLevel eLevel, const char **lppParams, bool bPrint = false) override;

    private:
        int32_t LogInternal();
        void LogRun();

    private:
        utility::IJsonObj *m_lpJsonConfig{nullptr};
        LogLevel m_eLevel{LogLevel::INFO};
        std::string m_strLogDir{"./log"};
        int32_t m_nQueueSize{10240};
        bool m_bSyncLog{false};

        utility::RunningStatus m_Status;
        std::thread m_thLogger;
        std::mutex m_lockQueue;
        std::condition_variable m_condQueue;
        std::queue<const char *> m_logQueue;
    };
}

#endif //__LOGGER_IMPL_H
