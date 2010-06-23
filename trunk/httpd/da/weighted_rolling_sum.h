#ifndef __WEIGHTED_ROLLING_SUM_H__
#define __WEIGHTED_ROLLING_SUM_H__

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/rolling_window.hpp>

namespace boost { namespace accumulators
     {

	  namespace impl
	  {

	       template<typename Sample>
	       struct weight_rolling_sum_impl
		    : accumulator_base
	       {
		    typedef Sample result_type;

		    template<typename Args>
		    weight_rolling_sum_impl(Args const &args)
			 : sum_(args[sample | Sample()])
			 {}

		    template<typename Args>
		    void operator ()(Args const &args)
			 {
			      iterator_range<typename circular_buffer<Sample>::const_iterator> win=rolling_window_plus1(args);
			      if(is_rolling_window_plus1_full(args))
			      {

				   for(typename iterator_range<typename circular_buffer<Sample>::const_iterator>::iterator it=win.begin();it!=win.end();++it)
				   {
					this->sum_ -= *it;
				   }
			      }
			      this->sum_ += args[sample]*win.size();

			      
			 }

		    template<typename Args>
		    result_type result(Args const &args) const
			 {
			      return this->sum_;
			 }

	       private:
		    Sample sum_;
	       };
	  } // namespace impl


	  namespace tag
	  {
	       struct weight_rolling_sum
		    : depends_on< rolling_window_plus1 >
	       {
		    /// INTERNAL ONLY
		    ///
		    typedef accumulators::impl::weight_rolling_sum_impl< mpl::_1 > impl;

#ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
		    /// tag::rolling_window::window_size named parameter
		    static boost::parameter::keyword<tag::rolling_window_size> const window_size;
#endif
	       };
	  } // namespace tag


	  namespace extract
	  {
	       extractor<tag::weight_rolling_sum> const weight_rolling_sum = {};

	       BOOST_ACCUMULATORS_IGNORE_GLOBAL(weight_rolling_sum)
	  }

	  using extract::weight_rolling_sum;

     }
} // namespace boost::accumulators

#endif
