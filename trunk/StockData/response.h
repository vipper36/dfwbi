#ifndef RESPONSE_H_INCLUDED
#define RESPONSE_H_INCLUDED
#include <boost/smart_ptr.hpp>
namespace StockMarket
{
#pragma pack(push)
#pragma pack(1)


struct ResHead
{
public:
    int finger;
    char zip;
    uint seq_id;			// 同一种命令的 seq_id。
    char span2;
    ushort cmd;
    ushort len1;
    ushort len2;
};
class Response
{
private:
    ResHead head;
    boost::shared_ptr<char>  data;
public:
    Response()
    {
    }
    Response(const char*buf):head(),data()
    {
        memcpy(&this->head,buf,sizeof(ResHead));
        data.reset(new char[head.len1]);
        memcpy(data.get(),buf+sizeof(ResHead),head.len1);
    }
    ~Response()
    {
    }
    void setHead(const char*buf)
    {
        memcpy(&this->head,buf,sizeof(ResHead));
    }
    void setData(const char*buf)
    {
        data.reset(new char[head.len1]);
        memcpy(data.get(),buf,head.len1);
    }
    ResHead &getHead()
    {
        return head;
    }
    boost::shared_ptr<char>  getData()
    {
        return data;
    }
};

#pragma pack(pop)
}
#endif // RESPONSE_H_INCLUDED
