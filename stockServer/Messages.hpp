#ifndef __MESSAGES_H__
#define __MESSAGES_H__
#include <Theron/Address.h>
#include <boost/assign/list_of.hpp>
#include "StockPrice.hpp"

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
    StockRealMessage(stock::RealPrice r):rp(r){};
    StockRealMessage(){};
    stock::RealPrice rp;
};
struct StockKLineMessage
{
};
#endif
