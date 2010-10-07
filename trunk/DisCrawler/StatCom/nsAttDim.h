#include "nsIAttDim.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsIDOMDocument.h"
#include "nsIDOMNode.h"
#include "nsStringAPI.h"
#include <map>
#include <string>
#ifndef __NSATTDIM_H__
#define __NSATTDIM_H__
#define NS_ATTDIM_CONTRACTID "@nyapc.com/XPCOM/nsAttDim;1"
#define NS_ATTDIM_CLASSNAME "nsAttDim"

#define NS_ATTDIM_CID NS_IATTDIM_IID
class nsAttDim : public nsIAttDim
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIATTDIM

  nsAttDim();

private:
  ~nsAttDim();
  std::map<std::string,int> dims;
protected:
  /* additional members */
};
#endif
