#include <iostream>
#include <fstream>
#include <string>
#include <boost/program_options.hpp>
#include "Logger.hpp"
#include "config_file.hpp"
#include "stock_inter.hpp"
#include "list_inter.hpp"
#include <boost/assign/list_of.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <list>
#include <algorithm>
#include "da.h"
#include "GLSFitting.h"
#include <dlib/svm.h>


namespace po = boost::program_options;
using namespace boost::assign;
using namespace boost::numeric::ublas;
using namespace Base;
static double lastval=0;
void OutStock(std::ostream &ost,StockPrice sp)
{
  double curval=log(sp.PriceValues["money"]/sp.PriceValues["volum"]);
  double deltaval=100*(curval-lastval);
		
  if(lastval!=0)
    {
      ost << sp.time<<","<<sp.PriceValues["open"]<<","<<sp.PriceValues["close"]<<","<<sp.PriceValues["high"]<<","<<sp.PriceValues["low"]<<","<<deltaval<<","<<sp.PriceValues["volum"]<<","<<sp.PriceValues["money"]<<std::endl;
    }
  lastval=curval;
}
class GetMatrix
{

private:
  int m_order;
  int m_curRow;
  std::list<double> curList;
  double m_last;
public:
  typedef void result_type;
  GetMatrix(int order)
    :m_curRow(0),
     m_last(0),
     m_order(order)
  {
	       
  }
  result_type operator ()(StockPrice sp,matrix<double> &x,vector<double> &y)
  {
    double curval=log(sp.PriceValues["money"]/sp.PriceValues["volum"]);
    double deltaval=100*(curval-m_last);
    if(m_last==0)
      {
	m_last=curval;
	return;
      }else
      {
	m_last=curval;
      }
    if(fabs(deltaval)<10.1)
      {

	if(curList.size()<m_order)
	  {
	    curList.push_back(deltaval);
	  }else
	  {
	    x.resize(m_curRow+1,m_order+1);
	    y.resize(m_curRow+1);
			 
	    y(m_curRow)=deltaval;
	    x(m_curRow,0)=1;
	    int col=1;
	    for(std::list<double>::iterator it=curList.begin();it!=curList.end();++it)
	      {
		x(m_curRow,col)=*it;
		col++;
	      }	
			 
	    curList.push_back(deltaval);
	    curList.pop_front();
	    m_curRow++;
			 
	  }
      }
  }
};
struct LsAtt
{
  double c;
  double b1;
  double b2;
  double b3;
  double var;
};
void AddtoCont(std::list<double> &target,StockPrice sp)
{
  target.push_back(sp.PriceValues["money"]/sp.PriceValues["volum"]);
}
int main(int argc, char* argv[])
{
  using namespace boost::posix_time;
  using namespace boost::gregorian;
  try
    {
      std::string aStock;
      std::string configFile("stock.conf");
      std::string cmd("yahoo");
      std::string slist("file");
      po::options_description desc("Allowed options");
      desc.add_options()
	("help,h", "usage message")
	("config,f", po::value(&configFile), "config file")
	("cmd,c", po::value(&cmd), "command")
	("list,l", po::value(&slist), "list")
	("stock,s", po::value(&aStock), "list")
	;
      po::variables_map vm;
      po::store(po::parse_command_line(argc, argv, desc), vm);
      po::notify(vm);
      if (vm.count("help")) {
	std::cout << desc << "\n";
	std::cout << "usage:httpd -f [config file] [-l list] [-c command]" << "\n";
	return 0;
      }
      std::cout<<"config file:"<<configFile<<std::endl;
      Configer* conf=Configer::Instance();
      conf->LoadIni(configFile);
      init_logs();
      std::map<std::string,std::string> stockList;
      if(aStock.length()>0)
	{
	  stockList.insert(std::make_pair(aStock,aStock));
	      
	}else
	{
	  list_inter *lp=conf->CreateObject<list_inter>(slist);
	  lp->open("ss.csv","ss");
	  std::map<std::string,std::string> &sslist=lp->GetList();
	  stockList.insert(sslist.begin(),sslist.end());
	  lp->open("sz.csv","sz");
	      
	  std::map<std::string,std::string> &szlist=lp->GetList();
	  stockList.insert(szlist.begin(),szlist.end());
	}
      std::map<std::string,LsAtt> lsmap;
      stock_inter *tp=conf->CreateObject<stock_inter>(cmd);
      if(tp!=NULL)
	{
	  //ptime from(date(2010,1,1),hours(0));
	  ptime now = second_clock::local_time();
	  for(int i=0;i<100;i++)
	    {
	      now=now-days(1);
	      std::cout<<"-------------"<<now<<std::endl;
	      greg_weekday wd = now.date().day_of_week();
	      if(wd.as_number()<5)
		{	
		  ptime from=now-months(3);
		  for(std::map<std::string,std::string>::iterator it=stockList.begin();it!=stockList.end();++it)
		    {
		      std::cout<<"-------------1--"<<now<<std::endl;
		      std::list<StockPrice> &spList=tp->GetHisPrice(it->first,from, now,stock_inter::DAY);
		      std::cout<<"-------------2--"<<now<<std::endl;
		      if(spList.size()>10&&spList.back().time.date()==now.date())
			{

			  // 		    std::ofstream tof(it->first.c_str());
			  // 		    std::for_each(spList.begin(),spList.end(),boost::bind(OutStock,boost::ref(tof),_1));
			  //		    tof.close();
		    
			  GetMatrix getMatrix(3);
			  matrix<double> xs;
			  vector<double> ys;
		    

			  std::for_each(spList.begin(),spList.end(),boost::bind(getMatrix,_1,boost::ref(xs),boost::ref(ys)));
		    
			  //		    std::cout<<"xs="<<std::endl;
			  //		    std::cout<<xs<<std::endl;
		    
			  //		    std::cout<<"ys="<<std::endl;
			  //		    std::cout<<ys<<std::endl;
		    
			  matrix_range<matrix<double> > x (xs, range (0, xs.size1()-1), range (0,  xs.size2()));
			  //		    std::cout<<"x="<<std::endl;
			  //		    std::cout<<x<<std::endl;
		    
			  vector_range<vector<double> > y (ys, range (0, ys.size()-1));
			  //		    std::cout<<"y="<<std::endl;
			  //		    std::cout<<y<<std::endl;
		    
		    
			  // std::cout<<"x="<<std::endl;
			  // 		    std::cout<<x<<std::endl;
			  // 		    std::cout<<"y="<<std::endl;
			  // 		    std::cout<<y<<std::endl;
		    matrix_column<matrix<double> > x1(xs, 1);
                      identity_matrix<double> l(x.size1());
                      matrix<double> ll(x.size1(),x.size1());
                      ll.assign(l);
                      for(int i=0;i<x.size1();i++)
                           ll(i,i)=1/fabs(x1(i));
                      lsf::GLSFitting<double> ls(x,y,ll);
                      ls.calcParams();
                      ls.calcVar();
		//	  lsf::LSFitting<double> ls(x,y);
		//	  ls.calcParams();
		//	  ls.calcVar();
			  //		    std::cout<<ls.getParams()<<std::endl;
			  //		    std::cout<<ls.getVar()<<std::endl;
		    
			  matrix_row<matrix<double> > xt (xs, xs.size1()-1);
		    

			  //		    std::cout<<"xt="<<std::endl;
			  //		    std::cout<<xt<<std::endl;
		    
			  double yt=ys(ys.size()-1);
			  //		    std::cout<<"yt="<<std::endl;
			  //		    std::cout<<yt<<std::endl;
		    
			  double ytt=inner_prod(ls.getParams(),xt);
		    

			  double delta=yt-ytt;
			  //		    std::cout<<"delta="<<std::endl;
			  //		    std::cout<<delta<<std::endl;

			std::ofstream resof("resultdata.txt",std::ios::app);
			  if(fabs(delta)>2*ls.getVar())
			    {
			      vector<double> pars=ls.getParams();
			      LsAtt att;
			      att.c=pars(0);
			      att.b1=pars(1);
			      att.b2=pars(2);
			      att.b3=pars(3);
			      att.var=ls.getVar();
			      lsmap.insert(std::make_pair(it->second,att));
			      resof<<it->second<<","<<spList.back().time<<","<<ls.getParams()<<","<<ls.getVar()<<std::endl;
			    }
			  resof.close();
			      
			}
		    }
		  std::cout<<"-------------3"<<now<<std::endl;
		}
	    }
	}
      typedef dlib::matrix<double,5,1> sample_type;

      typedef dlib::radial_basis_kernel<sample_type> kernel_type;


      dlib::kcentroid<kernel_type> kc(kernel_type(0.1),0.01, 8);

      dlib::kkmeans<kernel_type> test(kc);

      std::vector<sample_type> samples;
      std::vector<sample_type> initial_centers;

      for (std::map<std::string,LsAtt>::iterator it=lsmap.begin(); it!=lsmap.end(); ++it)
	{
	  sample_type m;
	  m(0) = it->second.c;
	  m(1) = it->second.b1;
	  m(2) = it->second.b2;
	  m(3) = it->second.b3;
	  m(4) = it->second.var;
	  // add this sample to our set of samples we will run k-means 
	  samples.push_back(m);
	}
      
      test.set_number_of_centers(3);

      dlib::pick_initial_centers(3, initial_centers, samples, test.get_kernel());

      // now run the k-means algorithm on our set of samples.  
      test.train(samples,initial_centers);

      // now loop over all our samples and print out their predicted class.  In this example
      // all points are correctly identified.
      for (unsigned long i = 0; i < samples.size(); ++i)
	{
	  std::cout << test(samples[i]) << "\n";
	}

      // Now print out how many dictionary vec
    }
  catch (std::exception& e)
    {
      std::cout<< "exception: " << e.what()<<std::endl;
    }

  return 0;
}
