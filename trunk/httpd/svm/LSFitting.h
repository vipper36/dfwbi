#ifndef LSFITTING_H
#define LSFITTING_H
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

using namespace boost::accumulators;
using namespace boost::numeric::ublas;
namespace lsf
{
  template <typename T>
  bool InvertMatrix(const matrix<T> &input, matrix<T> &inverse) 
  {
    typedef permutation_matrix<std::size_t> pmatrix;
    // create a working copy of the input
    matrix<T> A(input);
    // create a permutation matrix for the LU-factorization
    pmatrix pm(A.size1());

    // perform LU-factorization
    int res = lu_factorize(A,pm);
    if( res != 0 ) return false;

    // create identity matrix of "inverse"
    inverse.assign(identity_matrix<T>(A.size1()));

    // backsubstitute to get the inverse
    lu_substitute(A, pm, inverse);

    return true;
  }
  template <typename Type>
  class LSFitting
  {

  public:

    LSFitting( const matrix<Type> &xn, const vector<Type> &yn)
    {
      m_x=xn;
      m_y=yn;
      pars.resize(xn.size2());
    }
    ~LSFitting()
    {
    }

    void calcParams()
    {
      matrix<Type> xx=prod(trans (m_x),m_x);
      std::cout<<"xx:"<<std::endl;
      std::cout<<xx<<std::endl;
      vector<Type> xy=prod(trans (m_x),m_y);
      
      std::cout<<"xy:"<<std::endl;
      std::cout<<xy<<std::endl;

      matrix<Type> Invxx(xx.size1(),xx.size2());
      InvertMatrix(xx,Invxx);
      std::cout<<"inverse xx:"<<std::endl;
      std::cout<<Invxx<<std::endl;
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
    vector<Type> m_y;
    vector<Type> pars;     // fitted parameters
    Type  var;       // fitted functions

  };


}
// namespace itlab


#endif
// LSFITTING_H


