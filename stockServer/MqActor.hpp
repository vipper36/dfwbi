#ifndef __MQ_ACTOR_H__
#define __MQ_ACTOR_H__
#include <Theron/Actor.h>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "Messages.hpp"
#include <iostream>
#include <sstream>
#include "OperateActor.hpp"
#include <amqp.h>
#include <amqp_framing.h>

// A trivial actor that does nothing.
class MqActor : public OperateActor
{
public:

    inline MqActor()
        {
            RegisterHandler(this, &MqActor::StockHandler);
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {
            Send(OperateMessage(OperateMessage::STATUS,"ok"), from);
        }
    void MapHandler(const MapMessage &message, const Theron::Address from)
        {
            if(message.type==MapMessage::ATTR)
            {
                attMap=message.map;
            }
        }
    void StockHandler(const StockMessage &message, const Theron::Address from)
        {
            int sockfd;
            amqp_connection_state_t conn;

            stock::StockPrice stock=*message.rp;
            delete message.rp;
            std::stringstream ss;
            boost::archive::xml_oarchive oa(ss);
            oa << BOOST_SERIALIZATION_NVP(stock);
            
            
            int port=atoi(attMap["port"].c_str());
            conn = amqp_new_connection();
            
            sockfd = amqp_open_socket(attMap["host"].c_str(), port);
            
            if(sockfd<0)
                return;
            amqp_set_sockfd(conn, sockfd);
            
            amqp_rpc_reply_t logRep=amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest");

            if(logRep.reply_type==AMQP_RESPONSE_NORMAL)
            {
                amqp_channel_open(conn, 1);

                amqp_rpc_reply_t rpcRep=amqp_get_rpc_reply(conn);
                if(rpcRep.reply_type==AMQP_RESPONSE_NORMAL)
                {
                    amqp_basic_properties_t props;
                    props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
                    props.content_type = amqp_cstring_bytes("text/plain");
                    props.delivery_mode = 2; // persistent delivery mode
                    int ret=amqp_basic_publish(conn,
                                               1,
                                               amqp_cstring_bytes(attMap["exchange"].c_str()),
                                               amqp_cstring_bytes(attMap["key"].c_str()),
                                               0,
                                               0,
                                               &props,
                                               amqp_cstring_bytes(ss.str().c_str()));
                }
         
                amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);
                amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
                amqp_destroy_connection(conn);
            }
        }
private:
    std::map<std::string,std::string> attMap;
}; 
#endif
