#include "HttpResponse.h"
#include <sstream>
#include <cstring>
#include <cstdlib>
std::string &HttpResponse::getVersion()
{
     return _http_ver;
}
int HttpResponse::getStat()
{
     return _stat_code;
}
std::string HttpResponse::getHeadAtt(std::string &headTag)
{
     std::map<std::string,std::string>::iterator it;
     it=_heads.find(headTag);
     if(it!=_heads.end())
	  return it->second;
     else
	  return std::string("");
     
}
std::string &HttpResponse::getBody()
{
     return _body;
}
std::istream& operator>>(std::istream& in,HttpResponse &res)
{
     bool bodyStart=false;
     std::stringstream ss;
     std::string line;
     while(!in.eof())
     {
	  std::getline(in,line);
	  if(line.length()==0||line=="\r")
	  {
	       bodyStart=true;
	  }
	  else
	  {
	       if(bodyStart)
		    ss<<line<<std::endl;
	       else
	       {
		    size_t idx=line.find(':');
		    if(idx!=std::string::npos)
		    {
			 std::string hTag=line.substr(0,idx);
			 std::string val=line.substr(idx+1);
			 res._heads.insert(make_pair(hTag,val));
		    }
		    else
		    {
			 idx=line.find("HTTP/");
			 if(idx!=std::string::npos)
			 {
			      size_t idx2=line.find(' ',idx+5);
			      if(idx2!=std::string::npos)
			      {
				   size_t idx3=line.find(' ',idx2+1);
				   if(idx3!=std::string::npos)
				   {
					std::string stat=line.substr(idx2+1,idx3-idx2-1);
					res._stat_code=atoi(stat.c_str());
				   }
			      }
			      res._http_ver=line.substr(idx,idx2-idx);
			 }
		    }
	      
	       }
	  }
     }
     res._body=ss.str();
     return in;
    
}
