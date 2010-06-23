#ifndef __DA_H__
#define __DA_H__

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>
#include "EMA.h"
#include "WMA.h"

using namespace boost::assign;
using namespace boost::accumulators;
namespace Base
{
     template<typename DC>
     class SMA
     {
     public:
	  void operator () (DC &tar,DC &src,int step)
	       {
		    accumulator_set<typename DC::value_type, stats<tag::rolling_mean> > acc(tag::rolling_window::window_size = step);
		    
		    for(typename DC::iterator it=src.begin();it!=src.end();++it)
		    {
			 acc(*it);
			 tar.push_back(rolling_mean(acc));
		    }
	       }
     };
     template<typename DC>
     class EMA
     {
     public:
	  void operator () (DC &tar,DC &src,double fac)
	       {
		    accumulator_set<typename DC::value_type, stats<tag::ema> > acc(fact=fac);
		    
		    for(typename DC::iterator it=src.begin();it!=src.end();++it)
		    {
			 acc(*it);
			 tar.push_back(ema(acc));
		    }
	       }
     };
     template<typename DC>
     class WMA
     {
     public:
	  void operator () (DC &tar,DC &src,double fac)
	       {
		    accumulator_set<typename DC::value_type, stats<tag::wma> > acc(tag::rolling_window::window_size = fac);
		    
		    for(typename DC::iterator it=src.begin();it!=src.end();++it)
		    {
			 acc(*it);
			 tar.push_back(wma(acc));
		    }
	       }
     };
}

#endif
