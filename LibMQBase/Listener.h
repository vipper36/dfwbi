#ifndef LISTENER_H
#define LISTENER_H
#include <queue>
#include <zmq.hpp>
#include "MqUtil.h"
#include <Theron/Theron.h>
#include <boost/thread/thread.hpp>
#include "MqMessage.h"
#include <map>
#include <Theron/Actor.h>
struct Interval
{
    int value;
};
struct OperSig
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
    void OperHandler(const OperSig &msg, const Theron::Address from);
private:
    bool isStop;
    void listen(const int timeout);
    Theron::ActorRef m_listenInter;
    zmq::pollitem_t *m_items;
    zmq::socket_t *m_olsocket;
    zmq::socket_t *m_ilsocket;
    std::queue<Theron::Address> operList;
};

#endif // LISTENACTOR_H
