#include "nsISoapTask.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"

#include "nsStringAPI.h"
#include <vector>
#include <string>
#ifndef __NSSOAPTASK_H__
#define __NSSOAPTASK_H__
#define NS_SOAPTASK_CONTRACTID "@nyapc.com/XPCOM/nsSoapTask;1"
#define NS_SOAPTASK_CLASSNAME "nsSoapTask"

#define NS_SOAPTASK_CID NS_ISOAPTASK_IID
class nsSoapTask : public nsISoapTask
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISOAPTASK

  nsSoapTask();

private:
  ~nsSoapTask();
  PRInt32 JobId;
  nsCString Type;
  PRInt32 WrapId;
  PRInt32 WrapVer;
  PRInt32 TaskId;
  std::vector< std::pair<int,std::string> > urls;
protected:
  /* additional members */
};
#endif
