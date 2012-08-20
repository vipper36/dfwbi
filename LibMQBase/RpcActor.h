#ifndef RPCACTOR_H
#define RPCACTOR_H
#include <Theron/Actor.h>
#include <zmq.hpp>
#include "MqUtil.h"
class RpcActor: public Theron::Actor
{

    public:
        struct Parameters
        {
            int timeout;
            std::string mValue;
            zmq::context_t *mContext;
        };
        inline explicit RpcActor(const Parameters address);
        ~RpcActor() {
            delete m_socket;
        }

    void ReqMessageHandler(const IXReqMessage &msg, const Theron::Address from);
    private:
        int m_timeout;
        bool m_isconnect;
        std::string m_cid;
        std::string m_Address;
        zmq::socket_t *m_socket;
        zmq::context_t *m_context;
};

#endif // RPCACTOR_H
