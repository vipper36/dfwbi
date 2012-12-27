#ifndef MQMESSAGE_H
#define MQMESSAGE_H
#include <string>
#include <map>
#include <json_spirit.h>
#include <iostream>
#include <list>
#include "ValueUtil.h"
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include "MsgFactory.h"
#include "ContextManager.h"
class MqMessage
{
public:
    MqMessage() {}
    MqMessage(const MqMessage &msg)
    {
        m_head=msg.getHeadMap();
        m_id=msg.getIdentify();
    }
    virtual ~MqMessage() {}
    std::map<std::string,std::string> getHeadMap() const
    {
        return m_head;
    }
    std::string getHead() const
    {
        json_spirit::Value  val=ValueUtil< std::map<std::string,std::string> >::toValue(m_head);
        std::stringstream ss;
        json_spirit::write( val, ss);
        return ss.str();
    }
    virtual std::string getMsg() const=0;
    std::string getIdentify() const
    {
        return m_id;
    }
    void setIdentify(std::string &id)
    {
        m_id=id;
    }
    void setHead(std::string &head)
    {
        std::stringstream ss(head);
        json_spirit::Value value;
        read( ss, value );
        m_head=ValueUtil< std::map<std::string,std::string> >::fromValue(value);
    }
    std::string getHeadAtt(std::string name) const
    {
        std::map<std::string,std::string>::const_iterator fit=m_head.find(name);
        if(fit!=m_head.end())
            return fit->second;
        else
            return "";
    }
    void addHeadAtt(const std::string &name,const std::string &value)
    {
        m_head.insert(std::make_pair(name,value));
    }
    virtual void setMsg(std::string &msg)=0;
    virtual void print() const
    {
        std::cout<<"id:"<<getIdentify()<<std::endl;
        std::cout<<"head:"<<getHead()<<std::endl;
        std::cout<<"msg:"<<getMsg()<<std::endl;
    }
protected:
    std::string m_id;
    std::map<std::string,std::string> m_head;
};
class BaseMqMessage:public MqMessage
{
public:
    BaseMqMessage() {}
    BaseMqMessage(const std::string &msg)
    {
        m_msg=msg;
    }
    BaseMqMessage(const MqMessage &msg):MqMessage(msg)
    {
        std::string content=msg.getMsg();
        setMsg(content);
    }
    virtual ~BaseMqMessage() {}
    virtual std::string getMsg() const
    {
        return m_msg;
    }
    virtual void setMsg(std::string &msg)
    {
        m_msg=msg;
    }
private:
    std::string m_msg;
};

class MsgWrapper
{
public:
    MsgWrapper(boost::shared_ptr<Message> msg)
    {
        m_msg=msg;
    };
    void setMsg(boost::shared_ptr<Message> msg)
    {
        m_msg=msg;
    }
    boost::shared_ptr<Message> getMsg() const
    {
        return m_msg;
    }
private:
    boost::shared_ptr<Message>  m_msg;
};
class ActorMqMessage:public MqMessage
{
public:
    ActorMqMessage() {}
    ActorMqMessage(const boost::shared_ptr<Message> &msg)
    {
        m_msg=msg;
        if(!msg)
        {
            MqMessage::addHeadAtt("type",msg->getMsgType());
        }
    }
    ActorMqMessage(const MqMessage &msg):MqMessage(msg)
    {
        std::string content=msg.getMsg();
        setMsg(content);
    }
    virtual ~ActorMqMessage() {}

    virtual std::string getMsg() const
    {
        return m_msg->toJson();
    }

    virtual void setMsg(std::string &msg)
    {
        ContextManager *cm=ContextManager::Instance();
        MsgFactory *factory=cm->GetMsgFactory();
        m_msg=factory->CreateMSG(msg);
    }

    boost::shared_ptr<Message> getActorMsg() const
    {
        return m_msg;
    }
    void setActorMsg(boost::shared_ptr<Message> &msg)
    {
        m_msg=msg;
    }
protected:
private:
    std::map<std::string,std::string> m_head;
    boost::shared_ptr<Message>  m_msg;
};



#endif // MQMESSAGE_H
