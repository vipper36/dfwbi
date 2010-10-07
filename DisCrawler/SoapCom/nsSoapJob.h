#include "nsISoapJob.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"

#include "nsStringAPI.h"

#ifndef __NSSOAPJOB_H__
#define __NSSOAPJOB_H__
#define NS_SOAPJOB_CONTRACTID "@nyapc.com/XPCOM/nsSoapJob;1"
#define NS_SOAPJOB_CLASSNAME "nsSoapJob"

#define NS_SOAPJOB_CID NS_ISOAPJOB_IID
class nsSoapJob : public nsISoapJob
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISOAPJOB

  nsSoapJob();

private:
  ~nsSoapJob();
  PRInt32 Id;
  nsCString Comment;
  nsCString Seed;
  nsCString Name;
  nsCString SeedType;
protected:
  /* additional members */
};
#endif
