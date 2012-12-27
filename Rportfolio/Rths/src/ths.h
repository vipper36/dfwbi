#ifndef _mypackage_RCPP_THS_H
#define _mypackage_RCPP_THS_H
#include <Rcpp.h>
RcppExport void thsInit(SEXP dir);
RcppExport SEXP thsDay(SEXP code,SEXP marcket,SEXP start);
RcppExport SEXP thsMin(SEXP code,SEXP marcket,SEXP start);
RcppExport SEXP thsMinOfDay(SEXP code,SEXP marcket,SEXP day);
#endif
