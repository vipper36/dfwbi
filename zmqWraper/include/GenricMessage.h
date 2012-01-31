#ifndef __GENRIC_MESSAGE_H__
#define __GENRIC_MESSAGE_H__
#include <string>
namespace zmqWrapper
{
    class GenericMessage:public BaseMessage
    {
    public:
        GenericMessage();
        GenericMessage(std::string msg);
        GenericMessage(const BaseMessage &msg);
        ~GenericMessage(){};
        virtual std::string GetBody(){return m_body;}
        void SetBody(std::string body){m_body=body;}
        virtual std::string toString();
    private:
        std::string m_body;
    }
};
#endif
