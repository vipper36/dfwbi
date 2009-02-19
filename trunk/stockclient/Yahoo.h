#include <string>
class Yahoo :
{
  public:
     Yahoo ();
     ~Yahoo ();
     void update()
     std::string parseDate (std::string &);
     void parseHistory ();
     void parseQuote ();
     void cancelUpdate ();
     void parseFundamental ();
     void loadAllSymbols ();
     void createHistoryUrls (std::string &);
     void createAutoHistoryUrls (std::string &, std::string &);
     void createQuoteUrls (std::string &);
     void createFundamentalUrls (std::string &);
      
  public:
     void startDownload ();
     void fileDone (bool);
     void timeoutError ();
     void newStock ();
     void methodChanged (int);
     void allSymbolsChecked (bool);

  private:
     std::list<std::string> symbolList;
     std::string<std::string> SetList;
     std::string dataPath;
     std::list<std::string> fileList;
     std::list<std::string> monthList;
};
