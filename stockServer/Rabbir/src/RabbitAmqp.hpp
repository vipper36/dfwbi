#ifndef __RABBIT_AMQP_H__
#define __RABBIT_AMQP_H__
#include <amqp.h>
#include <amqp_framing.h>
namespace AMQP
{
    class RabbitClient
    {
    public:
        RabbitClient():isConnect(false)
            {
            }
        RabbitClient(std::string host,int port)
            :isConnect(false)
            {
                Connect(host,port);
            }
        bool Connect(std::string host,int port)
            {
                if(!isConnect)
                {
                    conn = amqp_new_connection();
            
                    int sockfd = amqp_open_socket(host.c_str(), port);
                    
                    if(sockfd<0)
                        return false;
                    amqp_set_sockfd(conn, sockfd);
                    
                    amqp_rpc_reply_t logRep=amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest");
                    
                    if(logRep.reply_type!=AMQP_RESPONSE_NORMAL)
                    {
                        return false;
                    }
                    amqp_channel_open(conn, 1);
                        
                    amqp_rpc_reply_t rpcRep=amqp_get_rpc_reply(conn);
                    if(rpcRep.reply_type!=AMQP_RESPONSE_NORMAL)
                    {
                        return false;
                    }
                    isConnect=true;
                }
                return true;
            }
        bool Send(std::string msg,std::string exchange,std::string key)
            {
                if(isConnect)
                {
                    amqp_bytes_t tExch;
                    if(exchange.length()>0)
                    {
                        tExch=amqp_cstring_bytes(exchange.c_str());
                    }else
                    {
                        tExch.len=0;
                        tExch.bytes=NULL;
                    } 
                    amqp_basic_properties_t props;
                    props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
                    props.content_type = amqp_cstring_bytes("text/plain");
                    props.delivery_mode = 2; // persistent delivery mode
                    int ret=amqp_basic_publish(conn,
                                               1,
                                               tExch,
                                               amqp_cstring_bytes(key.c_str()),
                                               0,
                                               0,
                                               &props,
                                               amqp_cstring_bytes(msg.c_str()));
                    return true;
                }else
                {
                    return false;
                }
            }
        bool DeclareExchange(std::string exchange,std::string type)
            {
                if(isConnect)
                {
                    amqp_table_t empty_table;
                    empty_table.num_entries=-3;
                    empty_table.entries=NULL;
                    amqp_exchange_declare(conn, 1, amqp_cstring_bytes(exchange.c_str()), amqp_cstring_bytes(type.c_str()),
                                          0, 0, empty_table);
                    amqp_rpc_reply_t rpcRep=amqp_get_rpc_reply(conn);
                    if(rpcRep.reply_type==AMQP_RESPONSE_NORMAL)
                    {
                        return true;
                    }
                }
                return false;
            }
        bool DeclareQueue(std::string queue)
            {
                if(isConnect)
                {
                    amqp_table_t empty_table;
                    empty_table.num_entries=-3;
                    empty_table.entries=NULL;
                    amqp_queue_declare(conn, 1, amqp_cstring_bytes(queue.c_str()), 0, 0, 0, 0,
						    empty_table);
                    amqp_rpc_reply_t rpcRep=amqp_get_rpc_reply(conn);
                    if(rpcRep.reply_type==AMQP_RESPONSE_NORMAL)
                    {
                        return true;
                    }
                }
                return false;
            }
        bool BindQueue(std::string exchange,std::string key,std::string queue)
            {
                if(isConnect)
                {
                    amqp_table_t empty_table;
                    empty_table.num_entries=-3;
                    empty_table.entries=NULL;
                    amqp_queue_bind(conn, 
                                    1, 
                                    amqp_cstring_bytes(queue.c_str()), 
                                    amqp_cstring_bytes(exchange.c_str()), 
                                    amqp_cstring_bytes(key.c_str()),
                                    empty_table);
                    amqp_rpc_reply_t rpcRep=amqp_get_rpc_reply(conn);
                    if(rpcRep.reply_type==AMQP_RESPONSE_NORMAL)
                    {
                        return true;
                    }
                }
                return false;
            }
        std::string Recv(std::string queue)
            {
                if(isConnect)
                {
                    amqp_bytes_t empty_bytes;
                    empty_bytes.len=0;
                    empty_bytes.bytes=NULL;
                    amqp_table_t empty_table;
                    empty_table.num_entries=-3;
                    empty_table.entries=NULL;
                    amqp_bytes_t queuename=amqp_cstring_bytes(queue.c_str()); 

                    amqp_basic_consume(conn, 1, queuename, empty_bytes, 0, 1, 0, empty_table);
                    amqp_rpc_reply_t rpcRep=amqp_get_rpc_reply(conn);
                    if(rpcRep.reply_type!=AMQP_RESPONSE_NORMAL)
                    {
                        return std::string("");
                    }
                    amqp_frame_t frame;
                    int result;
            
                    amqp_basic_properties_t *p;
                    size_t body_target;
                    size_t body_received;
                
                    amqp_maybe_release_buffers(conn);
                    result = amqp_simple_wait_frame(conn, &frame);
                    if (result < 0)
                        return std::string("");
                    if (frame.frame_type != AMQP_FRAME_METHOD)
                        return std::string("");
                
                    if (frame.payload.method.id != AMQP_BASIC_DELIVER_METHOD)
                        return std::string("");
                
                    result = amqp_simple_wait_frame(conn, &frame);
                    if (result < 0)
                        return std::string("");
                
                    if (frame.frame_type != AMQP_FRAME_HEADER) {
                        return std::string("");
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
                    return ss.str();
                }
                return std::string("");
            }
        std::string Recv(std::string exchange,std::string key)
            {
                if(isConnect)
                {
                    amqp_bytes_t empty_bytes;
                    empty_bytes.len=0;
                    empty_bytes.bytes=NULL;
                    amqp_table_t empty_table;
                    empty_table.num_entries=-3;
                    empty_table.entries=NULL;
                    amqp_bytes_t queuename;
                    amqp_queue_declare_ok_t *r = amqp_queue_declare(conn,1,empty_bytes,0,0,0,1,empty_table);
                    amqp_rpc_reply_t rpcRep=amqp_get_rpc_reply(conn);
                    if(rpcRep.reply_type!=AMQP_RESPONSE_NORMAL)
                    {
                        return std::string("");
                    }
                    queuename = amqp_bytes_malloc_dup(r->queue);
                    if (queuename.bytes == NULL) {
                        return std::string("");
                    }
                    amqp_queue_bind(conn, 
                                    1, 
                                    queuename, 
                                    amqp_cstring_bytes(exchange.c_str()), 
                                    amqp_cstring_bytes(key.c_str()),
                                    empty_table);
                    rpcRep=amqp_get_rpc_reply(conn);
                    if(rpcRep.reply_type!=AMQP_RESPONSE_NORMAL)
                    {
                        return std::string("");
                    }
                    amqp_basic_consume(conn, 1, queuename, empty_bytes, 0, 1, 0, empty_table);
                    rpcRep=amqp_get_rpc_reply(conn);
                    if(rpcRep.reply_type!=AMQP_RESPONSE_NORMAL)
                    {
                        return std::string("");
                    }
                    amqp_frame_t frame;
                    int result;
            
                    amqp_basic_properties_t *p;
                    size_t body_target;
                    size_t body_received;
                
                    amqp_maybe_release_buffers(conn);
                    result = amqp_simple_wait_frame(conn, &frame);
                    if (result < 0)
                        return std::string("");
                    if (frame.frame_type != AMQP_FRAME_METHOD)
                        return std::string("");
                
                    if (frame.payload.method.id != AMQP_BASIC_DELIVER_METHOD)
                        return std::string("");
                
                    result = amqp_simple_wait_frame(conn, &frame);
                    if (result < 0)
                        return std::string("");
                
                    if (frame.frame_type != AMQP_FRAME_HEADER) {
                        return std::string("");
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
                    return ss.str();
                }
                return std::string("");
            }
        template<class Function>
        bool Listen(std::string exchange,std::string key,Function f)
            {
                if(isConnect)
                {
                    amqp_bytes_t empty_bytes;
                    empty_bytes.len=0;
                    empty_bytes.bytes=NULL;
                    amqp_table_t empty_table;
                    empty_table.num_entries=-3;
                    empty_table.entries=NULL;
                    amqp_queue_declare_ok_t *r = amqp_queue_declare(conn,1,empty_bytes,0,0,0,1,empty_table);
                    amqp_rpc_reply_t rpcRep=amqp_get_rpc_reply(conn);
                    if(rpcRep.reply_type!=AMQP_RESPONSE_NORMAL)
                    {
                        return false;
                    }
                    amqp_bytes_t queuename = amqp_bytes_malloc_dup(r->queue);
                    if (queuename.bytes == NULL) {
                        return false;
                    }
                    amqp_queue_bind(conn, 
                                    1, 
                                    queuename, 
                                    amqp_cstring_bytes(exchange.c_str()), 
                                    amqp_cstring_bytes(key.c_str()),
                                    empty_table);
                    rpcRep=amqp_get_rpc_reply(conn);
                    if(rpcRep.reply_type!=AMQP_RESPONSE_NORMAL)
                    {
                        return false;
                    }
                    amqp_basic_consume(conn, 1, queuename, empty_bytes, 0, 1, 0, empty_table);
                    rpcRep=amqp_get_rpc_reply(conn);
                    if(rpcRep.reply_type!=AMQP_RESPONSE_NORMAL)
                    {
                        return false;
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
                        p = (amqp_basic_properties_t *) frame.payload.properties.decoded;

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
                        f(ss.str(),p);
                    }
                }
                return false;
            }
        std::string RpcCall(std::string msg,std::string exchange,std::string key)
            {
                if(isConnect)
                {
                    amqp_bytes_t empty_bytes;
                    empty_bytes.len=0;
                    empty_bytes.bytes=NULL;
                    amqp_table_t empty_table;
                    empty_table.num_entries=-3;
                    empty_table.entries=NULL;
                    amqp_queue_declare_ok_t *r = amqp_queue_declare(conn,1,empty_bytes,0,0,0,1,empty_table);
                    amqp_rpc_reply_t rpcRep=amqp_get_rpc_reply(conn);
                    if(rpcRep.reply_type!=AMQP_RESPONSE_NORMAL)
                    {
                        return std::string("");
                    }
                    amqp_bytes_t queuename = amqp_bytes_malloc_dup(r->queue);
                    if (queuename.bytes == NULL) {
                        return std::string("");
                    }
                    amqp_basic_properties_t props;
                    props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG|AMQP_BASIC_REPLY_TO_FLAG;
                    props.content_type = amqp_cstring_bytes("text/plain");
                    props.delivery_mode = 2; // persistent delivery mode
                    props.reply_to=queuename;

                    int ret=amqp_basic_publish(conn,
                                               1,
                                               amqp_cstring_bytes(exchange.c_str()),
                                               amqp_cstring_bytes(key.c_str()),
                                               0,
                                               0,
                                               &props,
                                               amqp_cstring_bytes(msg.c_str()));
                    
                    
                    amqp_basic_consume(conn, 1, queuename, empty_bytes, 0, 1, 0, empty_table);
                    rpcRep=amqp_get_rpc_reply(conn);
                    if(rpcRep.reply_type!=AMQP_RESPONSE_NORMAL)
                    {
                        return std::string("");
                    }
                    amqp_frame_t frame;
                    int result;
            
                    size_t body_target;
                    size_t body_received;
                
                    amqp_maybe_release_buffers(conn);
                    result = amqp_simple_wait_frame(conn, &frame);
                    if (result < 0)
                        return std::string("");
                    if (frame.frame_type != AMQP_FRAME_METHOD)
                        return std::string("");
                
                    if (frame.payload.method.id != AMQP_BASIC_DELIVER_METHOD)
                        return std::string("");
                
                    result = amqp_simple_wait_frame(conn, &frame);
                    if (result < 0)
                        return std::string("");
                
                    if (frame.frame_type != AMQP_FRAME_HEADER) {
                        return std::string("");
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
                    return ss.str();
                }
                return std::string("");
            }
        template<class Function>
        bool Listen(std::string queue,Function f)
            {
                if(isConnect)
                {
                    amqp_bytes_t empty_bytes;
                    empty_bytes.len=0;
                    empty_bytes.bytes=NULL;
                    amqp_table_t empty_table;
                    empty_table.num_entries=-3;
                    empty_table.entries=NULL;
                    amqp_bytes_t queuename=amqp_cstring_bytes(queue.c_str()); 

                    amqp_basic_consume(conn, 1, queuename, empty_bytes, 0, 1, 0, empty_table);
                    amqp_rpc_reply_t rpcRep=amqp_get_rpc_reply(conn);
                    if(rpcRep.reply_type!=AMQP_RESPONSE_NORMAL)
                    {
                        return false;
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
                        p = (amqp_basic_properties_t *) frame.payload.properties.decoded;
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
                        f(ss.str(),p);
                    }
                }
                return false;
            }
        bool isConnected()
            {
                return isConnect;
            }
        ~RabbitClient()
            {
                amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);
                amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
                amqp_destroy_connection(conn);
            }
    private:
        bool isConnect;
        amqp_connection_state_t conn;
    };
}

#endif
