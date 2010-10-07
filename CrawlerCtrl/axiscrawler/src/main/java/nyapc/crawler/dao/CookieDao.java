package nyapc.crawler.dao;

import java.util.List;


public interface CookieDao {
	CookieAtt getCookie(int id);
	CookieAtt getCookieByJobId(int jid);
	int AddCookie(CookieAtt cook);
	void SetCookieStr(int jid,String cookie);
	List<Integer> getAllJobId();
}
