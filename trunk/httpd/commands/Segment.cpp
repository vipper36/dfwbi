#include <iostream>
#include <sstream>
#include "Segment.h"
#include "config_file.hpp"
#include "Logger.hpp"
#include <map>
#include <boost/assign/list_of.hpp>
using namespace boost::assign;
using namespace Base;
void *Segment_create()
{
     Segment_cmd *ret=new Segment_cmd();
     return (void*)ret;
}
Segment_cmd::~Segment_cmd()
{     
     scws_free(m_s);
}

Segment_cmd::Segment_cmd()
{
     m_s=scws_new();
     
     scws_set_charset(m_s, "utf-8");
}
std::string Segment_cmd::handle(const std::string& param,const std::string& content)
{
    
//     scws_res_t res, cur;
     scws_top_t top, xtop;
     LOG_APP << "param:"<<param;
     LOG_APP << "content:"<<content;
     
     if(m_param!=param)
     {
	  m_param=param;
	  Configer* conf=Configer::Instance();

	  std::string dict=conf->GetConfig(m_param+".dict");
	  std::string rules=conf->GetConfig(m_param+".rules");
	  if(dict.length()>0)
	  {
	  
	       scws_set_dict(m_s, dict.c_str(),SCWS_XDICT_XDB);
	  }
	  if(rules.length()>0)
	  {
	       scws_set_rule(m_s, rules.c_str());
	  }
     }
     
     int tlimit=content.length();
     std::stringstream ss;
     scws_send_text(m_s, content.c_str(), content.length());
     ss<<"No. WordString               Attr  Weight(times)"<<std::endl;
     ss<<"-------------------------------------------------"<<std::endl;
     if ((top = xtop = scws_get_tops(m_s, tlimit, NULL)) != NULL)
     {
	  tlimit = 1;
	  while (xtop != NULL)
	  {
	       ss<< tlimit
		 << ". "<<xtop->word
		 << "              "<< xtop->attr
		 << " "<<xtop->weight
		 << "("<<xtop->times<<")"<<std::endl;
	       xtop = xtop->next;
	       tlimit++;
	  }
	  scws_free_tops(top);
     }
     // if ((cur = res = scws_get_result(s)) != NULL)
     // {
     //      while (cur != NULL)
     //      {
	       
     //           ss<<content.substr(cur->off,cur->len)<<std::endl;
     //           cur = cur->next;;
     //      }
     //      scws_free_result(res);
     // }
     std::string ret(ss.str());
     return ret;
}
