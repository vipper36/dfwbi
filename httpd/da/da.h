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
namespace ba = boost::accumulators;
namespace Base
{
     template<typename DC>
     class SMA
     {
     public:
	  void operator () (DC &tar,DC &src,int step)
	       {
		    ba::accumulator_set<typename DC::value_type, ba::stats<ba::tag::rolling_mean> > acc(ba::tag::rolling_window::window_size = step);
		    
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
		    ba::accumulator_set<typename DC::value_type, ba::stats<ba::tag::ema> > acc(ba::fact=fac);
		    
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
		    ba::accumulator_set<typename DC::value_type, ba::stats<ba::tag::wma> > acc(ba::tag::rolling_window::window_size = fac);
		    
		    for(typename DC::iterator it=src.begin();it!=src.end();++it)
		    {
			 acc(*it);
			 tar.push_back(wma(acc));
		    }
	       }
     };
}

#endif
