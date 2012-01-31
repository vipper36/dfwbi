#ifndef __BASE_MESSAGE_H__
#define __BASE_MESSAGE_H__
#include <string>
namespace zmqWrapper
{
    enum MsgType
    {
        USER_SYNC=0,
        USER_ASYNC,
        SYS_SYNC,
        SYS_ASYNC
    };
    class BaseMessage
    {
    public:
        BaseMessage()
            :m_type(0),
             m_name("")
            {
                m_gen=SNGenerator::instance();
                m_sn=m_get.GetSN();
            }
        ~BaseMessage(){};
        MsgType GetType(){return m_type;}
        void SetType(MsgType type){m_type=type;}
        std::string GetName(){return m_name;}
        void SetName(std::string name){m_name=name;}
        unsigned long GetSN(){return m_sn;}
        virtual std::string GetBody()=0;
        virtual std::string toString()=0;
    private:
        MsgType m_type;
        std::string m_name;
        unsigned long m_sn;
        SNGenerator *m_gen;
    }
};
#endif
