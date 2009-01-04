#include "soci.h"
#include "soci-oracle.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <exception>

using namespace soci;
using namespace std;

bool getName(string &name)
{
     cout << "Enter name: ";
     return cin >> name;
}

int main()
{
    try
    {
	 session sql(oracle, "service=ORCL user=fly password=fly");

	 int count;
	 sql << "select count(*) from cat", into(count);

	 cout << "We have " << count << " table in the db.\n";
	 double textid;
	 double textseq;
	 string pubstat;
	 tm rtime;
	 sql << "select * from TB_TEXT_0042_INSERTED where rownum = 1",
	      into(textid),into(textseq),into(rtime),into(pubstat );
	 
	 cout << "The textid number is "<<textid << '\n';   
	 cout << "The textseq number is " << textseq << '\n';   
	 cout << "The rtime number is " << rtime.tm_year<<rtime.tm_mon<<rtime.tm_mday << '\n';   
	 cout << "The pubstat number is " << pubstat << '\n';   
    }
    catch (exception const &e)
    {
	 cerr << "Error: " << e.what() << '\n';
    }
}
