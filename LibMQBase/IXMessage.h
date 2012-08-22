#ifndef IXMESSAGE_H
#define IXMESSAGE_H
#include <string>
#include <map>
#include <json_spirit.h>
#include <iostream>
#include <list>
#include "ValueUtil.h"
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
            json_spirit::read( ss, value );
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
