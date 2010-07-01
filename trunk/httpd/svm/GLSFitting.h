#ifndef GLSFITTING_H
#define GLSFITTING_H
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include "LSFitting.h"
using namespace boost::accumulators;
using namespace boost::numeric::ublas;
namespace lsf
{
  template <typename Type>
  class GLSFitting
  {

  public:

       GLSFitting( const matrix<Type> &xn, const vector<Type> &yn,const matrix<Type> &L)
    {
      m_x=xn;
      m_L=L;
      m_y=yn;
      pars.resize(xn.size2());
    }
    ~GLSFitting()
    {
    }

    void calcParams()
    {
	 matrix<Type> Lx=prod(m_L,m_x);;
	 vector<Type> Ly=prod(m_L,m_y);;


	 matrix<Type> xx=prod(trans (Lx),Lx);

	 vector<Type> xy=prod(trans (Lx),Ly);
	 

	 matrix<Type> Invxx(xx.size1(),xx.size2());
	 InvertMatrix(xx,Invxx);

	 pars=prod(Invxx,xy);
    }
    void calcVar()
    {
      vector<Type> u=m_y-prod(m_x,pars);
      accumulator_set<Type, stats<tag::variance > > acc;

      for(typename vector<Type>::iterator it=u.begin();it!=u.end();++it)
	{
	  acc(*it);
	}
      var=variance(acc);
    }
    vector<Type> getParams() const
    {
      return pars;
    }
    Type getVar() const
    {
      return var;
    }
	  
  private:
    matrix<Type> m_x;
    matrix<Type> m_L;
    vector<Type> m_y;
    vector<Type> pars;     // fitted parameters
    Type  var;       // fitted functions

  };


}



#endif
// GLSFITTING_H


