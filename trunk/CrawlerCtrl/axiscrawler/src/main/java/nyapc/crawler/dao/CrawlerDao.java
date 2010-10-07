package nyapc.crawler.dao;

import java.util.HashMap;
import java.util.List;

public interface CrawlerDao {
    int save(CrawlerAtt crawlerAtt);
	int del(int id);
	CrawlerAtt get(int id);
    List list();
}
