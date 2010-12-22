#ifndef __SEARCH_INFO_H__
#define __SEARCH_INFO_H__
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
namespace search
{
    struct IndexInfo
    {
    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_NVP(uid);
                ar & BOOST_SERIALIZATION_NVP(content);
                ar & BOOST_SERIALIZATION_NVP(db);
                ar & BOOST_SERIALIZATION_NVP(attMap);
            }

    public:
        std::string uid;
        std::string content;
        std::string db;
        std::map<std::string,std::string> attMap;
    };
    struct DocList
    {
    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_NVP(docList);
            }

    public:
        std::list<IndexInfo> docList;
    };
    struct QueryInfo
    {
    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_NVP(query);
                ar & BOOST_SERIALIZATION_NVP(vdb);
            }

    public:
        std::string query;
        std::string vdb;
    };
}
#endif
