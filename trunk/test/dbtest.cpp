#include "soci.h"
#include "soci-oracle.h"
#include "soci-mysql.h"
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
	 session sql(mysql, "db=urlCrawler user=root password=''");

	 int count;
	 sql << "select count(*) from URL_CRAWED", into(count);

	 
	 cout << "We have " << count << " table in the db.\n";
	

	 soci::rowset<soci::row> rs = (sql.prepare << "select url_hash,url_link,url_title from URL_CRAWED where url_stat='0'");
	 
	 for (soci::rowset<soci::row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
	 {
	       soci::row const& row = *it;
	       std::cout<<row.get<std::string>(1)<<"--"<<row.get<std::string>(2);
//	       sql<<"update URL_CRAWED set url_stat='1' where url_hash="<<row.get<std::string>(0);
	       sql<<"commit";
	  }

    }
    catch (exception const &e)
    {
	 cerr << "Error: " << e.what() << '\n';
    }
}
