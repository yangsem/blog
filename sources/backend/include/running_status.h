#ifndef __RUN_STATUS_H
#define __RUN_STATUS_H

namespace utility
{
    class RunningStatus
    {
    public:
        enum class Status
        {
            Init = 0,
            Start,
            Running,
            Stop,
            Exit,
            Pause,

            InitFail,
            StartFail
        };

    public:
        void SetStatus(Status eStatus)
        {
            m_eStatus = eStatus;
        }

        Status GetStatus()
        {
            return m_eStatus;
        }

        bool IsRunning()
        {
            return m_eStatus == Status::Start || m_eStatus == Status::Running;
        }

        bool IsPause()
        {
            return m_eStatus == Status::Pause;
        }

        const char *GetCurStatusStr()
        {
            static const char *StatusStr[] = {"Init", "Start", "Running", "Stop", "Exit", "Pause", "InitFail", "StartFail"};
            return StatusStr[(int)m_eStatus];
        }

    private:
        Status m_eStatus{Status::Running};
    };
}
#endif // __RUN_STATUS_H
