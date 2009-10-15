#include "BaseException.hpp"
#include "config_file.hpp"
#include <map>
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/program_options.hpp>
#include "Logger.hpp"
namespace po = boost::program_options;
/// Init the static pointer of Configer.
Configer* Configer::m_instance=0;
/**
* @brief Get a pointer of Configer.
* 
* 
* @return 
*/

Configer* Configer::Instance()
{
     if(m_instance==0)
     {
	  m_instance=new Configer;
     }
     return m_instance;
}
/** 
 * @brief Delete the instance of Configer.
 * 
 */
void Configer::Destroy()
{
     if(m_instance!=0)
     {
	  delete m_instance;
	  m_instance=0;
     }
}

/** 
 * @brief The default constructor.
 * 
 */
Configer::Configer()
{
}
/** 
 * @brief The destructor.
 * 
 */
Configer::~Configer()
{
}
std::string Configer::GetConfig(std::string filename,std::string section,std::string Name)
{
     std::ifstream ifs(filename.c_str());
     std::string opname;
     if(section.length()>0)
	  opname=section+"."+Name;
     else
	  opname=Name;
     po::options_description desc;
     desc.add_options()
	  (opname.c_str(), "");
     po::variables_map vm;       
     po::store(po::parse_config_file(ifs, desc, true), vm);
     po::notify(vm);
     LOG_APP<<opname<<" count:"<<vm.count(opname.c_str());
     std::string ret;
     if(vm.count(opname.c_str()))
	  ret=vm[opname.c_str()].as<std::string>();
     return ret;
}
std::string Configer::GetConfig(std::string filename,std::string Name)
{
     std::ifstream ifs(filename.c_str());
     std::string opname=Name;
     po::options_description desc;
     desc.add_options()
	  (opname.c_str(), "");
     po::variables_map vm;       
     po::store(po::parse_config_file(ifs, desc, true), vm);
     po::notify(vm);
     LOG_APP<<opname<<" count:"<<vm.count(opname.c_str());
     std::string ret;
     if(vm.count(opname.c_str()))
	  ret=vm[opname.c_str()].as<std::string>();
     return ret;
}
std::map<std::string,std::string> Configer::GetConfig(std::string filename,std::list<std::string> NameList)
{
     std::ifstream ifs(filename.c_str());
     po::options_description desc;
     std::map<std::string,std::string> ret;
     for(std::list<std::string>::iterator it=NameList.begin();it!=NameList.end();++it)
     {
	  desc.add_options()
	       (it->c_str(), "");
     }
     po::variables_map vm;       
     po::store(po::parse_config_file(ifs, desc, true), vm);
     po::notify(vm);
     for(std::list<std::string>::iterator it=NameList.begin();it!=NameList.end();++it)
     {
	  std::string key=*it;
	  LOG_APP<<key<<" count:"<<vm.count(key.c_str());
	  if(vm.count(key.c_str()))
	  {
	       std::string value=vm[key.c_str()].as<std::string>();
	       ret.insert(make_pair(key,value));
	  }
     }
     return ret;
}
std::map<std::string,std::string> Configer::GetConfig(std::string filename,std::string section,std::list<std::string> NameList)
{
     std::ifstream ifs(filename.c_str());
     po::options_description desc;
     std::map<std::string,std::string> ret;
     for(std::list<std::string>::iterator it=NameList.begin();it!=NameList.end();++it)
     {
	  std::string opname;
	  if(section.length()>0)
	  {
	       opname=section+"."+*it;
	  }else
	  {
	       opname=*it;
	  }
	  desc.add_options()
	       (opname.c_str(), "");
     }
     po::variables_map vm;       
     po::store(po::parse_config_file(ifs, desc, true), vm);
     po::notify(vm);
     for(std::list<std::string>::iterator it=NameList.begin();it!=NameList.end();++it)
     {
	  std::string key;
	  if(section.length()>0)
	  {
	       key=section+"."+*it;
	  }else
	  {
	       key=*it;
	  }
	  LOG_APP<<key<<" count:"<<vm.count(key.c_str());
	  if(vm.count(key.c_str()))
	  {
	       std::string value=vm[key.c_str()].as<std::string>();
	       ret.insert(make_pair(key,value));
	  }
     }
     return ret;
}
