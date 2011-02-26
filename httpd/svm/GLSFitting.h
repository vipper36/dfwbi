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
namespace ba = boost::accumulators;
namespace bu = boost::numeric::ublas;
namespace lsf
{
  template <typename Type>
  class GLSFitting
  {

  public:

       GLSFitting( const bu::matrix<Type> &xn, const vector<Type> &yn,const bu::matrix<Type> &L)
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
	 bu::matrix<Type> Lx=bu::prod(m_L,m_x);
	 bu::vector<Type> Ly=bu::prod(m_L,m_y);


	 bu::matrix<Type> xx=bu::prod(bu::trans (Lx),Lx);

	 bu::vector<Type> xy=bu::prod(bu::trans (Lx),Ly);
	 

	 bu::matrix<Type> Invxx(xx.size1(),xx.size2());
	 InvertMatrix(xx,Invxx);

	 pars=bu::prod(Invxx,xy);
    }
    void calcVar()
    {
      bu::matrix<Type> Lx=bu::prod(m_L,m_x);
      bu::vector<Type> Ly=bu::prod(m_L,m_y);
      bu::vector<Type> u=Ly-bu::prod(Lx,pars);

      ba::accumulator_set<Type, ba::stats<ba::tag::variance > > acc;

      for(typename vector<Type>::iterator it=u.begin();it!=u.end();++it)
	{
	  acc(*it);
	}
      var=ba::variance(acc);
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
    bu::matrix<Type> m_x;
    bu::matrix<Type> m_L;
    bu::vector<Type> m_y;
    bu::vector<Type> pars;     // fitted parameters
    Type  var;       // fitted functions

  };


}



#endif
// GLSFITTING_H


