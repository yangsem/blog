#ifndef __TCP_H
#define __TCP_H

#include <common.h>
#include <json_obj.h>
#include <logger.h>

namespace net
{
    namespace tcp
    {
        enum class EventType
        {
            Connected = 0,
            DisConnect,
            HeadbeatTimeout
        };

        class IConnection
        {
        public:
            virtual ~IConnection() = default;

            virtual bool IsConnect() = 0;
            virtual const char *GetLocalIp() = 0;
            virtual uint16_t GetLocalPort() = 0;
            virtual const char *GetRemoterIp() = 0;
            virtual uint16_t GetRemoterPort() = 0;

            virtual void Lock() = 0;
            virtual void Unlock() = 0;

            virtual int32_t SendMsg(const void *lpData, uint32_t nLength) = 0;
            virtual int32_t Call(const void *lpRequest, uint32_t nReqLength, const void **lpResponse, uint32_t *lpRspLength) = 0;

            virtual const char *GetLastError() = 0;
        };

        class ICallback
        {
        public:
            virtual ~ICallback() = default;

            virtual void OnEvent(IConnection *lpConnection, EventType eType) = 0;

            virtual int32_t OnHeadbeat(IConnection *lpConnection, const void *lpData, uint32_t nLength) = 0;

            virtual int32_t OnGetMsgLength(const void *lpData, uint32_t nLength) = 0;

            virtual int32_t OnMessage(IConnection *lpConnection, const void *lpData, uint32_t nLength) = 0;
        };

        class ITcpClient : public IConnection
        {
        public:
            virtual ~ITcpClient() = default;
            virtual int32_t Init(utility::IJsonObj *lpConfig, ICallback *lpCallback) = 0;
            virtual int32_t Connect() = 0;
            virtual void DisConnect() = 0;
        };

        class ITcpServer
        {
        public:
            virtual ~ITcpServer() = default;
            virtual int32_t Init(utility::IJsonObj *lpConfig, ICallback *lpCallback) = 0;
            virtual int32_t Start() = 0;
            virtual void Stop() = 0;
            virtual void Exit() = 0;
        };

        class ITcpFactory
        {
        public:
            virtual ~ITcpFactory() = default;

            virtual int32_t Init(logger::ILogger *lpLogger) = 0;

            virtual ITcpServer *NewTcpServer() = 0;

            virtual void DeleteTcpServer(ITcpServer *lpTcpServer) = 0;

            virtual ITcpClient *NewTcpClient() = 0;

            virtual void DeleteTcpClient(ITcpClient *lpTcpClient) = 0;
        };
    };
};
#ifdef __cplusplus
extern "C"
{
#endif

    net::tcp::ITcpServer *NewTcpFactory();

    void DeleteTcpFactory(net::tcp::ITcpFactory *lpTcpFactory);

#ifdef __cplusplus
}
#endif

#endif //__TCP_H
