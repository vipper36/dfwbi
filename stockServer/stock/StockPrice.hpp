#ifndef __STOCK_PRICE_H__
#define __STOCK_PRICE_H__
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/assign/list_of.hpp>
#include "boost/date_time/posix_time/posix_time.hpp" 
#include <map>
#include <list>
#include <sstream>
namespace stock
{
    static std::list<std::string> NTAGS=boost::assign::list_of("open")
	("high")
	("low")
	("close")
	("volum")
	("money");

    static std::list<std::string> TAGS=boost::assign::list_of("open")
        ("lclose")
        ("close")
        ("high")
        ("low")
        ("buyPrice")
        ("sellPrice")
        ("volum")
        ("money")
        ("buy1Ask")
        ("buy1Price")
        ("buy2Ask")
        ("buy2Price")
        ("buy3Ask")
        ("buy3Price")
        ("buy4Ask")
        ("buy4Price")
        ("buy5Ask")
        ("buy5Price")
        ("sell1Ask")
        ("sell1Price")
        ("sell2Ask")
        ("sell2Price")
        ("sell3Ask")
        ("sell3Price")
        ("sell4Ask")
        ("sell4Price")
        ("sell5Ask")
        ("sell5Price");
    enum TimeCycle
    {
        REAL=0,
        M1,
        M15,
        M30,
        M60,
        DAY,
        WEEK,
        MON
    };
    struct StockPrice
    {
    private:
        friend class boost::serialization::access;
        template<class Archive>
        void save(Archive & ar, const unsigned int version) const
            {
                std::string timeStr=to_iso_string(time);
                ar & BOOST_SERIALIZATION_NVP(type);
                ar & BOOST_SERIALIZATION_NVP(marcket);
                ar & BOOST_SERIALIZATION_NVP(code);
                ar & BOOST_SERIALIZATION_NVP(stockName);
                ar & BOOST_SERIALIZATION_NVP(priceMap);
                ar & BOOST_SERIALIZATION_NVP(timeStr);
            }
        template<class Archive>
        void load(Archive & ar, const unsigned int version)
            {
                std::string timeStr;
                ar & BOOST_SERIALIZATION_NVP(type);
                ar & BOOST_SERIALIZATION_NVP(marcket);
                ar & BOOST_SERIALIZATION_NVP(code);
                ar & BOOST_SERIALIZATION_NVP(stockName);
                ar & BOOST_SERIALIZATION_NVP(priceMap);
                ar & BOOST_SERIALIZATION_NVP(timeStr);
                time=boost::posix_time::from_iso_string(timeStr);
            }
        BOOST_SERIALIZATION_SPLIT_MEMBER()

    public:
        StockPrice(){}
        StockPrice(const StockPrice &rp):type(rp.type),marcket(rp.marcket),code(rp.code),stockName(rp.stockName),priceMap(rp.priceMap),time(rp.time)
            {}
        TimeCycle type;
        std::string marcket;
        std::string code;
        std::string stockName;
        std::map<std::string,double> priceMap;
        boost::posix_time::ptime time;
        
    };
    struct StockPriceList
    {
    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_NVP(type);
                ar & BOOST_SERIALIZATION_NVP(marcket);
                ar & BOOST_SERIALIZATION_NVP(code);
                ar & BOOST_SERIALIZATION_NVP(priceList);
            }
    public:
        StockPriceList(){}
        StockPriceList(const StockPriceList &r):type(r.type),marcket(r.marcket),code(r.code),priceList(r.priceList)
            {}
        TimeCycle type;
        std::string marcket;
        std::string code;
        std::list<StockPrice> priceList;
    };
    struct PriceReq
    {
    private:
        friend class boost::serialization::access;
        template<class Archive>
        void save(Archive & ar, const unsigned int version) const
            {
                std::string fromStr=to_iso_string(from);
                std::string toStr=to_iso_string(to);
                ar & BOOST_SERIALIZATION_NVP(type);
                ar & BOOST_SERIALIZATION_NVP(marcket);
                ar & BOOST_SERIALIZATION_NVP(code);
                ar & BOOST_SERIALIZATION_NVP(fromStr);
                ar & BOOST_SERIALIZATION_NVP(toStr);
            }
        template<class Archive>
        void load(Archive & ar, const unsigned int version)
            {
                std::string fromStr;
                std::string toStr;
                ar & BOOST_SERIALIZATION_NVP(type);
                ar & BOOST_SERIALIZATION_NVP(marcket);
                ar & BOOST_SERIALIZATION_NVP(code);
                ar & BOOST_SERIALIZATION_NVP(fromStr);
                ar & BOOST_SERIALIZATION_NVP(toStr);
                from=boost::posix_time::from_iso_string(fromStr);
                to=boost::posix_time::from_iso_string(toStr);
            }
        BOOST_SERIALIZATION_SPLIT_MEMBER()

    public:
        PriceReq(){}
        PriceReq(const PriceReq &req):marcket(req.marcket),code(req.code),type(req.type),from(req.from),to(req.to)
            {}
        PriceReq(std::string t,std::string m,std::string c,std::string f,std::string e)
            :marcket(m),code(c)
            {
                if(t=="REAL")
                    type=REAL;
                else if(t=="M1")
                    type=M1;
                else if(t=="M15")
                    type=M15;
                else if(t=="M30")
                    type=M30;
                else if(t=="M60")
                    type=M60;
                else if(t=="DAY")
                    type=DAY;
                else if(t=="WEEK")
                    type=WEEK;
                else if(t=="MON")
                    type=MON;
                from=boost::posix_time::from_iso_string(f);
                to=boost::posix_time::from_iso_string(e);
            }
        TimeCycle type;
        std::string marcket;
        std::string code;
        boost::posix_time::ptime from;
        boost::posix_time::ptime to;
    };

}
#endif
