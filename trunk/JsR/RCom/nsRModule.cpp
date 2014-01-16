#include "mozilla/ModuleUtils.h"
#include "nsIClassInfoImpl.h"

#include "nsRCom.h"
NS_GENERIC_FACTORY_CONSTRUCTOR(nsRCom)

NS_DEFINE_NAMED_CID(NS_RCOM_CID);

// Build a table of ClassIDs (CIDs) which are implemented by this module. CIDs
// should be completely unique UUIDs.
// each entry has the form { CID, service, factoryproc, constructorproc }
// where factoryproc is usually NULL.
static const mozilla::Module::CIDEntry kRComCIDs[] = {
    { &kNS_RCOM_CID, false, NULL, nsRComConstructor },
    { NULL }
};
 
// Build a table which maps contract IDs to CIDs.
// A contract is a string which identifies a particular set of functionality. In some
// cases an extension component may override the contract ID of a builtin gecko component
// to modify or extend functionality.
static const mozilla::Module::ContractIDEntry kRComContracts[] = {
    { NS_RCOM_CONTRACTID, &kNS_RCOM_CID },
    { NULL }
};
 
// Category entries are category/key/value triples which can be used
// to register contract ID as content handlers or to observe certain
// notifications. Most modules do not need to register any category
// entries: this is just a sample of how you'd do it.
// @see nsICategoryManager for information on retrieving category data.
static const mozilla::Module::CategoryEntry kRComCategories[] = {
    { "RCom", "rcom", NS_RCOM_CONTRACTID },
    { NULL }
};
 
static const mozilla::Module kRComModule = {
    mozilla::Module::kVersion,
    kRComCIDs,
    kRComContracts,
    kRComCategories
};
 
// The following line implements the one-and-only "NSModule" symbol exported from this
// shared library.
NSMODULE_DEFN(nsRComModule) = &kRComModule;
 
