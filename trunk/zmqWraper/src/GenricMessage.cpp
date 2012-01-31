#include "GenericMessage.h"
#include <json.h>
using namespace zmqWrapper;
GenericMessage::GenericMessage()
    :BaseMessage(),
     m_body("")
{
}
GenericMessage::GenericMessage(std::string msg)
    :BaseMessage(),
     m_body("")
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
            m_body = value["body"].asString();
    }
}
GenericMessage::GenericMessage(const BaseMessage &msg)
    :BaseMessage(),
     m_body(msg.GetBody())
{
    SetSN(msg.GetSN());
    SetType(msg.GetType());
    SetName(msg.GetName());
}
std::string GenericMessage::toString()
{
    Json::Value msgJson;
    msgJson["type"]=Json::Value(GetType());
    msgJson["name"]=Json::Value(GetName());
    msgJson["sn"]=Json::Value(GetSN());
    msgJson["body"]=Json::Value(m_body);
    Json::FastWriter fast_writer;
    return fast_writer.write(msgJson);
}
