#ifndef __FETCH_INFO_H__
#define __FETCH_INFO_H__
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
namespace fetch
{
    enum FETCH_TYPE
    {
        NORMAL=0,
        COOKIE,
        LOGIN
    };
    struct FetchInfo
    {
    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_NVP(type);
                ar & BOOST_SERIALIZATION_NVP(pathList);
                ar & BOOST_SERIALIZATION_NVP(url);
                ar & BOOST_SERIALIZATION_NVP(attMap);
            }

    public:
        FETCH_TYPE type;
        std::list<std::string> pathList;
        std::string url;
        std::map<std::string,std::string> attMap;
    };
    enum RESULT_TYPE
    {
        UNKNOWN=0,
        COOKIESTR,
        URL,
        CONTENT,
        ERROR
    };
    struct FetchResult
    {
    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_NVP(type);
                ar & BOOST_SERIALIZATION_NVP(pathList);
                ar & BOOST_SERIALIZATION_NVP(url);
                ar & BOOST_SERIALIZATION_NVP(result);
            }

    public:
        RESULT_TYPE type;
        std::list<std::string> pathList;
        std::string url;
        std::string result;
    };
    struct FetchTreeNode;
    typedef std::map<std::string,FetchTreeNode>::iterator node_iterator;
    struct FetchTreeNode
    {
        struct FetchInfo info;
        boost::posix_time::ptime update;
        std::list<node_iterator> childList;
        node_iterator parent;
    };
}
#endif
