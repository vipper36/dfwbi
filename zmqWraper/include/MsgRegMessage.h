#ifndef __MSGREG_MESSAGE_H__
#define __MSGREG_MESSAGE_H__
#include "BaseMessage.h"
namespace zmqWrapper
{
    class MsgRegMessage:public BaseMessage
    {
    public:
        MsgRegMessage();
        MsgRegMessage(std::string msg);
        ~MsgRegMessage(){};
        std::string GetNodeName(){return m_NodeName;}
        void SetNodeName(std::string name){m_NodeName=name;}
        std::list<std::pair<MsgType,std::string> > &GetMsgList(){return m_MsgList;}
        void AddMsg(MsgType type,std::string name);
        void AddMsg(std::list<std::pair<MsgType,std::string> > &list);
        virtual std::string GetBody();
        virtual std::string toString();
    private:
        std::string m_NodeName;
        std::list<std::pair<MsgType,std::string> > m_MsgList;
    }
};
#endif
