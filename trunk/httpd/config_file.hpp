#ifndef __CONFIGER_H__
#define __CONFIGER_H__
#include <map>
#include <list>
#include <iostream>
/**
 * 
 * 
 */

class Configer
{
  public:
     static Configer* Instance();
     static void Destroy();
     bool SetDefaultConfig(const std::string& file)
	  {
	       file_name_=file;
	       return true;
	  }
     std::string GetConfig(std::string section,std::string Name);
     std::string GetConfig(std::string Name);
     std::map<std::string,std::string> GetConfig(std::list<std::string> NameList);
     std::map<std::string,std::string> GetConfig(std::string section,std::list<std::string> NameList);
     std::string GetFileConfig(std::string filename,std::string section,std::string Name);
     std::string GetFileConfig(std::string filename,std::string Name);
     std::map<std::string,std::string> GetFileConfig(std::string filename,std::list<std::string> NameList);
     std::map<std::string,std::string> GetFileConfig(std::string filename,std::string section,std::list<std::string> NameList);
  protected:
     Configer();
     ~Configer();
  private:
     std::string file_name_;
     static Configer* m_instance;
     std::string GetAbsConfig(std::string filename,std::string Name);
     std::map<std::string,std::string> GetAbsConfig(std::string filename,std::list<std::string> NameList);
};

    

#endif
