#ifndef __HANDLE_COMMAND_H__
#define __HANDLE_COMMAND_H__
#include <string>
#include <map>
#include <boost/signals2/signal.hpp>
#include <boost/assign/list_of.hpp>
#include "command_inter.hpp"
#include "Factory.hpp"
#include "Logger.hpp"
#include "config_file.hpp"
using namespace Base;
using namespace boost::assign;
namespace http {
     namespace server3 {

	  typedef boost::signals2::signal<std::string (const std::string &param, const std::string& content)> SigType;
	  typedef boost::function<std::string (const std::string&,const std::string&)> funType;
	  class handle_command
	       : private boost::noncopyable
	  {
	  public:
	       handle_command(){
		 conf=Configer::Instance();
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
		      LOG_DBG<<"command:"<<cmd;
		      command_inter *tp=conf->CreateObject<command_inter>(cmd);
		      if(tp!=NULL)
			{
			  boost::function<std::string (const std::string&,const std::string&)> fun=boost::bind(&command_inter::handle,tp,_1,_2); 
			  cmds.insert(make_pair(cmd,fun));
			  return true;
			}else
			{
			  return false;
			}
		    }
	  private:
	    std::map<std::string,funType> cmds;
	    Configer *conf;
	  };
     }
}
#endif
