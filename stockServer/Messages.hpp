#ifndef __MESSAGES_H__
#define __MESSAGES_H__
#include <Theron/Address.h>
#include <boost/assign/list_of.hpp>
#include "StockPrice.hpp"
#include <boost/shared_ptr.hpp>
struct AddressMessage
{
    enum AddType
    {
        CHILD,
        PARENT,
        LOG
    };
    AddressMessage(){}
    AddressMessage(AddType t,std::string n,Theron::Address a):type(t),address(a),name(n)
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
    OpType type;
    std::string status;
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
    StockRealMessage(stock::RealPrice &r){
        std::stringstream ss;
        boost::archive::xml_oarchive oa(ss);
        oa << BOOST_SERIALIZATION_NVP(r);
        rp=ss.str();
    };
    StockRealMessage(){};
    std::string rp;
};
struct StockKLineMessage
{
};
#endif
