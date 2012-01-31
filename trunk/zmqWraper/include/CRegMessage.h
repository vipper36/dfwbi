#ifndef __CREG_MESSAGE_H__
#define __CREG_MESSAGE_H__
#include "BaseMessage.h"
namespace zmqWrapper
{
    class CRegMessage:public BaseMessage
    {
    public:
        CRegMessage();
        CRegMessage(std::string msg);
        ~CRegMessage(){};
        std::string GetNodeName(){return m_NodeName;}
        void SetNodeName(std::string name){m_NodeName=name;}
        virtual std::string GetBody();
        virtual std::string toString();
    private:
        std::string m_NodeName;
    }
};
#endif
