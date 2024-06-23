#ifndef __LOGGER_H
#define __LOGGER_H

#include <common.h>
#include <json_obj.h>
#include <running_status.h>

namespace logger
{
    enum class LogLevel
    {
        DEBUG = 0,
        INFO,
        WARN,
        ERROR,
        FATAL,
        EVENT
    };

    class ILogger
    {
    public:
        /**
         * 虚析构函数
         */
        virtual ~ILogger() = default;

        virtual int32_t Init(utility::IJsonObj *lpJsonConfig) = 0;

        /**
         * @brief 获取日志等级
         *
         * @return 返回日志对象当前的日志等级
         */
        virtual LogLevel GetLogLevel() = 0;

        /**
         * @brief 设置日志等级，任何时期都允许
         * @param[in] eLevel 输出的最低日志等级
         * @return 成功返回0，否则失败
         */
        virtual int32_t SetLogLevel(LogLevel eLevel) = 0;

        /**
         * @brief 写日志接口
         * @param[in] nErrorNo 错误号
         * @param[in] eLevel 错误等级
         * @param[in] lppParams 日志填充参数或额外字符串参数数组，以nullptr结尾
         * @param[in] bPrint 是否打印终端，默认不打印
         * @return 成功返回0，否则失败
         */
        virtual int32_t Log(int32_t nErrorNo, LogLevel eLevel, const char **lppParams, bool bPrint = false) = 0;
    };

    class CLoggerWrap
    {
    public:
        CLoggerWrap() = default;
        ~CLoggerWrap() = default;

        void Init(ILogger *lpLogger, const char *lpOwner)
        {
            m_lpLogger = lpLogger;
            m_lpOwner = lpOwner;
        }

        void SetPhase(utility::RunningStatus::Status eStatus)
        {
            m_Phase.SetStatus(eStatus);
        }

        const char *GetPhaseStr()
        {
            return m_Phase.GetCurStatusStr();
        }

        const char *GetOwner()
        {
            return m_lpOwner;
        }

        int32_t Log(int32_t nErrorNo, LogLevel eLevel, const char **lppParams)
        {
            if (likely(m_lpLogger != nullptr && m_lpLogger->GetLogLevel() >= eLevel))
            {
                auto bPrint = m_Phase.GetStatus() != utility::RunningStatus::Status::Running;
                return m_lpLogger->Log(nErrorNo, eLevel, lppParams, bPrint);
            }

            return 0;
        }

    private:
        ILogger *m_lpLogger{nullptr};
        const char *m_lpOwner{""};
        utility::RunningStatus m_Phase;
    };

#define LOG_BASE(nErrorNo, eLevel, ...)                                                                              \
    do                                                                                                               \
    {                                                                                                                \
        const char *params[] = {##__VA_ARGS__, m_loggerWrap.GetPhaseStr(), m_loggerWrap.GetOwner(), __POSION, NULL}; \
        m_loggerWrap->log(nErrorNo, eLevel, params);                                                                 \
    } while (0)

#define LOG_DEBUG(nErrorNo, ...) LOG_BASE(nErrorNo, utility::logger::LogLevel::DEBUG, ##__VA_ARGS__)
#define LOG_INFO(nErrorNo, ...) LOG_BASE(nErrorNo, utility::logger::LogLevel::INFO, ##__VA_ARGS__)
#define LOG_WARN(nErrorNo, ...) LOG_BASE(nErrorNo, utility::logger::LogLevel::WARN, ##__VA_ARGS__)
#define LOG_ERROR(nErrorNo, ...) LOG_BASE(nErrorNo, utility::logger::LogLevel::ERROR, ##__VA_ARGS__)
#define LOG_FATAL(nErrorNo, ...) LOG_BASE(nErrorNo, utility::logger::LogLevel::FATAL, ##__VA_ARGS__)
#define LOG_EVENT(nErrorNo, ...) LOG_BASE(nErrorNo, utility::logger::LogLevel::EVENT, ##__VA_ARGS__)
}

#ifdef __cplusplus
extern "C"
{
#endif

    logger::ILogger *NewLogger();

    void DeleteLogger(logger::ILogger *lpLogger);

#ifdef __cplusplus
}
#endif

#endif //__LOGGER_H
