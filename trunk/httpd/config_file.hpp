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
     std::string GetConfig(std::string filename,std::string section,std::string Name);
     std::string GetConfig(std::string filename,std::string Name);
     std::map<std::string,std::string> GetConfig(std::string filename,std::list<std::string> NameList);
     std::map<std::string,std::string> GetConfig(std::string filename,std::string section,std::list<std::string> NameList);
  protected:
     Configer();
     ~Configer();
  private:
     static Configer* m_instance;
};

    

#endif
