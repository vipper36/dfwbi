#ifndef __HANDLE_COMMAND_H__
#define __HANDLE_COMMAND_H__
#include <string>
#include <map>
#include <boost/signals/signal.hpp>
#include <boost/assign/list_of.hpp>
#include "command_inter.hpp"
#include "Factory.hpp"
#include "config_file.hpp"
using namespace boost::assign;
namespace http {
     namespace server3 {

	  typedef boost::signals::signal<std::string (const std::string &param, const std::string& content)> SigType;
	  typedef boost::function<std::string (const std::string&,const std::string&)> funType;
	  template<typename T>
	  class handle_command
	       : private boost::noncopyable
	  {
	  public:
	       handle_command(){
		    fact=Factory<T>::Instance();
	       };
	       ~handle_command(){};
	       bool SigCommand(const std::string& cmd,const std::string& param,const std::string& content, std::string& ret)
		    {
			 std::map<std::string,funType>::iterator fit=cmds.find(cmd);
			 if(fit!=cmds.end())
			 {
			      SigType sig;
			      sig.connect(fit->second);
			      ret=*sig(param,content);
			      return true;
			 }
			 else
			 {
			      if(RegisterCmd(cmd))
			      {
				   fit=cmds.find(cmd);
				   SigType sig;
				   sig.connect(fit->second);
				   ret=*sig(param,content);
				   return true;
			      }else
			      {
				   return false;
			      }
			 }
		    }
	       bool RegisterCmd(const std::string& cmd)
		    {
			 Configer* conf=Configer::Instance();
	  
			 std::list<std::string> cmdconf=list_of("dlfile")("create_fun");
			 std::map<std::string,std::string> remap=conf->GetConfig(cmd,cmdconf);
			 if(remap.size()<cmdconf.size())
			 {
			      return false;
			 }else
			 {
			      try
			      {
				   std::string dlName=remap[cmd+".dlfile"];
				   std::string funName=remap[cmd+".create_fun"];
				   fact-> Register(dlName);
				   command_inter *tp=fact->CreateObject(dlName,funName);
			  
				   boost::function<std::string (const std::string&,const std::string&)> fun=boost::bind(&command_inter::handle,tp,_1,_2);
			 
				   cmds.insert(make_pair(cmd,fun));
				   return true;
			      }catch(BaseException e)
			      {
				   return false;
			      }
			 }
		    }
	       bool setConfig(const std::string& file)
		    {
			 config_file_=file;
			 return true;
		    }
	  private:
	       std::map<std::string,funType> cmds;
	       std::string config_file_;
	       Factory<T> *fact;
	  };
     }
}
#endif
