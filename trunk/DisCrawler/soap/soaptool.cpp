#include "soapCrawlerCtrlSoapBindingProxy.h"
#include "CrawlerCtrlSoapBinding.nsmap"
#include <unistd.h>
#include <fstream>
void usage()
{
     std::cout<<"usage:\nsoaptool [-T]\n"
	      <<"soaptool [-J <-n name -t type -u url [-c comment] [-s service]>\n"
	      <<"soaptool [-W <-i jobid -t type -v generator -f wrapfile [-c comment] [-s service]>]\n"
	      <<"soaptool [-U <[-i jobid] [-a] [-s service]>]\n"
	      <<"soaptool [-I <[-s service]>]"
	      <<"soaptool [-E <[-s service] -d service>]"
	      <<std::endl;
     exit(0);
}
int main(int argc,char* argv[])
{
     int miss=-1;
     std::string serviceStr;
     std::string tarServiceStr;
     
     std::string jobname;
     std::string jobtype;
     std::string joburl;
     std::string comment;
     std::string wrapfile;
     std::string vargen;
     bool all=false;
     int jobid=-1;
     int opt;
     while((opt = getopt(argc, argv, "ETJWUIn:t:u:c:f:i:v:s:d:a")) != -1) {
	  switch(opt) {
	
	  case 'T':
	       if(miss>0)
		    usage();
	       else
		    miss=1;
	       break;
	  case 'J':
	       if(miss>0)
		    usage();
	       else
		    miss=2;
	       break;
	  case 'W':
	       if(miss>0)
		    usage();
	       else
		    miss=3;
	       break;
	  case 'U':
	       if(miss>0)
		    usage();
	       else
		    miss=4;
	       break;
	  case 'I':
	       if(miss>0)
		    usage();
	       else
		    miss=5;
	       break;
	  case 'E':
	       if(miss>0)
		    usage();
	       else
		    miss=6;
	       break;
	  case 'n':
	       jobname=std::string(optarg);
	       break;
	  case 't':
	       jobtype=std::string(optarg);
	       break;
	  case 'u':
	       joburl=std::string(optarg);
	       break;
	  case 'c':
	       comment=std::string(optarg);
	       break;
	  case 'f':
	       wrapfile=std::string(optarg);
	       break;
	  case 'v':
	       vargen=std::string(optarg);
	       break;
	  case 's':
	       serviceStr=std::string(optarg);
	       break;
	  case 'd':
	       tarServiceStr=std::string(optarg);
	       break;

	  case 'i':
	       jobid=atoi(optarg);
	       break;
	  case 'a':
	       all=true;
	       break;
	  default:
	       usage();
	  }
     }
     CrawlerCtrlSoapBindingProxy service;
     soap_set_mode(&service, SOAP_C_UTFSTRING);
     if(serviceStr.length()>0)
	  service.soap_endpoint=serviceStr.c_str();
     switch(miss)
     {
     case 1:
     {          
	  _nyapc1__hasTask treq;
	  treq.cid=1;
	  _nyapc1__hasTaskResponse tres;
	  if (service.hasTask(&treq,&tres) == SOAP_OK)
	  {
	       std::cout<<tres.hasTaskReturn<<"\n";
	  }
	  break;
     }
     
     case 2:
     {
	  
	  if(jobname.length()>0&&jobtype.length()>0&&joburl.length()>0)
	  {
	       _nyapc1__addJob areq;
	       _nyapc1__addJobResponse ares;
     
	       areq.name=jobname;
	       areq.comment=comment;
	       areq.url=joburl;
	       areq.type=jobtype;
	       if (service.addJob(&areq,&ares) == SOAP_OK)
	       {
		    std::cout << ares.addJobReturn << std::endl;
	       }
	       
	  }
	  else
	  {
	       usage();
	  }
	  break;
     }
     
     case 3:
     {
	  if(jobid>0&&jobtype.length()>0&&wrapfile.length()>0)
	  {
	       std::ifstream ifs(wrapfile.c_str());
	       std::string wrapper=std::string(std::istreambuf_iterator<char>(ifs),std::istreambuf_iterator<char>());
	       _nyapc1__addWrapper areq;
	       _nyapc1__addWrapperResponse ares;
     
	       areq.jobId=jobid;
	       areq.type=jobtype;
	       areq.Wrapper=wrapper;
	       areq.vargen=vargen;
	       areq.comment=comment;
	       if (service.addWrapper(&areq,&ares) == SOAP_OK)
	       {
		    std::cout << ares.addWrapperReturn << std::endl;
	       }
	  }
	  else
	  {
	       usage();
	  }
	  
	  break;
     }
     case 4:
     {
	  if(jobid>0)
	  {
	       _nyapc1__updateJob areq;
	       _nyapc1__updateJobResponse ares;
     
	       areq.id=jobid;
	       if (service.updateJob(&areq,&ares) == SOAP_OK)
	       {
		    std::cout << ares.updateJobReturn << std::endl;
	       }
	  }
	  else if(all)
	  {
	       _nyapc1__getJobID req;
	       _nyapc1__getJobIDResponse res;
	       if (service.getJobID(&req,&res) == SOAP_OK)
	       {
		    for(std::vector<int>::iterator it=res.getJobIDReturn.begin();it!=res.getJobIDReturn.end();++it)
		    {
			 _nyapc1__updateJob areq;
			 _nyapc1__updateJobResponse ares;
     
			 areq.id=*it;
			 if (service.updateJob(&areq,&ares) == SOAP_OK)
			 {
			      std::cout << ares.updateJobReturn << std::endl;
			 }
		    }
		    
	       }
	  }
	  else
	  {
	       usage();
	  }
	  
	  break;
     }
     case 5:
     {
	  _nyapc1__getJobID areq;
	  _nyapc1__getJobIDResponse ares;
	  if (service.getJobID(&areq,&ares) == SOAP_OK)
	  {
	       for(std::vector<int>::iterator it=ares.getJobIDReturn.begin();it!=ares.getJobIDReturn.end();++it)
		    std::cout << *it << std::endl;
	  }
	  
	  break;
     }
     case 6:
     {
	  std::cout << "target service:"<<tarServiceStr<<std::endl;
	  if(tarServiceStr.length()>0)
	  {
	       CrawlerCtrlSoapBindingProxy tarService;
	       soap_set_mode(&tarService, SOAP_C_UTFSTRING);
	       tarService.soap_endpoint=tarServiceStr.c_str();
	       
	       _nyapc1__getJobID areq;
	       
	       _nyapc1__getJobIDResponse ares;
	       
	       if (service.getJobID(&areq,&ares) == SOAP_OK)
	       {
		
		    for(std::vector<int>::iterator it=ares.getJobIDReturn.begin();it!=ares.getJobIDReturn.end();++it)
		    {
			 std::string job_comment;
			 std::string job_name;
			 std::string job_seed;
			 std::string job_seedtype;
			 _nyapc1__getJob jreq;
			 jreq.id=*it;
			 _nyapc1__getJobResponse jres;
			 if (service.getJob(&jreq,&jres) == SOAP_OK)
			 {
			      job_comment=*jres.getJobReturn->comment;
			      job_name=*jres.getJobReturn->name;
			      job_seed=*jres.getJobReturn->seed;
			      job_seedtype=*jres.getJobReturn->seedType;
			 }
			 _nyapc1__addJob treq;
			 _nyapc1__addJobResponse tres;
			 treq.name=job_name;
			 treq.comment=job_comment;
			 treq.url=job_seed;
			 treq.type=job_seedtype;
			 int newJobId=0;
			 if (tarService.addJob(&treq,&tres) == SOAP_OK)
			 {
			      newJobId=tres.addJobReturn;
			 }
			 if(newJobId>0)
			 {
			      std::cout << newJobId << std::endl;
			      _nyapc1__getWrapId wreq;
			      wreq.jid=*it;
			      _nyapc1__getWrapIdResponse wres;
			      if (service.getWrapId(&wreq,&wres) == SOAP_OK)
			      {
				   for(std::vector<int>::iterator wit=wres.getWrapIdReturn.begin();wit!=wres.getWrapIdReturn.end();++wit)
				   {
					std::string wrapper;
					std::string wrapgen;
					std::string wraptype;
					_nyapc1__getWrapper wreq1;
					wreq1.id=*wit;
					_nyapc1__getWrapperResponse wres1;
					if (service.getWrapper(&wreq1,&wres1) == SOAP_OK)
					{
					     wrapper=wres1.getWrapperReturn;
					}
					_nyapc1__getWrapGen wreq2;
					wreq2.id=*wit;
					_nyapc1__getWrapGenResponse wres2;
					if (service.getWrapGen(&wreq2,&wres2) == SOAP_OK)
					{
					     wrapgen=wres2.getWrapGenReturn;
					}
					_nyapc1__getWraptype wreq3;
					wreq3.id=*wit;
					_nyapc1__getWraptypeResponse wres3;
					if (service.getWraptype(&wreq3,&wres3) == SOAP_OK)
					{
					     wraptype=wres3.getWraptypeReturn;
					}
				   

					
					_nyapc1__addWrapper treq1;
					_nyapc1__addWrapperResponse tres1;
					
					treq1.jobId=newJobId;
					treq1.type=wraptype;
					treq1.Wrapper=wrapper;
					treq1.vargen=wrapgen;
					treq1.comment="";
					if (tarService.addWrapper(&treq1,&tres1) == SOAP_OK)
					{
					     std::cout << tres1.addWrapperReturn << std::endl;
					}

				   

				   }
			      }
			 }
			 
			 
			 
		    }
	       }
	  }else
	  {
	       usage();
	  }
	  
	  
	  break;
     }
     
     
     default:
	  usage();
	  
     }
     
     

} 
