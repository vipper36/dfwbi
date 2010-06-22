#ifndef LSFITTING_H
#define LSFITTING_H

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>

using namespace boost::numeric::ublas;
namespace lsf
{

     template <typename Type>
     class LSFitting
     {

     public:

	  LSFitting( const matrix<Type> &xn, const vector<Type> &yn)
	       {
		    m_x=xn;
		    m_y=yn;
		    pars.resize(xn.m.size2());
	       }
	  ~LSFitting();

	  void calcParams()
	       {
		    matrix<Type> xx=prod(trans (m_x),m_x);
		    vector<Type> xy=prod(trans (m_x),m_y);
		    pars=prod((-xx),xy);
	       }
	  void calcVar()
	       {
		    vector<Type> u=m_y-prod(m_x,pars);
		    accumulator_set<Type, stats<tag::variance > > acc;
		    for(vector<Type>::iterator it=u.begin();it!=u.end();++it)
		    {
			 acc(*it);
		    }
		    var=variance(acc)
	       }
	  vector<Type> &getParams() const
	       {
		    return pars;
	       }
	  Type &getVar() const
	       {
		    return var;
	       }
	  
     private:
	  vector<Type> m_x;
	  matrix<Type> m_y;
	  vector<Type> pars;     // fitted parameters
	  Type  var;       // fitted functions

     };

     template <typename Type>
     LSFitting<Type>::~LSFitting()
     {
	  
     }


}
// namespace itlab


#endif
// LSFITTING_H


