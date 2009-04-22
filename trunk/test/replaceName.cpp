#include <boost/program_options/option.hpp>
#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/environment_iterator.hpp>
#include <boost/program_options/eof_iterator.hpp>
#include <boost/program_options/errors.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/version.hpp>
#include <boost/spirit.hpp>
#include <iostream>
#include <string>
#include <set>
#include <iterator>
#include <fstream>

using namespace std;
namespace po = boost::program_options;
namespace bs = boost::spirit;
void print(string ins)
{
     cout<<ins<<endl;
}

int main(int argc,char** argv)
{
     
     po::options_description desc("Allowed options");
     desc.add_options()
	  ("help,h", "show help message ")
	  ("field,d", po::value<string>(),"show help message ")
	  ("target,f", po::value<string>(), "set target file")
	  ("stoplist,s", po::value<string>(), "set stoplist file")
	  ("output,o", po::value<string>(), "set output file")
	  ;
     string targetfile;
     string stoplist;
     string outputfile;
     string fieldname; 
     po::variables_map vm;
     po::store(po::parse_command_line(argc, argv, desc), vm);
     po::notify(vm);    
     
     
     if (vm.count("help")) {
	  cout << desc << "\n";
	  return 1;
     }
     
     if (vm.count("target")) {
	  targetfile=vm["target"].as<string>();
     }
     if (vm.count("stoplist")) {
	  
	  stoplist=vm["stoplist"].as<string>();
     }
     if (vm.count("output")) {
	  outputfile=vm["output"].as<string>();
     }
     if (vm.count("field")) {
	  fieldname=vm["field"].as<string>();
     }
     ostream *outstr=NULL;
     ofstream outfile;
     if(outputfile.length()>0)
     {
	  outfile.open(outputfile.c_str());
	  outstr=&outfile;
     }else
     {
	  outstr=&cout;
     }
     if(fieldname.length()==0)
     {
	  fieldname="PERSON";
     }
     ifstream  targetStr( targetfile.c_str());
     ifstream  stoplistStr( stoplist.c_str());
     set<string> stopset;
     istream_iterator<string> eos;         // end-of-stream iterator
     istream_iterator<string> iit (stoplistStr);   // stdin iterator
     while(iit!=eos)
     {
	  stopset.insert(*iit);
	  iit++;
     }
     string tagstr="#DREFIELD "+fieldname+"=";
     stoplistStr.close();
     while(!targetStr.eof())
      {
	   string line;
	   string name;
	   getline(targetStr,line);
	   bs::parse_info<const char*> ret=parse(line.c_str(), bs::str_p(tagstr.c_str()) >> bs::ch_p('"') >> (+(~bs::ch_p('"')))[bs::assign_a(name)]>>bs::ch_p('"'), bs::cntrl_p);
	   bool parCor=ret.full;
	   if(parCor)
	   {
		set<string>::iterator it=stopset.find(name);
		if(it!=stopset.end())
		{
		     //   cout<<name<<endl;
		     continue;
		}
		
	   }
	   *outstr<<line<<endl;
      }
     targetStr.close();
     outfile.close();
     
//     for_each(stopset.begin(),stopset.end(),print);
     
     return 0;
     
}

