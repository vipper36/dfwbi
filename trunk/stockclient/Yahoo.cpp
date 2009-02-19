Yahoo::Yahoo ()
{

  monthList.append("Jan");
  monthList.append("Feb");
  monthList.append("Mar");
  monthList.append("Apr");
  monthList.append("May");
  monthList.append("Jun");
  monthList.append("Jul");
  monthList.append("Aug");
  monthList.append("Sep");
  monthList.append("Oct");
  monthList.append("Nov");
  monthList.append("Dec");
  
}

Yahoo::~Yahoo ()
{
}

void Yahoo::update ()
{
  SetList.clear();
  for (loop = 0; loop < (int) symbolList.count(); loop++)
  {
    fileCount++;
    std::string path = dataPath + "/";
    QFileInfo fi(symbolList[loop]);
    if (fi.extension(FALSE).length())
      path.append(fi.extension(FALSE).upper());
    else
      path.append("US");
    path.append("/");
    path.append(symbolList[loop]);
    if (! dir.exists(path, TRUE))
      continue;
      
    if (! method->currentText().compare("History"))
      createHistoryUrls(symbolList[loop]);
    else
    {
      if (! method->currentText().compare("Auto History"))
        createAutoHistoryUrls(path, symbolList[loop]);
      else
      {
        if (! method->currentText().compare("Quote"))
          createQuoteUrls(symbolList[loop]);
	else
          createFundamentalUrls(symbolList[loop]);
      }
    }
  }

  if (! url.count())
  {
    downloadComplete();
    std::string ss(tr("No symbols selected. Done"));
    printStatusLogMessage(ss);
    return;
  }
  
  currentUrl = url.first();

  startDownload();
}

void Yahoo::startDownload ()
{
  std::string s, ts;
  ts = "url";
  currentUrl->getData(ts, s);
  getFile(s);
  fileCounter++;
  progressBar->setProgress(fileCounter, fileCount);
}

void Yahoo::fileDone (bool d)
{
  if (d)
  {
//    std::string ss(tr("Network error aborting"));
//    printStatusLogMessage(ss);
//    printStatusLogMessage(stringDone);
//    downloadComplete();
//    return;
  }
  else
  {
    if (method->currentText().contains("History"))
      parseHistory();
    else
    {
      if (method->currentText().contains("Quote"))
        parseQuote();
      else
        parseFundamental();
    }
  }

  currentUrl = url.next();
  if (! currentUrl)
  {
    downloadComplete();
    printStatusLogMessage(stringDone);
    printErrorList();
    progressBar->reset();
    return;
  }

  errorLoop = 0;
  startDownload();    
}

void Yahoo::timeoutError ()
{
  std::string ts = "symbol";
  std::string ts2;
  errorLoop++;
  if (errorLoop == retrySpin->value())
  {
    currentUrl->getData(ts, ts2);
    std::string ss = tr("Timeout: retry limit skipping") + " " + ts2 + " " + tr("skipped");
    printStatusLogMessage(ss);
    errorList.append(ts2);
    
    errorLoop = 0;
    currentUrl = url.next();
    if (! currentUrl)
    {
      downloadComplete();
      printStatusLogMessage(stringDone);
      printErrorList();
      return;
    }

    startDownload();
  }
  else
  {
    currentUrl->getData(ts, ts2);
    std::string ss = tr("Timeout: retry") + " " + QString::number(errorLoop + 1) + " " + ts2;
    printStatusLogMessage(ss);
    startDownload();
  }
}

void Yahoo::parseHistory ()
{
  if (! data.length())
    return;

  if (data.contains("No data available"))
    return;

  if (data.contains("No Prices in this date range"))
    return;
    
  // strip off the header
  std::string s = "Date,Open,High,Low,Close";
  int p = data.find(s, 0, TRUE);
  if (p != -1)
    data.remove(0, p + s.length());

  QFile f(file);
  if (! f.open(IO_WriteOnly))
    return;
  QTextStream stream(&f);
  stream << data;
  f.close();

  f.setName(file);
  if (! f.open(IO_ReadOnly))
    return;
  stream.setDevice(&f);

  s = dataPath + "/";
  std::string ts = "symbol";
  std::string ts2;
  currentUrl->getData(ts, ts2);
  QFileInfo fi(ts2);
  if (fi.extension(FALSE).length())
    s.append(fi.extension(FALSE).upper());
  else
    s.append("US");
  s.append("/");
  s.append(ts2);

  if (plug.open(s, chartIndex))
  {
    std::string ss(tr("Could not open db"));
    printStatusLogMessage(ss);
    f.close();
    return;
  }

  std::string fn = ts2;

  // verify if this chart can be updated by this plugin
  DBIndexItem item;
  chartIndex->getIndexItem(fn, item);
  item.getSymbol(s);  
  if (! s.length())
  {
    if (plug.createNewStock())
    {
      f.close();
      plug.close();
      return;
    }

    chartIndex->getIndexItem(fn, item);

    item.setSymbol(ts2);
    item.setTitle(ts2);
    item.setQuotePlugin(pluginName);

    chartIndex->setIndexItem(fn, item);
  }

//  item.getQuotePlugin(s);
//  if (s.compare(pluginName))
//  {
//    s = ts2 + " - " + tr("skipping update. Source does not match destination");
//    printStatusLogMessage(s);
//    f.close();
//    plug.close();
//    return;
//  }

  while(stream.atEnd() == 0)
  {
    ts = stream.readLine();
    stripJunk(ts, s);

    QStringList l = QStringList::split(",", s, FALSE);
    if (l.count() < 5)
      continue;

    // date
    std::string date = parseDate(l[0]);
    Bar bar;
    if (bar.setDate(date))
    {
      std::string ss = ts2 + " - " + tr("Bad date") + " " + l[0];
      qDebug("Yahoo::parseHistory: %s - Bad date %s", ts2.latin1(), l[0].latin1());
      printStatusLogMessage(ss);
      continue;
    }

    if (setTFloat(l[1], FALSE))
      continue;
    else
      bar.setOpen(tfloat);

    if (setTFloat(l[2], FALSE))
      continue;
    else
      bar.setHigh(tfloat);

    if (setTFloat(l[3], FALSE))
      continue;
    else
      bar.setLow(tfloat);

    if (setTFloat(l[4], FALSE))
      continue;
    else
      bar.setClose(tfloat);

    if (l.count() >= 6)
    {
      if (setTFloat(l[5], FALSE))
        continue;
      else
        bar.setVolume(tfloat);
    }

    if (bar.verify())
      continue;

    // adjusted close
    if (adjustment->isChecked())
    {
      double adjclose = 0;
      if (l.count() >= 7)
      {
	if (setTFloat(l[6], FALSE))
	  continue;
	else
	  adjclose = tfloat;
	// apply yahoo's adjustments through all the data, not just closing price
	// i.e. adjust for stock splits and dividends
	float factor = bar.getClose() / adjclose;
	if (factor != 1)
	{
	  bar.setHigh(bar.getHigh() / factor);
	  bar.setLow(bar.getLow() / factor);
	  bar.setOpen(bar.getOpen() / factor);
	  bar.setClose(bar.getClose() / factor);
	  bar.setVolume(bar.getVolume() * factor);
	}
      }
    }

    plug.setBar(bar);

    emit signalWakeup();
  }

  f.close();
  plug.close();
}

void Yahoo::parseQuote ()
{
  if (! data.length())
    return;

  QFile f(file);
  if (! f.open(IO_WriteOnly))
    return;
  QTextStream stream(&f);
  stream << data;
  f.close();

  f.setName(file);
  if (! f.open(IO_ReadOnly))
    return;
  stream.setDevice(&f);

  std::string s = dataPath + "/";
  std::string ts = "symbol";
  std::string ts2;
  currentUrl->getData(ts, ts2);
  QFileInfo fi(ts2);
  if (fi.extension(FALSE).length())
    s.append(fi.extension(FALSE).upper());
  else
    s.append("US");
  s.append("/");
  s.append(ts2);
  
  if (plug.open(s, chartIndex))
  {
    std::string ss(tr("Could not open db"));
    printStatusLogMessage(ss);
    f.close();
    return;
  }

  std::string fn = ts2;

  // verify if this chart can be updated by this plugin
  DBIndexItem item;
  chartIndex->getIndexItem(fn, item);
  item.getSymbol(s);    
  if (! s.length())
  {
    if (plug.createNewStock())
    {
      f.close();
      plug.close();
      return;
    }

    chartIndex->getIndexItem(fn, item);

    item.setSymbol(ts2);
    item.setTitle(ts2);
    item.setQuotePlugin(pluginName);

    chartIndex->setIndexItem(fn, item);
  }

//  item.getQuotePlugin(s);
//  if (s.compare(pluginName))
//  {
//    s = ts2 + " - " + tr("skipping update. Source does not match destination");
//    printStatusLogMessage(s);
//    f.close();
//    plug.close();
//    return;
//  }

  while(stream.atEnd() == 0)
  {
    ts = stream.readLine();
    stripJunk(ts, s);

    QStringList l = QStringList::split(",", s, FALSE);
    if (l.count() < 9 || l.count() > 10)
      continue;

    // get date
    QStringList l2 = QStringList::split("/", l[3], FALSE);
    if (l2.count() != 3)
      continue;
    std::string date = l2[2];
    if (l2[0].toInt() < 10)
      date.append("0");
    date.append(l2[0]);
    if (l2[1].toInt() < 10)
      date.append("0");
    date.append(l2[1]);
    date.append("000000");

    Bar bar;
    if (bar.setDate(date))
    {
      std::string ss = ts2 + " - " + tr("Bad date") + " " + l[3];
      qDebug("Yahoo::parseQuote: %s - Bad date %s", ts2.latin1(), l[3].latin1());
      printStatusLogMessage(ss);
      continue;
    }

    if (setTFloat(l[6], FALSE))
      continue;
    else
      bar.setOpen(tfloat);

    if (setTFloat(l[7], FALSE))
      continue;
    else
      bar.setHigh(tfloat);

    if (setTFloat(l[8], FALSE))
      continue;
    else
      bar.setLow(tfloat);

    if (setTFloat(l[2], FALSE))
      continue;
    else
      bar.setClose(tfloat);

    if (l.count() == 10)
    {
      if (setTFloat(l[9], FALSE))
        continue;
      else
        bar.setVolume(tfloat);
    }

    if (bar.verify())
      continue;
      
    plug.setBar(bar);

    emit signalWakeup();
  }

  f.close();
  plug.close();
}

std::string Yahoo::parseDate (std::string &d)
{
  std::string s;

  QStringList l = QStringList::split("-", d, FALSE);
  if (l.count() != 3)
    return s;

  bool ok;
  int t = l[1].toInt(&ok);
  if (ok)
  {
    // new date format YYYY-MM-DD
    s = l[0] + l[1] + l[2];
    s.append("000000");
    return s;
  }

  // old date format

  // get year
  s = l[2];
  if (s.toInt() > 29)
    s.prepend("19");
  else
    s.prepend("20");

  // get month
  t = monthList.findIndex(l[1]);
  if (t == -1)
    return s;
  if (t < 9)
    s.append("0" + QString::number(t + 1));
  else
    s.append(QString::number(t + 1));

  // get day
  if (l[0].toInt() < 10)
    s.append("0");
  s.append(l[0]);
  s.append("000000");

  return s;
}

void Yahoo::loadSettings ()
{
  QSettings settings;
  settings.beginGroup("/Qtstalker/Yahoo plugin");

  std::string s = settings.readEntry("/Adjustment", "0");
  adjustment->setChecked(s.toInt());
  
  s = settings.readEntry("/Method", "History");
  setMethod(s);
  
  s = settings.readEntry("/Retries", "3");
  retrySpin->setValue(s.toInt());
  
  s = settings.readEntry("/Timeout", "15");
  timeoutSpin->setValue(s.toInt());
  
  s = settings.readEntry("/AllSymbols", "1");
  allSymbols->setChecked(s.toInt());
  allSymbolsChecked(s.toInt());
  
  settings.endGroup();
}

void Yahoo::saveSettings ()
{
  QSettings settings;
  settings.beginGroup("/Qtstalker/Yahoo plugin");
  
  settings.writeEntry("/Adjustment", QString::number(adjustment->isChecked()));
  settings.writeEntry("/Method", method->currentText());
  settings.writeEntry("/Retries", retrySpin->text());
  settings.writeEntry("/Timeout", timeoutSpin->text());
  settings.writeEntry("/AllSymbols", QString::number(allSymbols->isChecked()));

  settings.endGroup();
}

void Yahoo::printErrorList ()
{
  int loop;
  for (loop = 0; loop < (int) errorList.count(); loop++)
  {
    std::string s = tr("Unable to download") + " " + errorList[loop];
    printStatusLogMessage(s);
  }
}	

void Yahoo::cancelUpdate ()
{
  if (op)
  {
    timer->stop();
    op->stop();
  }
  
  downloadComplete();
  printStatusLogMessage(stringCanceled);
  progressBar->reset();
}

void Yahoo::parseFundamental ()
{
  if (! data.length())
    return;

  if (data.contains("data available"))
    return;
    
  QStringList l = QStringList::split("yfnc_tablehead1", data, FALSE);
  int loop;
  Setting fund;
  for (loop = 1; loop < (int) l.count(); loop++)
  {
    std::string k = l[loop];
    int p = k.find(">", 0, TRUE);
    if (p == -1)
      continue;
    p++;
    k.remove(0, p);
    p = k.find("<", 0, TRUE);
    if (p == -1)
      continue;
    k.truncate(p);
    
    if (k.contains("&sup"))
      k.truncate(k.length() - 6);
    if (k.contains("&amp"))
      k.remove(k.find("&", 0, TRUE), 5);
    k = k.stripWhiteSpace();
    if (! k.length())
      continue;
    
    std::string d = l[loop];
    p = d.find("yfnc_tabledata1", 0, TRUE);
    if (p == -1)
      continue;
    p = d.find(">", p, TRUE);
    if (p == -1)
      continue;
    p++;
    d.remove(0, p);
    p = d.find("<", 0, TRUE);
    if (p == -1)
      continue;
    d.truncate(p);
    d = d.stripWhiteSpace();  
    if (! d.length())
      continue;

    fund.setData(k, d);
  }
      
  std::string s = dataPath + "/";
  std::string ts = "symbol";
  std::string ts2;
  currentUrl->getData(ts, ts2);
  QFileInfo fi(ts2);
  if (fi.extension(FALSE).length())
    s.append(fi.extension(FALSE).upper());
  else
    s.append("US");
  s.append("/");
  s.append(ts2);
  
  if (plug.open(s, chartIndex))
  {
    std::string ss(tr("Could not open db"));
    printStatusLogMessage(ss);
    return;
  }

  std::string fn = ts2;
  
  // verify if this chart can be updated by this plugin
  DBIndexItem item;
  chartIndex->getIndexItem(fn, item);
  item.getSymbol(s);  
  if (! s.length())
  {
    if(plug.createNewStock())
    {
      plug.close();
      return;
    }

    chartIndex->getIndexItem(fn, item);

    item.setQuotePlugin(pluginName);
    item.setSymbol(ts2);
    std::string title = ts2;
    int p = data.find("yfnc_leftnav1", 0, TRUE);
    if (p != -1)
    {
      p = data.find("b>", p, TRUE);
      if (p != -1)
      {
        p = p + 2;
        int p2 = data.find("<", p, TRUE);
        if (p2 != -1)
	{
	  s = data.mid(p, p2 - p);
	  if (s.length())
            title = s;
	}
      }
    }
    item.setTitle(title);

    chartIndex->setIndexItem(fn, item);
  }
  else
  {
    std::string s2;
    item.getTitle(s2);
    if (! s.compare(s2))
    {
      int p = data.find("yfnc_leftnav1", 0, TRUE);
      if (p != -1)
      {
        p = data.find("b>", p, TRUE);
        if (p != -1)
        {
          p = p + 2;
          int p2 = data.find("<", p, TRUE);
          if (p2 != -1)
	  {
            s = data.mid(p, p2 - p);
	    if (s.length())
            {
              item.setTitle(s);
              chartIndex->setIndexItem(fn, item);
            }
	  }
	}
      }
    }
  }
  
//  item.getQuotePlugin(s);
//  if (s.compare(pluginName))
//  {
//    s = ts2 + " - " + tr("skipping update. Source does not match destination");
//    printStatusLogMessage(s);
//    plug.close();
//    return;
//  }

  // include date of this update
  QDate dt = QDate::currentDate();
  ts = "updateDate";
  ts2 = dt.toString("yyyy-MM-dd");
  fund.setData(ts, ts2);
  fund.getString(ts2);
  ts = "Fundamentals";
  chartIndex->setFundamentals(fn, ts2);
    
  plug.close();

  emit signalWakeup();
}

void Yahoo::loadAllSymbols ()
{
  symbolList.clear();
  
  QDir dir(dataPath);
  int loop;
  for (loop = 2; loop < (int) dir.count(); loop++)
  {
    std::string s = dir.absPath() + "/" + dir[loop];
    QFileInfo fi(s);
    if (fi.isDir())
    {
      int loop2;
      QDir dir2(s);
      for (loop2 = 2; loop2 < (int) dir2.count(); loop2++)
        symbolList.append(dir2[loop2]);
    }
  }
  
  symbolList.sort();
}

void Yahoo::createHistoryUrls (std::string &d)
{
  if (sdate->date().daysTo(edate->date()) > 199) 
  { 
    QDate tsdate = sdate->date();
    QDate tedate = sdate->date();
	  
    while (tsdate <= edate->date())
    {
      tsdate = tedate;
      tedate = tsdate.addDays(199);
      if (tedate.dayOfWeek() == 6)
        tedate = tedate.addDays(-1);
      else
      {
        if (tedate.dayOfWeek() == 7)
          tedate = tedate.addDays(-2);
      }
            
      if (tedate > edate->date())
	tedate = edate->date();
	    
      std::string s = "http://ichart.yahoo.com/table.csv?s=";
      s.append(d);
      s.append("&a=");
      s.append(QString::number(tsdate.month() - 1));
      s.append("&b=");
      s.append(tsdate.toString("dd"));
      s.append("&c=");
      s.append(tsdate.toString("yy"));
      s.append("&d=");
      s.append(QString::number(tedate.month() - 1));
      s.append("&e=");
      s.append(tedate.toString("dd"));
      s.append("&f=");
      s.append(tedate.toString("yy"));
      s.append("&g=d&q=q&y=0&x=.csv");
	    
      Setting *set = new Setting;
      std::string ts = "url";
      set->setData(ts, s);
      ts = "symbol";
      set->setData(ts, d);
      url.append(set);
	    
      if (tedate == edate->date())
        break;
    }
  }
  else 
  { 
    std::string s = "http://ichart.yahoo.com/table.csv?s=";
    s.append(d);
    s.append("&a=");
    s.append(QString::number(sdate->date().month() - 1));
    s.append("&b=");
    s.append(sdate->date().toString("dd"));
    s.append("&c=");
    s.append(sdate->date().toString("yy"));
    s.append("&d=");
    s.append(QString::number(edate->date().month() - 1));
    s.append("&e=");
    s.append(edate->date().toString("dd"));
    s.append("&f=");
    s.append(edate->date().toString("yy"));
    s.append("&g=d&q=q&y=0&x=.csv");
    
    Setting *set = new Setting;
    std::string ts = "url";
    set->setData(ts, s);
    ts = "symbol";
    set->setData(ts, d);
    url.append(set);
  }
}

void Yahoo::createAutoHistoryUrls (std::string &path, std::string &d)
{
  if (plug.open(path, chartIndex))
  {
    qDebug("Yahoo::createAutoHistoryUrls:could not open db");
    return;
  }

  QFileInfo fi(path);
  std::string fn = fi.fileName();

  // verify if this chart can be updated by this plugin
  std::string s;
  DBIndexItem item;
  chartIndex->getIndexItem(fn, item);
  item.getQuotePlugin(s);
  if (! s.length())
  {
    item.setQuotePlugin(pluginName);
    chartIndex->setIndexItem(fn, item);
  }
//  else
//  {
//    if (s.compare(pluginName))
//    {
//      qDebug("Yahoo::createAutoHistoryUrls:source not same as destination");
//      plug.close();
//      return;
//    }
//  }

  QDate edt = QDate::currentDate();        
  if (edt.dayOfWeek() == 6)
    edt = edt.addDays(-1);
  else
  {
    if (edt.dayOfWeek() == 7)
      edt = edt.addDays(-2);
  }
	
  Bar bar;
  plug.getLastBar(bar);
  if (bar.getEmptyFlag())
  {
    QDate dt = edt;
    dt = dt.addDays(-365);
    s = dt.toString("yyyyMMdd000000");
    bar.setDate(s);
  }

  QDateTime dt;
  bar.getDate(dt);
  if (dt.date() == edt)
  {
//    qDebug("Yahoo::createAutoHistoryUrls:barDate == endDate");
    plug.close();
    return;
  }
		
  s = "http://ichart.yahoo.com/table.csv?s=";
  s.append(d);
  s.append("&a=");
  s.append(QString::number(dt.date().month() - 1));
  s.append("&b=");
  s.append(dt.toString("dd"));
  s.append("&c=");
  s.append(dt.toString("yy"));
  s.append("&d=");
  s.append(QString::number(edt.month() - 1));
  s.append("&e=");
  s.append(edt.toString("dd"));
  s.append("&f=");
  s.append(edt.toString("yy"));
  s.append("&g=d&q=q&y=0&x=.csv");
	
  plug.close();
  
  Setting *set = new Setting;
  std::string ts = "url";
  set->setData(ts, s);
  ts = "symbol";
  set->setData(ts, d);
  url.append(set);
}

void Yahoo::createQuoteUrls (std::string &d)
{
  // multiple quotes: download.finance.yahoo.com/d/quotes.csv?s=IBM+RHAT+SCOX+MSFT+GOLD&f=sl1d1t1c1ohgv 
  // multiple close only: download.finance.yahoo.com/d/quotes.csv?s=IBM+RHAT+SCOX+MSFT+GOLD&f=sl1
  // URLPrefix = "http://download.finance.yahoo.com/d/quotes.csv?s=";
  // URLPostfix = "&f=snl1d1t1c1ohgv&e=.csv";	
  std::string s = "http://download.finance.yahoo.com/d/quotes.csv?s=";
  s.append(d);
  s.append("&f=snl1d1t1c1ohgv&e=.csv");
  
  Setting *set = new Setting;
  std::string ts = "url";
  set->setData(ts, s);
  ts = "symbol";
  set->setData(ts, d);
  url.append(set);
}

void Yahoo::createFundamentalUrls (std::string &d)
{
  std::string s = "http://finance.yahoo.com/q/ks?s=" + d;
  Setting *set = new Setting;
  std::string ts = "url";
  set->setData(ts, s);
  ts = "symbol";
  set->setData(ts, d);
  url.append(set);
}

void Yahoo::newStock ()
{
  bool ok = FALSE;
  std::string symbols = QInputDialog::getText(tr("New Yahoo Symbols"),
                                          tr("Enter symbols to add. Note: separate symbols with a space"),
				          QLineEdit::Normal,
				          QString::null,
				          &ok,
				          this);
  if (! symbols.length())
    return;

  QStringList l = QStringList::split(" ", symbols, FALSE);
  
  std::string s;
  config.getData(Config::DataPath, s);
  s.append("/Stocks");
  QDir dir(s);
  if (! dir.exists(s))
  {
    if (! dir.mkdir(s))
    {
      qDebug("YahooDialog::newStock: Unable to create %s directory", s.latin1());
      return;
    }
  }
  
  if (! dir.exists(dataPath))
  {
    if (! dir.mkdir(dataPath))
    {
      qDebug("YahooDialog::newStock: Unable to create %s directory", dataPath.latin1());
      return;
    }
  }
  
  int loop;
  for (loop = 0; loop < (int) l.count(); loop++)
  {
    std::string exchange;
    std::string s = dataPath + "/";
    QFileInfo fi(l[loop]);
    if (fi.extension(FALSE).length())
    {
      exchange = fi.extension(FALSE).upper();
      s.append(fi.extension(FALSE).upper());
      if (! dir.exists(s, TRUE))
      {
        if (! dir.mkdir(s))
	{
          qDebug("YahooDialog::newStock: Unable to create %s directory", s.latin1());
          continue;
	}
      }
    }
    else
    {
      s.append("US");
      if (! dir.exists(s, TRUE))
      {
        if (! dir.mkdir(s))
	{
          qDebug("YahooDialog::newStock: Unable to create %s directory", s.latin1());
          continue;
	}
      }
    }
    s.append("/");
    s.append(l[loop]);
    if (dir.exists(s, TRUE))
      continue;

    if (plug.open(s, chartIndex))
    {
      qDebug("YahooDialog::newStock: could not open db %s", s.latin1());
      plug.close();
      continue;
    }
          
    plug.createNewStock();

    QFileInfo fi2(s);
    std::string fn = fi2.fileName();
    DBIndexItem item;
    chartIndex->getIndexItem(fn, item);
    getExchange(exchange, s);
    item.setExchange(s);
    chartIndex->setIndexItem(fn, item);

    plug.close();
  }
}

void Yahoo::setMethod (std::string d)
{
  if (! d.compare("History"))
  {
    method->setCurrentItem(0);
    methodChanged(0);
  }
  else
  {
    if (! d.compare("Auto History"))
    {
      method->setCurrentItem(1);
      methodChanged(1);
    }
    else
    {
      if (! d.compare("Quote"))
      {
        method->setCurrentItem(2);
        methodChanged(2);
      }
      else
      {
        method->setCurrentItem(3);
        methodChanged(3);
      }
    }
  }
}

void Yahoo::methodChanged (int d)
{
  switch (d)
  {
    case 0:
      adjustment->setEnabled(TRUE);
      sdate->setEnabled(TRUE);
      edate->setEnabled(TRUE);
      break;
    case 1:
      adjustment->setEnabled(TRUE);
      sdate->setEnabled(FALSE);
      edate->setEnabled(FALSE);
      break;
    case 2:
      adjustment->setEnabled(FALSE);
      sdate->setEnabled(FALSE);
      edate->setEnabled(FALSE);
      break;
    case 3:
      adjustment->setEnabled(FALSE);
      sdate->setEnabled(FALSE);
      edate->setEnabled(FALSE);
      break;
    default:
      break;
  }
}

void Yahoo::allSymbolsChecked (bool d)
{
  if (d)
  {
    list->setEnabled(FALSE);
    loadAllSymbols();
  }
  else
  {
    list->setEnabled(TRUE);
    list->getFile(fileList);
    int loop;
    symbolList.clear();
    for (loop = 0; loop < (int) fileList.count(); loop++)
    {
      QFileInfo fi(fileList[loop]);
      symbolList.append(fi.fileName());
    }
  }
}

void Yahoo::getExchange (std::string &ext, std::string &exchange)
{
  while (1)
  {
    if (! ext.compare("BA"))
    {
      exchange = QString::number(Exchange::BASE);
      break;
    }

    if (! ext.compare("VA"))
    {
      exchange = QString::number(Exchange::VASE);
      break;
    }

    if (! ext.compare("AX"))
    {
      exchange = QString::number(Exchange::AXSE);
      break;
    }

    if (! ext.compare("SA"))
    {
      exchange = QString::number(Exchange::SASE);
      break;
    }

    if (! ext.compare("TO"))
    {
      exchange = QString::number(Exchange::TOSE);
      break;
    }

    if (! ext.compare("V"))
    {
      exchange = QString::number(Exchange::TSXVE);
      break;
    }

    if (! ext.compare("SS"))
    {
      exchange = QString::number(Exchange::SSSE);
      break;
    }

    if (! ext.compare("SZ"))
    {
      exchange = QString::number(Exchange::SZSE);
      break;
    }

    if (! ext.compare("CO"))
    {
      exchange = QString::number(Exchange::COSE);
      break;
    }

    if (! ext.compare("PA"))
    {
      exchange = QString::number(Exchange::PASE);
      break;
    }

    if (! ext.compare("BE"))
    {
      exchange = QString::number(Exchange::BESE);
      break;
    }

    if (! ext.compare("BM"))
    {
      exchange = QString::number(Exchange::BMSE);
      break;
    }

    if (! ext.compare("DU"))
    {
      exchange = QString::number(Exchange::DUSE);
      break;
    }

    if (! ext.compare("F"))
    {
      exchange = QString::number(Exchange::FSE);
      break;
    }

    if (! ext.compare("HM"))
    {
      exchange = QString::number(Exchange::HMSE);
      break;
    }

    if (! ext.compare("HA"))
    {
      exchange = QString::number(Exchange::HASE);
      break;
    }

    if (! ext.compare("MU"))
    {
      exchange = QString::number(Exchange::MUSE);
      break;
    }

    if (! ext.compare("SG"))
    {
      exchange = QString::number(Exchange::SGSE);
      break;
    }

    if (! ext.compare("DE"))
    {
      exchange = QString::number(Exchange::XETRA);
      break;
    }

    if (! ext.compare("HK"))
    {
      exchange = QString::number(Exchange::HKSE);
      break;
    }

    if (! ext.compare("BO"))
    {
      exchange = QString::number(Exchange::BOSE);
      break;
    }

    if (! ext.compare("NS"))
    {
      exchange = QString::number(Exchange::NSEOI);
      break;
    }

    if (! ext.compare("JK"))
    {
      exchange = QString::number(Exchange::JKSE);
      break;
    }

    if (! ext.compare("TA"))
    {
      exchange = QString::number(Exchange::TASE);
      break;
    }

    if (! ext.compare("MI"))
    {
      exchange = QString::number(Exchange::MISE);
      break;
    }

    if (! ext.compare("KS"))
    {
      exchange = QString::number(Exchange::KSSE);
      break;
    }

    if (! ext.compare("KQ"))
    {
      exchange = QString::number(Exchange::KOSDAQ);
      break;
    }

    if (! ext.compare("MX"))
    {
      exchange = QString::number(Exchange::MXSE);
      break;
    }

    if (! ext.compare("AS"))
    {
      exchange = QString::number(Exchange::ASSE);
      break;
    }

    if (! ext.compare("NZ"))
    {
      exchange = QString::number(Exchange::NZSE);
      break;
    }

    if (! ext.compare("OL"))
    {
      exchange = QString::number(Exchange::OLSE);
      break;
    }

    if (! ext.compare("SI"))
    {
      exchange = QString::number(Exchange::SISE);
      break;
    }

    if (! ext.compare("BC"))
    {
      exchange = QString::number(Exchange::BCSE);
      break;
    }

    if (! ext.compare("BI"))
    {
      exchange = QString::number(Exchange::BISE);
      break;
    }

    if (! ext.compare("MF"))
    {
      exchange = QString::number(Exchange::MFIM);
      break;
    }

    if (! ext.compare("MC"))
    {
      exchange = QString::number(Exchange::MCCATS);
      break;
    }

    if (! ext.compare("MA"))
    {
      exchange = QString::number(Exchange::MASE);
      break;
    }

    if (! ext.compare("ST"))
    {
      exchange = QString::number(Exchange::STSE);
      break;
    }

    if (! ext.compare("SW"))
    {
      exchange = QString::number(Exchange::SWE);
      break;
    }

    if (! ext.compare("TWO"))
    {
      exchange = QString::number(Exchange::TWOOTC);
      break;
    }

    if (! ext.compare("TW"))
    {
      exchange = QString::number(Exchange::TWSE);
      break;
    }

    if (! ext.compare("L"))
    {
      exchange = QString::number(Exchange::LSE);
      break;
    }

    break;
  }
}

