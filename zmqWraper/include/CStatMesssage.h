#ifndef __CSTAT_MESSAGE_H__
#define __CSTAT_MESSAGE_H__
#include "BaseMessage.h"
namespace zmqWrapper
{
    enum CStat
    {
        NodeStart=0,
        NodeEnd
    };
    class CStatMessage:public BaseMessage
    {
    public:
        CStatMessage();
        CStatMessage(std::string msg);
        ~CStatMessage(){};
        std::string GetNodeName(){return m_NodeName;}
        void SetNodeName(std::string name){m_NodeName=name;}
        CStat GetNodeStat(){return m_stat;}
        void SetNodeStat(CStat stat){m_stat=stat;}
        virtual std::string GetBody();
        virtual std::string toString();
    private:
        std::string m_NodeName;
        CStat m_stat;
    }
};
#endif
