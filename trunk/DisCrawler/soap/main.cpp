#include "soapCrawlerCtrlSoapBindingProxy.h"
#include "CrawlerCtrlSoapBinding.nsmap"

int main()
{
     CrawlerCtrlSoapBindingProxy service;
     soap_set_mode(&service, SOAP_C_UTFSTRING);
     _nyapc1__addJob areq;
     _nyapc1__addJobResponse ares;

     areq.name="test2";
     areq.comment="hehe";
     areq.url="163";
     areq.type="1";
     if (service.addJob(&areq,&ares) == SOAP_OK)
     {
     	  if(ares.addJobReturn)
     	       std::cout << "Add success!! " << std::endl;
     	  else
     	       std::cout << "Add failed!! " << std::endl;
     }
     _nyapc1__getJobID req;
     _nyapc1__getJobIDResponse res;
     if (service.getJobID(&req,&res) == SOAP_OK)
     {
	  for(std::vector<int>::iterator it=res.getJobIDReturn.begin();it!=res.getJobIDReturn.end();++it)
	  {
	       _nyapc1__getJob req;
	       req.id=*it;
	       _nyapc1__getJobResponse res;
	       if (service.getJob(&req,&res) == SOAP_OK)
	       {
		    std::cout << "The id is " <<res.getJobReturn->id<< std::endl;
		    std::cout << "The name is " <<*(res.getJobReturn->name)<< std::endl;
		    std::cout << "The comment is " <<*(res.getJobReturn->comment)<< std::endl;
		    std::cout << "The seed is " <<*(res.getJobReturn->seed)<< std::endl;
	       }
	  }

     }
     else
     	  service.soap_stream_fault(std::cerr);
     
     _nyapc1__getWrapper breq;
     breq.id=1;
     _nyapc1__getWrapperResponse bres;
     if (service.getWrapper(&breq,&bres) == SOAP_OK)
     {
	  std::cout << "The wrap is " <<bres.getWrapperReturn<< std::endl;
     }
     _nyapc1__getJobs creq;
     _nyapc1__getJobsResponse cres;
     if (service.getJobs(&creq,&cres) == SOAP_OK)
     {
	  for(std::vector<nyapc1__JobAtt*>::iterator it=cres.getJobsReturn.begin();it!=cres.getJobsReturn.end();++it)
	  {
	       std::cout << "The id is " <<(*it)->id<< std::endl;
	       std::cout << "The name is " <<*((*it)->name)<< std::endl;
	       std::cout << "The comment is " <<*((*it)->comment)<< std::endl;
	       std::cout << "The seed is " <<*((*it)->seed)<< std::endl;
	  }
     }
     _nyapc1__getTask treq;
     treq.cid=1;
     _nyapc1__getTaskResponse tres;
     if (service.getTask(&treq,&tres) == SOAP_OK)
       {
	 if(tres.getTaskReturn!=NULL)
	   {
	     int jobid=tres.getTaskReturn->job_USCOREid;

	     std::cout<<"jid:"<<jobid<<"\n";
		 std::cout<<"url:"<<*(tres.getTaskReturn->urls)<<"\n";
	   }
       }

} 
