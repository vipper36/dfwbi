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
    struct RealPrice
    {
    private:
        friend class boost::serialization::access;
        template<class Archive>
        void save(Archive & ar, const unsigned int version) const
            {
                std::string timeStr=to_iso_string(time);
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
                ar & BOOST_SERIALIZATION_NVP(marcket);
                ar & BOOST_SERIALIZATION_NVP(code);
                ar & BOOST_SERIALIZATION_NVP(stockName);
                ar & BOOST_SERIALIZATION_NVP(priceMap);
                ar & BOOST_SERIALIZATION_NVP(timeStr);
                time=boost::posix_time::from_iso_string(timeStr);
            }
        BOOST_SERIALIZATION_SPLIT_MEMBER()

    public:
        RealPrice(){}
        RealPrice(const RealPrice &rp):marcket(rp.marcket),code(rp.code),stockName(rp.stockName),priceMap(rp.priceMap),time(rp.time)
            {}
        std::string marcket;
        std::string code;
        std::string stockName;
        std::map<std::string,double> priceMap;
        boost::posix_time::ptime time;
        
    };

}
#endif
