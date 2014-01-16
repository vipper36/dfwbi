
#ifndef _STOCK_REQUEST_H_
#define _STOCK_REQUEST_H_
#include "stock.h"

namespace StockMarket
{
using namespace std;
using namespace boost;

#pragma pack(push)
#pragma pack(1)

struct ReqHead
{
public:
    ReqHead() {};
    ReqHead( ushort cmd_id, ushort packet_len,uint seq)
    {
        zip = 0x0c;
        seq_id = seq;
        packet_type = 1;
        len = len1 = packet_len - sizeof(ReqHead) + 2;
        cmd = cmd_id;
    }
    void set_len(ushort payload_len)
    {
        len = len1 = payload_len;
    }
public:
    char zip;				// always 0x0c: data-uncompressed
    uint seq_id;			// 同一种命令的 seq_id。
    char packet_type;	// 00: 回应。 1,2,3... request count
    ushort len;			//	数据长度
    ushort len1;			//  数据长度重复
    ushort cmd;			// b4 bf: 分钟线。。b5 bf 单笔成交
};

struct StockKLineStruct
{
    StockKLineStruct(const string& code, ushort btype,ushort ltype,uint seq=0,uint scale=0)
        : header(CMD_STOCK_KLINE, sizeof(StockKLineStruct),seq),little_type(ltype),big_type(btype)
    {
        memcpy(stock_code,code.c_str(), MarketInfo::StocksCodeLen);
        market=MarketInfo::get_market_from_code(stock_code);
        base_size=0x1a4;
        scaled_size=base_size*scale;
        memset(span,0,sizeof(span));
    }
    ReqHead	header;
    short market;		//  00 00 上, 	01 00 深,
    char stock_code[MarketInfo::StocksCodeLen];
    ushort little_type;
    ushort big_type;
    ushort scaled_size;
    ushort base_size;
    char span[10];
};

struct StockHeartBeatStruct
{
    StockHeartBeatStruct(uint seq=0) : header(CMD_HEART_BEAT, sizeof(StockHeartBeatStruct),seq), count(1)
    {
        memcpy(&stock_code[0],"000792", MarketInfo::StocksCodeLen);
        location = MarketInfo::get_market_location(&stock_code[0]);
    }
    ReqHead	header;
    ushort count;
    char location;
    char stock_code[MarketInfo::StocksCodeLen];
};

//   0c 22 07 0a 00 01 0c 00 0c 00 24 05 00 00 00 00 00 00 1e 00 00 00
struct StockListStruct
{
    StockListStruct(MarketInfo::MarketType market_code, ushort record_offset, ushort record_count,uint seq=0)
        : header(CMD_STOCK_LIST, sizeof(StockListStruct),seq),unknown1(0),
          offset(record_offset), count(record_count),unknown2(0)
    {
        block = MarketInfo::get_block_from_market_type(market_code);
    }
    ReqHead	header;
    ushort block;		//  00 00 上A, 	01 00 上B, 	02 00 深A, 	03 00 深B, 	0x0d: 权证
    ushort unknown1;
    ushort offset;
    ushort count;
    ushort unknown2;
};

struct StockHoldStruct
{
    char market_locale;
    char stock_code[MarketInfo::StocksCodeLen];
};
struct StockHoldChgReqStruct
{
    StockHoldChgReqStruct(uint seq=0) : header(CMD_STOCKHOLD_CHANGE, 0,seq), count(0) {}
    bool add_one_stock(const string& stock_code)
    {
        if(count >= MarketInfo::max_stocks_a_request)
            return false;

        s_buff[count].market_locale = MarketInfo::get_market_location(stock_code);
        memcpy(&s_buff[count].stock_code, stock_code.c_str(), MarketInfo::StocksCodeLen);
        count++;
        header.set_len( sizeof(StockHoldStruct) * count + 4);

        return true;
    }
    ReqHead	header;
    ushort count;
    StockHoldStruct s_buff[MarketInfo::max_stocks_a_request];
};
struct InstantTransStruct
{
    InstantTransStruct()
    {
    }
    InstantTransStruct(const string& stock_code,  ushort record_offset, ushort record_count ,uint seq=0)
        : header(CMD_INSTANT_TRANS, sizeof(InstantTransStruct),seq),
          offset(record_offset), count(record_count)
    {
        set_stock_code(stock_code);
    }
    void set_stock_code(const string& stock_code)
    {
        memcpy(code, stock_code.c_str(), MarketInfo::StocksCodeLen);
        location = MarketInfo::get_market_location(stock_code);
    }
    ReqHead	header;
    ushort location;
    char code[MarketInfo::StocksCodeLen];
    ushort offset;	//
    ushort count;	//
};
struct HisTransStruct		//0x0fb5
{
public:
    HisTransStruct() {}
    HisTransStruct(const string& stock_code,  uint record_date, ushort record_offset, ushort record_count,uint seq=0)
        : header(CMD_HIS_TRANS, sizeof(HisTransStruct),seq), date(record_date), offset(record_offset), count(record_count)
    {
        set_stock_code(stock_code);
    }
    void set_stock_code(const string& stock_code)
    {
        memcpy(code, stock_code.c_str(), MarketInfo::StocksCodeLen);
        location = MarketInfo::get_market_location(stock_code);
    }
    void set_offset(ushort off)
    {
        offset = off;
    }
    ReqHead	header;
    uint date;
    ushort location;
    char code[6];
    ushort offset;
    ushort count;
};
#pragma pack(pop)

}


#endif


