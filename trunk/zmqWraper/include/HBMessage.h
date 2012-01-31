#ifndef __HB_MESSAGE_H__
#define __HB_MESSAGE_H__
#include "BaseMessage.h"
namespace zmqWrapper
{
    class HBMessage:public BaseMessage
    {
    public:
        HBMessage();
        HBMessage(std::string msg);
        ~HBMessage(){};
        std::string GetNodeName(){return m_NodeName;}
        void SetNodeName(std::string name){m_NodeName=name;}
        virtual std::string GetBody();
        virtual std::string toString();
    private:
        std::string m_NodeName;
    }
};
#endif
