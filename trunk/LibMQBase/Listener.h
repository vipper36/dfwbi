#ifndef LISTENER_H
#define LISTENER_H
#include <queue>
#include <zmq.hpp>
#include "MqUtil.h"
#include <Theron/Framework.h>
#include <Theron/Actor.h>
#include <boost/thread/thread.hpp>
#include "MqMessage.h"
#include <map>
#include <Theron/Actor.h>
struct Interval
{
    int value;
};
class Listener:public Theron::Actor
{
public:
    struct Parameters
        {
            Theron::ActorRef listenInter;
            std::string interAdd;
            std::string outerAdd;
            int outerType;
            bool outerBind;
        };
    Listener(Parameters params);
    ~Listener();
    void LoopHandler(const Interval &msg, const Theron::Address from);
private:
    void listen(const int timeout);
    Theron::ActorRef m_listenInter;
    zmq::pollitem_t *m_items;
    zmq::socket_t *m_olsocket;
    zmq::socket_t *m_ilsocket;
};

#endif // LISTENACTOR_H
