#ifndef __MQ_LISTEN_ACTOR_H__
#define __MQ_LISTEN_ACTOR_H__
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
class MqListenActor : public OperateActor
{
public:

    inline MqListenActor()
        {
            Factory::TimerFactory *tFactory=Factory::TimerFactory::Instance();
            m_timer=tFactory->CreateTimer();
            m_timer->expires_from_now(boost::posix_time::seconds(5));
            m_timer->async_wait(boost::bind(&MqListenActor::TimerHandler,this,boost::asio::placeholders::error));                
        }
    inline void TimerHandler(const boost::system::error_code& error)
        {
            int sockfd;
            amqp_connection_state_t conn;
            amqp_bytes_t queuename;
            amqp_bytes_t empty_bytes;
            empty_bytes.len=0;
            empty_bytes.bytes=NULL;
            amqp_table_t empty_table;
            empty_table.num_entries=-3;
            empty_table.entries=NULL;
            int port=atoi(attMap["port"].c_str());
            conn = amqp_new_connection();
            
            sockfd = amqp_open_socket(attMap["host"].c_str(), port);
            
            if(sockfd<0)
                return;
            amqp_set_sockfd(conn, sockfd);
            
            amqp_rpc_reply_t logRep=amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest");

            if(logRep.reply_type!=AMQP_RESPONSE_NORMAL)
            {
                return;
            }
            amqp_channel_open(conn, 1);
            
            amqp_rpc_reply_t rpcRep=amqp_get_rpc_reply(conn);
            if(rpcRep.reply_type!=AMQP_RESPONSE_NORMAL)
            {
                return;
            }
            
            amqp_queue_declare_ok_t *r = amqp_queue_declare(conn,1,empty_bytes,0,0,0,1,empty_table);
            rpcRep=amqp_get_rpc_reply(conn);
            if(rpcRep.reply_type!=AMQP_RESPONSE_NORMAL)
            {
                return;
            }
            queuename = amqp_bytes_malloc_dup(r->queue);
            if (queuename.bytes == NULL) {
                return;
            }
            amqp_queue_bind(conn, 
                            1, 
                            queuename, 
                            amqp_cstring_bytes(attMap["exchange"].c_str()), 
                            amqp_cstring_bytes(attMap["key"].c_str()),
                            empty_table);
            rpcRep=amqp_get_rpc_reply(conn);
            if(rpcRep.reply_type!=AMQP_RESPONSE_NORMAL)
            {
                return;
            }
            amqp_basic_consume(conn, 1, queuename, empty_bytes, 0, 1, 0, empty_table);
            rpcRep=amqp_get_rpc_reply(conn);
            if(rpcRep.reply_type!=AMQP_RESPONSE_NORMAL)
            {
                return;
            }
            amqp_frame_t frame;
            int result;
            
            amqp_basic_properties_t *p;
            size_t body_target;
            size_t body_received;

            while (1) {
                amqp_maybe_release_buffers(conn);
                result = amqp_simple_wait_frame(conn, &frame);
                if (result < 0)
                    break;
                if (frame.frame_type != AMQP_FRAME_METHOD)
                    continue;
                
                if (frame.payload.method.id != AMQP_BASIC_DELIVER_METHOD)
                    continue;

                result = amqp_simple_wait_frame(conn, &frame);
                if (result < 0)
                    break;

                if (frame.frame_type != AMQP_FRAME_HEADER) {
                    break;
                }
                body_target = frame.payload.properties.body_size;
                body_received = 0;
                std::stringstream ss;
                while (body_received < body_target) {
                    result = amqp_simple_wait_frame(conn, &frame);
                    if (result < 0)
                        break;

                    if (frame.frame_type != AMQP_FRAME_BODY) {
                        break;
                    }
                    body_received += frame.payload.body_fragment.len;
                    ss.write((const char*)frame.payload.body_fragment.bytes,
                             frame.payload.body_fragment.len);
                }
                stock::StockPrice *stock=new stock::StockPrice();
                boost::archive::xml_iarchive ia(ss);
                ia >> BOOST_SERIALIZATION_NVP(*stock);
                
                StockMessage stockprice(stock);
                Send(stockprice, parent);
            }
         
            amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);
            amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
            amqp_destroy_connection(conn);
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
private:
    std::map<std::string,std::string> attMap;
    boost::asio::deadline_timer* m_timer;
}; 
#endif
