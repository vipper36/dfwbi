#ifndef __WMA_H__
#define __WMA_H__

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include "weighted_rolling_sum.h"
#include <boost/accumulators/statistics/rolling_count.hpp>

namespace boost { namespace accumulators
     {

	  namespace impl
	  {

	       ///////////////////////////////////////////////////////////////////////////////
	       // rolling_mean_impl
	       //    returns the unshifted results from the shifted rolling window
	       template<typename Sample>
	       struct wma_accumulator
		    : accumulator_base
	       {
		    typedef typename numeric::functional::average<Sample, std::size_t>::result_type result_type;

		    wma_accumulator(dont_care)
			 {}

		    template<typename Args>
		    result_type result(Args const &args) const
			 {
			      int count=rolling_count(args);
			      return weight_rolling_sum(args)/((count+1)*count/2);
			 }
	       };

	  } // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::rolling_mean
//
	  namespace tag
	  {
	       struct wma
		    : depends_on< weight_rolling_sum, rolling_count >
	       {
		    /// INTERNAL ONLY
		    ///
		    typedef accumulators::impl::wma_accumulator< mpl::_1 > impl;

#ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
		    /// tag::rolling_window::window_size named parameter
		    static boost::parameter::keyword<tag::rolling_window_size> const window_size;
#endif
	       };
	  } // namespace tag

///////////////////////////////////////////////////////////////////////////////
// extract::rolling_mean
//
	  namespace extract
	  {
	       extractor<tag::wma>  const wma = {};

	       BOOST_ACCUMULATORS_IGNORE_GLOBAL(wma)
	  }

	  using extract::wma;

     }
} // namespace boost::accumulators

#endif
