#include <iostream>
#include "client.h"
#include "stock.h"
#include "request.h"
using namespace std;

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 4)
        {
            std::cerr << "Usage: client <host> <port> <type>\n";
            return 1;
        }

        boost::asio::io_service io_service;
        tcp::resolver r(io_service);
        client c(io_service);

        for(StockMarket::MarketInfo::MarketType m = StockMarket::MarketInfo::MARKET_FIRST;
            m < StockMarket::MarketInfo::MARKET_MAX; m=(StockMarket::MarketInfo::MarketType)(m+1))
        {
            StockMarket::StockListStruct req(m, 1, 50);
            req.header.seq_id=c.getSeq(StockMarket::CMD_STOCK_LIST);
            c.send(req);
        }
//        std::string code="000005";
//        uint seq=c.getSeq(StockMarket::CMD_STOCK_KLINE);
//        std::cout << "query code: " << code <<"seq:"<<seq<< "\n";
//
//        StockMarket::StockKLineStruct req(code,1,4,seq);
//        c.send(req);
        if(strcmp("false",argv[3])==0)
        {
            c.setType(false);
        }
        c.start(r.resolve(tcp::resolver::query(argv[1], argv[2])));

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
