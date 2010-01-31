#ifndef __CONFIGER_H__
#define __CONFIGER_H__
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Factory.hpp"
/**
 * 
 * 
 */
namespace Base
{
  using boost::property_tree::ptree;
  enum CONF_TYPE
    {
      NONE=0,
      XML,
      INI,
      JSON
    };
  template<int T>
  class Configer_t
  {
  public:
    static Configer_t* Instance()
    {
      if(m_instance==0)
	{
	  m_instance=new Configer_t;
	}
      return m_instance;
    }
    static void Destroy()
    {
      if(m_instance!=0)
	{
	  delete m_instance;
	  m_instance=0;
	}
    }
    bool LoadXml(const std::string& file)
    {
      _type=XML;
      read_xml(file, pt);
      return true;
    }
    bool LoadIni(const std::string& file)
    {
      _type=INI;
      read_ini(file, pt);
      return true;
    }
    bool LoadJson(const std::string& file)
    {
      _type=JSON;
      read_json(file, pt);
      return true;
    }
    template<typename Object>
    Object *CreateObject(const std::string& name)
    {
      Factory<Object> *fact=Factory<Object>::Instance();
      std::string dllName;
      
      std::string funName;
      switch(_type)
	{
	case XML:
	case JSON:
	  funName=pt.get<std::string>("conf.object."+name+".create_fun");
	  dllName=pt.get<std::string>("conf.object."+name+".dlfile");
	  break;
	case INI:
	  funName=pt.get<std::string>(name+".create_fun");
	  dllName=pt.get<std::string>(name+".dlfile");
	  break;
	default:
	  break;
	}
      if(dllName.length()>0&&funName.length()>0)
	{
	  fact-> Register(dllName);
	  try
	    {
	      Object *obj=fact->CreateObject(dllName,funName);
	      return obj;
	    }catch(BaseException e)
	    {
	      return NULL;
	    }
	}
      else
	{
	  return NULL;
	}
    }
    std::string GetConfig(std::string Name)
    {
	try
	{
      		return pt.get<std::string>(Name);
	}catch(std::exception& e) 
	{
		return std::string("");
	}
    }
  protected:
    Configer_t():_type(NONE)
    {}
    ~Configer_t()
    {
    }
  private:
    CONF_TYPE _type;
    ptree pt;
    static Configer_t* m_instance;
  };
  template<int T>
  Configer_t<T>* Configer_t<T>::m_instance=0;
  typedef Configer_t<1> Configer;
}    

#endif
