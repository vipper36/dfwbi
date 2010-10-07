#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsSoapJob.h"
#include <iostream>
#include <sstream>
#include "property.h"
NS_IMPL_ISUPPORTS1(nsSoapJob, nsISoapJob)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsSoapJob)

static nsModuleComponentInfo components[] =
{
     {
	  NS_SOAPJOB_CLASSNAME,
	  NS_SOAPJOB_CID,
	  NS_SOAPJOB_CONTRACTID,
	  nsSoapJobConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsSoapJobModule", components)




nsSoapJob::nsSoapJob()
:Id(0)
{
     /* member initializers and constructor code */
}

nsSoapJob::~nsSoapJob()
{
     /* destructor code */
}

/* attribute long id; */
NS_IMETHODIMP nsSoapJob::GetId(PRInt32 *aId)
{
     *aId=Id;
     return NS_OK;
}
NS_IMETHODIMP nsSoapJob::SetId(PRInt32 aId)
{
     Id=aId;
     return NS_OK;
}

/* attribute AUTF8String comment; */
NS_IMETHODIMP nsSoapJob::GetComment(nsACString & aComment)
{
     aComment=Comment;
     return NS_OK;
}
NS_IMETHODIMP nsSoapJob::SetComment(const nsACString & aComment)
{
     Comment=aComment;
     return NS_OK;
}

/* attribute AUTF8String seed; */
NS_IMETHODIMP nsSoapJob::GetSeed(nsACString & aSeed)
{
     aSeed=Seed;
     return NS_OK;
}
NS_IMETHODIMP nsSoapJob::SetSeed(const nsACString & aSeed)
{
     Seed=aSeed;
     return NS_OK;
}

/* attribute AUTF8String name; */
NS_IMETHODIMP nsSoapJob::GetName(nsACString & aName)
{
     aName=Name;
     return NS_OK;
}
NS_IMETHODIMP nsSoapJob::SetName(const nsACString & aName)
{
     Name=aName;
     return NS_OK;
}

/* attribute AUTF8String seedType; */
NS_IMETHODIMP nsSoapJob::GetSeedType(nsACString & aSeedType)
{
     aSeedType=SeedType;
     return NS_OK;
}
NS_IMETHODIMP nsSoapJob::SetSeedType(const nsACString & aSeedType)
{
     SeedType=aSeedType;
     return NS_OK;
}
