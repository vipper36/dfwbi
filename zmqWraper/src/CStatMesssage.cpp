#include "CStatMessage.h"
using namespace zmqWrapper;
CStatMessage::CStatMessage()
    :BaseMessage(),
     m_NodeName("")
{
    m_gen=SNGenerator::instance();
    SetType(SYS_ASYNC);
    SetName("NodeStat");
}
CStatMessage::CStatMessage(std::string msg)
    :BaseMessage(),
     m_NodeName("")
{
    Json::Reader reader;
    Json::Value value;
    if(reader.parse(msg,value))
    {
        if(!value["type"].isNull())
            SetType(value["type"].asInt());
        if(!value["name"].isNull())
            SetName(value["name"].asString());
        if(!value["sn"].isNull())
            SetSN(value["sn"].asInt());
        if(!value["body"].isNull())
        {
            Json::Value m_body = value["body"];
            if(!m_body["NodeName"].isNull())
                m_NodeName=m_body["NodeName"].asString();
            if(!m_body["NodeStat"].isNull())
                m_stat=m_body["NodeStat"].asInt();
        }
    }
}
std::string GetBody()
{
    Json::Value msgBody;
    msgBody["NodeName"]=Json::Value(m_NodeName);
    msgBody["NodeStat"]=Json::Value(m_stat);
    Json::FastWriter fast_writer;
    return fast_writer.write(msgBody);
}
std::string CStatMessage::toString()
{
    Json::Value msgJson;
    msgJson["type"]=Json::Value(GetType());
    msgJson["name"]=Json::Value(GetName());
    msgJson["sn"]=Json::Value(GetSN());
    Json::Value msgBody;
    msgBody["NodeName"]=Json::Value(m_NodeName);
    msgBody["NodeStat"]=Json::Value(m_stat);
    msgJson["body"]=msgBody;
    Json::FastWriter fast_writer;
    return fast_writer.write(msgJson);
}
