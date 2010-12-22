#ifndef __MESSAGES_H__
#define __MESSAGES_H__
#include <Theron/Address.h>
#include <boost/assign/list_of.hpp>
#include "StockPrice.hpp"
#include "FetchInfo.hpp"
#include "SearchInfo.hpp"
#include <boost/shared_ptr.hpp>
#define MAX_LEN 40960
struct AddressMessage
{
    enum AddType
    {
        CHILD,
        PARENT,
        LOG
    };
    AddressMessage(){}
    AddressMessage(AddType t,std::string n,Theron::Address a):type(t),address(a)
        {
            memset(name,0,sizeof(name));
            strcpy(name,n.c_str());
        }
    AddType type;          // name of the actor.
    char name[1024];
    Theron::Address address;         // addres of the actor.
};
struct OperateMessage
{
    enum OpType
    {
        STATUS,
        SET,
        HTTP_GET,
        MQ_GET,
        MQ_PUT,
        RESP
    };
    OperateMessage(){}
    OperateMessage(OpType t,std::string m):type(t)
        {
            memset(status,0,sizeof(status));
            strcpy(status,m.c_str());
        }
    OpType type;
    char status[4096];
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
//复杂对象使用指针构建消息。
//对象在创建时手动分配空间，在消费完成后手动销毁！！！
struct StockMessage
{
    StockMessage(stock::StockPrice *r):rp(r){
        
    };
    StockMessage(){};
    stock::StockPrice *rp;
};
struct StockListMessage
{
    StockListMessage(stock::StockPriceList *r):list(r){
        
    };
    StockListMessage(){};
    stock::StockPriceList *list;
};
struct PriceReqMessage
{
    PriceReqMessage(stock::PriceReq *r,const char *k):req(r){
        memset(resKey,0,sizeof(resKey));
        strcpy(resKey,k);
    };
    PriceReqMessage(){};
    stock::PriceReq *req;
    char resKey[4096];
};
struct PriceResMessage
{
    PriceResMessage(stock::StockPriceList *r,const char *k):list(r){
        memset(resKey,0,sizeof(resKey));
        strcpy(resKey,k);
    };
    PriceResMessage(){};
    stock::StockPriceList *list;
    char resKey[4096];
};
struct FetchTaskMessage
{
    FetchTaskMessage(fetch::FetchInfo *f):fi(f){
    };
    FetchTaskMessage(){};
    fetch::FetchInfo *fi;
};
struct FetchResultMessage
{
    FetchResultMessage(fetch::FetchResult *r):result(r){
    };
    FetchResultMessage(){};
    fetch::FetchResult *result;
};
struct ClassifyResultMessage
{
    ClassifyResultMessage(fetch::FetchResult *r):result(r){
    };
    ClassifyResultMessage(){};
    fetch::FetchResult *result;
};
struct ExtractResultMessage
{
    ExtractResultMessage(fetch::FetchResult *r):result(r){
    };
    ExtractResultMessage(){};
    fetch::FetchResult *result;
};
struct IndexMessage
{
    IndexMessage(search::IndexInfo *i):index(i){
    };
    IndexMessage(){};
    search::IndexInfo *index;
};
struct QueryMessage
{
    QueryMessage(search::QueryInfo *q,char *k):query(q){
        memset(resKey,0,sizeof(resKey));
        strcpy(resKey,k);
    };
    QueryMessage(){};
    search::QueryInfo *query;
    char resKey[4096];
};
struct QueryResponceMessage
{
    QueryResponceMessage(search::DocList *r,const char *k):res(r){
        memset(resKey,0,sizeof(resKey));
        strcpy(resKey,k);
    };
    QueryResponceMessage(){};
    search::DocList *res;
    char resKey[4096];
};
#endif
