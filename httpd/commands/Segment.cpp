#include <iostream>
#include <sstream>
#include "Segment.h"
#include "config_file.hpp"
#include "Logger.hpp"
#include <map>
#include <boost/assign/list_of.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "word.hpp"
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
     LOG_DBG << "param:"<<param;
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
     words ws;
     scws_send_text(m_s, content.c_str(), content.length());
     if ((top = xtop = scws_get_tops(m_s, tlimit, NULL)) != NULL)
     {
	  while (xtop != NULL)
	  {
	    aword aw(xtop->word,xtop->weight,xtop->times,xtop->attr);
	    ws.addWord(aw);
	    xtop = xtop->next;
	  }
	  scws_free_tops(top);
     }
     boost::archive::xml_oarchive oa(ss);
     oa << BOOST_SERIALIZATION_NVP(ws);
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
