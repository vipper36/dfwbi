#include "HttpUrl.h"
#include <stdlib.h>
std::string HttpUrl::getPort()
{
  return _port;
}
std::string &HttpUrl::getProtoc()
{
  return _protocal;
}
std::string &HttpUrl::getHost()
{
  return _host;
}
std::string &HttpUrl::getResource()
{
  return _resource;
}
void HttpUrl::setUrl(std::string &url)
{
     if(parseURl(url))
	  correctUrl=true;
     else
	  correctUrl=false;
}
bool HttpUrl::IsUrl()
{
  return correctUrl;
}
bool HttpUrl::parseURl(std::string &url)
{
  _full=url;
  size_t proIdx=_full.find("://");
  if (proIdx==std::string::npos)
    return false;
  _protocal=_full.substr(0,proIdx);
  size_t addStart=proIdx+3;
  size_t addend=_full.find('/',addStart);
  if (addend==std::string::npos)
    return false;
  _resource=_full.substr(addend);
  std::string HostPort=_full.substr(addStart,addend-addStart);
  size_t portIdx=HostPort.find(':');
  if(portIdx==std::string::npos)
    {
      _port="80";
      _host=HostPort;
    }
  else
    {
      _port=HostPort.substr(portIdx+1);
      if(atoi(_port.c_str())<=0)
	   return false;
      _host=HostPort.substr(0,portIdx);
    }
  return true;
}
HttpUrl::HttpUrl(std::string &url)
  :_full(url),
   _protocal(),
   _host(),
   _port("80")
{
     if(parseURl(url))
	  correctUrl=true;
     else
	  correctUrl=false;
}
