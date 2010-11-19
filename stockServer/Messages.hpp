#ifndef __MESSAGES_H__
#define __MESSAGES_H__
#include <Theron/Address.h>
struct RealPrice
{
    std::string marcket;
    std::string code;
    std::string stockName;
    double open;
    double lclose;
    double close;
    double high;
    double low;
    double buyPrice;
    double sellPrice;
    int volum;
    double money;
    int buy1Ask;
    double buy1Price;
    int buy2Ask;
    double buy2Price;
    int buy3Ask;
    double buy3Price;
    int buy4Ask;
    double buy4Price;
    int buy5Ask;
    double buy5Price;
    int sell1Ask;
    double sell1Price;
    int sell2Ask;
    double sell2Price;
    int sell3Ask;
    double sell3Price;
    int sell4Ask;
    double sell4Price;
    int sell5Ask;
    double sell5Price;
    std::string date;
    std::string time;
};
struct AddressMessage
{
    enum AddType
    {
        CHILD,
        PARENT,
        LOG
    };
    AddressMessage(){}
    AddressMessage(AddType t,std::string n,Theron::Address a):type(t),name(n),address(a)
        {
        }
    AddType type;          // name of the actor.
    std::string name;
    Theron::Address address;         // addres of the actor.
};
struct OperateMessage
{
    enum OpType
    {
        STATUS,
        HTTP_GET,
        MQ_GET,
        MQ_PUT,
        RESP
    };
    OperateMessage(){}
    OperateMessage(OpType t,std::string m):type(t),status(m)
        {
        }
    OpType type;          // name of the actor.
    std::string status;         // addres of the actor.
};
struct MapMessage
{
    enum MapType
    {
        ATTR,
        MSG
    };
    MapMessage():type(ATTR),map(){};
    MapMessage(MapType t,std::map<std::string,std::string> &l):type(t),map(l){};
    MapType type;
    std::map<std::string,std::string> map;
};
struct StockRealMessage
{
};
struct StockKLineMessage
{
};
#endif
