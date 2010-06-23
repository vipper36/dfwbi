#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>


namespace boost {                  
     namespace accumulators {   

	  BOOST_PARAMETER_KEYWORD(tag, fact)   

	  namespace impl {


	       template<typename Sample>
	       struct ema_accumulator
		    : accumulator_base
	       {
		    typedef Sample result_type;             // The type returned by result() below.
    
		    template<typename Args>      
		    ema_accumulator(Args const & args)
			 : sum(args[sample | Sample()]),
			   fac(args[fact | 1.0])// Maybe there is an initial value in the
			 {                                       // argument pack. ('sample' is defined in
			      
			      if(fac>1)
				   fac=1;
			 }                                       // sample.hpp, included above.)
    
		    template<typename Args>                 // The accumulate function is the function
		    void operator ()(Args const & args)     // call operator, and it also accepts an
			 {                                       // argument pack.
			      this->sum = this->sum*(1-fac)+args[sample]*fac;
			 }
    
		    result_type result(dont_care) const     // The result function will also be passed
			 {                                       // an argument pack, but we don't use it here,
			      return this->sum;                   // so we use "dont_care" as the argument type.
			 }
	       private:
		    Sample sum;
		    double fac;
	       };

	  }
	  namespace tag
	  {
	       struct ema
		    : depends_on<>
	       {
		    /// INTERNAL ONLY
		    ///
		    typedef accumulators::impl::ema_accumulator<mpl::_1> impl;
	       };

	  }

	  namespace extract
	  {
	       extractor<tag::ema> const ema = {};

	       BOOST_ACCUMULATORS_IGNORE_GLOBAL(ema)
	  }
	  using extract::ema;
     }
} // namespace boost::accumulators
