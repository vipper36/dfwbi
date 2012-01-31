#include "MsgRegMessage.h"
using namespace zmqWrapper;
MsgRegMessage::MsgRegMessage()
    :BaseMessage(),
     m_NodeName("")
{
    m_gen=SNGenerator::instance();
    SetType(SYS_ASYNC);
    SetName("MsgReg");
}
MsgRegMessage::MsgRegMessage(std::string msg)
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
            if(!m_body["MsgArray"].isNull())
            {
                Json::Value msgArray=m_body["MsgArray"];
                for(Json::Value::iterator it=msgArray.begin();it!=msgArray.end();++it)
                {
                    MsgType tmpType=(*it)["type"].asInt();
                    std::string tmpName=(*it)["name"].asString();
                    AddMsg(tmpType,tmpName);
                }
            }
        }
    }
}
void AddMsg(MsgType type,std::string name)
{
    m_MsgList.push_back(std::make_pair(type,name))
}
void AddMsg(std::list<std::pair<MsgType,std::string> > &list)
{
    m_MsgList.insert(m_MsgList.begin(),list.begin(),list.end());
}
std::string GetBody()
{
    Json::Value msgBody;
    msgBody["NodeName"]=Json::Value(m_NodeName);
    Json::Value msgArray(Json::arrayValue);
    for(std::list<std::pair<MsgType,std::string> >::iterator it=m_MsgList.begin();it!=m_MsgList.end();++it)
    {
        Json::Value tmpV;
        tmpV["type"]=Json::Value(it->first);
        tmpV["name"]=Json::Value(it->second);
        msgArray.append(tmpV);
    }
    msgBody["MsgArray"]=msgArray;
    Json::FastWriter fast_writer;
    return fast_writer.write(msgBody);
}
std::string MsgRegMessage::toString()
{
    Json::Value msgJson;
    msgJson["type"]=Json::Value(GetType());
    msgJson["name"]=Json::Value(GetName());
    msgJson["sn"]=Json::Value(GetSN());
    Json::Value msgBody;
    msgBody["NodeName"]=Json::Value(m_NodeName);
    Json::Value msgArray(Json::arrayValue);
    for(std::list<std::pair<MsgType,std::string> >::iterator it=m_MsgList.begin();it!=m_MsgList.end();++it)
    {
        Json::Value tmpV;
        tmpV["type"]=Json::Value(it->first);
        tmpV["name"]=Json::Value(it->second);
        msgArray.append(tmpV);
    }
    msgBody["MsgArray"]=msgArray;
    msgJson["body"]=msgBody;
    Json::FastWriter fast_writer;
    return fast_writer.write(msgJson);
}
