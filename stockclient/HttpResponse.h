#ifndef __HTTP_RESPONSE__
#define __HTTP_RESPONSE__
#include <map>
#include <istream>
#include <string>
#include <sstream>
class HttpResponse
{
private:
     std::string _http_ver;
     int _stat_code;
     std::string _reason_phrase;
     std::map<std::string,std::string> _heads;
     std::stringstream _body;
public:
     HttpResponse()
	  :_http_ver(),
	   _stat_code(),
	   _reason_phrase(),
	   _heads(),
	   _body()
	  {
	       
	  }
     ~HttpResponse(){};
     std::string &getVersion();
     int getStat();
     std::string getHeadAtt(std::string &headTag);
     std::stringstream &getBody();
     friend std::istream& operator>>(std::istream& in,HttpResponse &res);
};
#endif
