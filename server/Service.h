
#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <iostream>
namespace server {

     class Service
     {
     public:
	  
	  /**
	   * @param  in
	   * @param  out
	   */
	  virtual void serve(std::istream &in,std::ostream &out)=0;

	  virtual std::string &getName()=0;
	  
	  
     };
}; // end of package namespace

#endif // SERVICE_H
