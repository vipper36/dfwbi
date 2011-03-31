#ifndef __YAHOO_ACTOR_H_
#define __YAHOO_ACTOR_H__
#include <boost/algorithm/string.hpp>
#include "boost/date_time/posix_time/posix_time.hpp" 
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <Theron/Actor.h>
#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <unicode/ucnv.h>  
#include "OperateActor.hpp"
#include "StockPrice.hpp"
#include "yahooParser.hpp"
static size_t  yahoo_write(void *ptr, size_t size, size_t nmemb, std::stringstream *stream)
{
    stream->write((char*)ptr,size*nmemb);
    return size*nmemb;
}
class YahooActor : public OperateActor
{
public:

    inline YahooActor()
        {
                   
        }
    void OperateHandler(const OperateMessage &message, const Theron::Address from)
        {            
            switch(message.type)
            {
            case OperateMessage::STATUS:
                Send(OperateMessage(OperateMessage::RESP,"YahooActor ok"), from);
                break;
            case OperateMessage::HTTP_GET:
            {
                std::cout<<"get data....:"<<message.status<<std::endl;
                std::string codeStr(message.status);
                std::vector<std::string> resv;
                boost::algorithm::split( resv, codeStr, boost::algorithm::is_any_of("|") );
                std::string url="http://data03.znz.finance.bj1.aliyk.com/test/kline.py/data.znzDo?cmd=";
                boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
                boost::gregorian::greg_year ty=now.date().year();
                boost::gregorian::greg_year sy=ty-3;
                std::stringstream uss;
                uss<<url;
                uss<<TransName(resv[0])<<resv[1];
                uss<<"|";
                for(boost::gregorian::greg_year year=sy;year<=ty;year=year+1)
                {
                    uss<<year<<",";
                }
                uss<<"|";
                std::cout<<uss.str()<<std::endl;
                CURL *curl = curl_easy_init();
                std::stringstream ss;
                if(curl!=NULL) {

                    curl_easy_setopt(curl, CURLOPT_URL, uss.str().c_str());
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA,&ss);
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, yahoo_write);
                    stock::StockPriceList *pl=new stock::StockPriceList();
                    pl->type=stock::DAY;
                    pl->marcket=resv[0];
                    pl->code=resv[1];
                    CURLcode res = curl_easy_perform(curl);
                    if(!ss.eof())
                    {
                        std::list<yahoo::YearData> yl=parseDayResult(ss.str());
                        for(std::list<yahoo::YearData>::iterator yit=yl.begin();yit!=yl.end();++yit)
                        {
                            for(std::list<yahoo::DayPrice>::iterator dit=yit->price_list.begin();dit!=yit->price_list.end();++dit)
                            {
                                stock::StockPrice rp;
                                rp.type=stock::DAY;
                                rp.marcket=resv[0];
                                rp.code=resv[1];
                                rp.stockName=resv[2];
                                int year=dit->date/10000;
                                int mon=(dit->date-year*10000)/100;
                                int day=dit->date-year*10000-mon*100;
                                rp.time=boost::posix_time::ptime(boost::gregorian::date(year,mon,day),boost::posix_time::hours(0));
                                rp.priceMap.insert(std::make_pair("open",dit->open));
                                rp.priceMap.insert(std::make_pair("high",dit->high));
                                rp.priceMap.insert(std::make_pair("low",dit->low));
                                rp.priceMap.insert(std::make_pair("close",dit->close));
                                rp.priceMap.insert(std::make_pair("volum",dit->volum));
                                rp.priceMap.insert(std::make_pair("money",dit->money));
                                pl->priceList.push_back(rp);
                                
                            }
                        }
                    }
                    std::cout<<"start a send:"<<pl->code<<std::endl;
                    StockListMessage stocklist(pl);
                    Send(stocklist, from);
                }
                
                /* always cleanup */ 
                if(curl!=NULL)
                    curl_easy_cleanup(curl);
            }
            break;
            default:
                break;
            }
        }

    std::list<yahoo::YearData> parseDayResult(std::string result)
    {
        using boost::spirit::qi::phrase_parse;
        using boost::spirit::standard::space;
        using boost::phoenix::push_back;
        using boost::phoenix::ref;
  
          
        std::list<yahoo::YearData> ylist;
        yahoo::yhy_parser<std::string::const_iterator> yhy_;
        std::string::const_iterator iter = result.begin();
        std::string::const_iterator end = result.end();
        bool r=phrase_parse(iter,end,
                            (
                                '['>>yhy_[push_back(ref(ylist), boost::spirit::qi::_1)]%','>>"]0"
                                )
                            ,
                            space);
        return ylist;
    }
    std::string TransName(std::string marcket)
        {
            std::string ret;
            if(marcket=="sh")
            {
                ret="SHHQ";
            }else if(marcket=="sz")
            {
                ret="SZHQ";
            }
            return ret;
        }
private:
    boost::asio::deadline_timer* m_timer;
}; 
#endif
