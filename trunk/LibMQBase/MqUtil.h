#ifndef MQUTIL_H
#define MQUTIL_H
#include <zmq.hpp>
#include <list>
#include "MqMessage.h"
class MqUtil{
    public:
    static bool SendMqMessage(zmq::socket_t *socket,const MqMessage &msg);

    static BaseMqMessage RecvMqMessage(zmq::socket_t *socket);
};
#endif // MQUTIL_H
