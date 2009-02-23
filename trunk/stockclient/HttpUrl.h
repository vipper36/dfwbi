#ifndef __HTTP_URL__
#define __HTTP_URL__
#include <string>
class HttpUrl
{
private:
  std::string _full;
  std::string _protocal;
  std::string _host;
  std::string _port;
  std::string _resource;
  bool correctUrl;
  bool parseURl(std::string &url);
public:
  void setUrl(std::string &url);
  bool IsUrl();
  std::string getPort();
  std::string &getProtoc();
  std::string &getHost();
  std::string &getResource();
  HttpUrl()
   :_full(),
   _protocal(),
   _host(),
   _port("80")
  {}
  HttpUrl(std::string &url);
  ~HttpUrl(){}
};
#endif
