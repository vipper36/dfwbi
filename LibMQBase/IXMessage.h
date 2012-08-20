#ifndef IXMESSAGE_H
#define IXMESSAGE_H
#include <string>
#include <map>
#include <json_spirit.h>
#include <iostream>
#include <list>

template<typename T>
class ValueUtil
{
    public:
    static json_spirit::Value toValue(T body)
    {
        return json_spirit::Value(body);
    }
    static T fromValue(json_spirit::Value v)
    {
        return v.get_value<T>();
    }
};
template<>
class ValueUtil< std::map<std::string,json_spirit::Value> >
{
    public:
    static json_spirit::Value toValue(std::map<std::string,json_spirit::Value> body)
    {
        json_spirit::Object addr_obj;
        for(std::map<std::string,json_spirit::Value>::iterator it=body.begin();it!=body.end();++it)
        {
            addr_obj.push_back( json_spirit::Pair( it->first, it->second ) );
        }
        return json_spirit::Value(addr_obj);
    }
    static std::map<std::string,json_spirit::Value> fromValue(json_spirit::Value v)
    {
        std::map<std::string,json_spirit::Value> ret;
        if(v.type()==json_spirit::obj_type)
        {
            json_spirit::Object obj=v.get_value<json_spirit::Object>();
            for(json_spirit::Object::iterator it= obj.begin();it!=obj.end();++it)
            {
                ret.insert(std::make_pair(it->name_,it->value_));
            }
        }
        return ret;
    }
};
template<>
class ValueUtil< std::list<json_spirit::Value> >
{
    public:
    static json_spirit::Value toValue(std::list<json_spirit::Value> body)
    {
        json_spirit::Array arr;
        for(std::list<json_spirit::Value>::iterator it=body.begin();it!=body.end();++it)
        {
            arr.push_back(*it);
        }
        return json_spirit::Value(arr);
    }
    static std::list<json_spirit::Value> fromValue(json_spirit::Value v)
    {
        std::list<json_spirit::Value> ret;
        if(v.type()==json_spirit::array_type)
        {
            json_spirit::Array arr=v.get_value<json_spirit::Array>();
            for(json_spirit::Array::iterator it= arr.begin();it!=arr.end();++it)
            {
                ret.push_back(*it);
            }
        }
        return ret;
    }
};
template<typename T>
class ValueUtil< std::map<std::string,T> >
{
public:
    static json_spirit::Value toValue(std::map<std::string,T> body)
    {
        std::map<std::string,json_spirit::Value> vmap;
        for(typename std::map<std::string,T>::iterator it=body.begin();it!=body.end();++it)
        {
            json_spirit::Value v=ValueUtil<T>::toValue(it->second);
            vmap.insert(std::make_pair(it->first,v));
        }
        return ValueUtil< std::map<std::string,json_spirit::Value> >::toValue(vmap);
    }
    static std::map<std::string,T> fromValue(json_spirit::Value v)
    {
        std::map<std::string,T> ret;
        if(v.type()==json_spirit::obj_type)
        {
            json_spirit::Object obj=v.get_value<json_spirit::Object>();
            for(json_spirit::Object::iterator it= obj.begin();it!=obj.end();++it)
            {
                ret.insert(std::make_pair(it->name_,ValueUtil<T>::fromValue(it->value_)));
            }
        }
        return ret;
    }
};
template<typename T>
class ValueUtil< std::list<T> >
{

    static json_spirit::Value toValue(std::list<T> body)
    {
        std::list<json_spirit::Value> vlist;
        for(typename std::list<T>::iterator it=body.begin();it!=body.end();++it)
        {
            vlist.push_back(ValueUtil<T>::toValue(*it));
        }
        return ValueUtil< std::list<json_spirit::Value> >::toValue(vlist);
    }
    static std::list<T> fromValue(json_spirit::Value v)
    {
        std::list<T> ret;
        if(v.type()==json_spirit::array_type)
        {
            json_spirit::Array arr=v.get_value<json_spirit::Array>();
            for(json_spirit::Array::iterator it= arr.begin();it!=arr.end();++it)
            {
                ret.push_back(ValueUtil<T>::fromValue(*it));
            }
        }
        return ret;
    }
};
class Message
{
    public:
        Message(){};
        virtual ~Message(){};
        std::string Getversion() const{ return m_version; }
        void Setversion(std::string val) { m_version = val; }
        std::map<std::string,std::string> Gethead() const{ return m_head; }
        void addHeadAtt(std::string name,std::string value)
        {
            m_head.insert(std::make_pair(name,value));
        }
        std::string getHeadAtt(std::string name) const
        {
            std::string ret;
            std::map<std::string,std::string>::const_iterator fit=m_head.find(name);
            if(fit!=m_head.end())
            {
                ret=fit->second;
            }
            return ret;
        }
        virtual void fromJson(std::string json)=0;
        virtual std::string toJson() const=0;
    protected:
        std::map<std::string,std::string> m_head;
        std::string m_version;
};
template<typename T>
class IXMessage:public Message
{
    public:
        IXMessage(){};
        virtual ~IXMessage(){};
        T Getbody() const{ return m_body; }
        void Setbody(T val) { m_body = val; }
        void fromJson(std::string json)
        {
            std::stringstream ss(json);
            json_spirit::Value value;
            read( ss, value );
            if(value.type()==json_spirit::obj_type)
            {
                json_spirit::Object obj=value.get_value<json_spirit::Object>();
                for(json_spirit::Object::iterator it= obj.begin();it!=obj.end();++it)
                {
                    if(it->name_=="version")
                    {
                        m_version=it->value_.get_value<std::string>();
                    }else if(it->name_=="head")
                    {
                        m_head=ValueUtil< std::map<std::string,std::string> >::fromValue(it->value_);
                    }else if(it->name_=="body")
                    {
                        m_body=ValueUtil<T>::fromValue(it->value_);
                    }
                }
            }
        }
        std::string toJson() const
        {
            std::stringstream ss;
            json_spirit::Object obj;
            obj.push_back(json_spirit::Pair("version",m_version));
            obj.push_back(json_spirit::Pair("head",ValueUtil< std::map<std::string,std::string> >::toValue(m_head)));
            obj.push_back(json_spirit::Pair("body",ValueUtil<T>::toValue(m_body)));
            json_spirit::write( obj, ss);
            return ss.str();
        }
    protected:
        T m_body;
};
class IXReqMessage:public IXMessage< std::map<std::string,std::string> >
{
public:
    void addReqAtt(std::string name,std::string value)
    {
        m_body.insert(std::make_pair(name,value));
    }
    std::string getReqAtt(std::string name)
    {
        return m_body[name];
    }
    void SetName(std::string value)
    {
        m_head.insert(std::make_pair("name",value));
    }
    std::string GetName()
    {
        return m_head["name"];
    }
    void SetType(std::string value)
    {
        m_head.insert(std::make_pair("type",value));
    }
    std::string GetType()
    {
        return m_head["type"];
    }
};

#endif // IXMESSAGE_H
