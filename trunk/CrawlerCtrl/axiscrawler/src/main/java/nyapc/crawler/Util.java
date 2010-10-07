package nyapc.crawler;


import java.text.DecimalFormat;
import java.text.NumberFormat;

import java.util.Calendar;

import java.util.regex.Matcher;
import java.util.regex.Pattern;


import java.io.BufferedReader;

import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;




public class Util {
	private static Log log = LogFactory.getLog(Util.class.getName());
	public static String strNotNull(String param) {
		if (param == null)
			return "";
		param = param.trim();
		return param;
	}

	public static String strNotNull(String param, String defaultStr) {
		if (param == null)
			return defaultStr;
		param = param.trim();
		return param;
	}

	public static String strNotBlank(String in) {
		Pattern p = Pattern.compile("\\s*|\t|\r|\n");
		Matcher m = p.matcher(in);
		return m.replaceAll("");
	}

	public static int str2int(String s) {
		return str2int(s, 0);
	}

	public static int str2int(String s, int defu) {
		if (s != null && !(s = s.trim()).equals("")) {
			try {
				defu = Integer.parseInt(s);
			} catch (Exception e) {
				//do nothing
			}
		}
		return defu;
	}

	public static long str2long(String s) {
		return str2long(s, 0);
	}

	public static long str2long(String s, long defu) {
		if (s != null && !(s = s.trim()).equals("")) {
			try {
				defu = Long.parseLong(s);
			} catch (Exception e) {
				//do nothing
			}
		}
		return defu;
	}

	public static float str2float(String s) {
		if (s == null)
			return 0;
		try {
			return Float.parseFloat(s.trim());
		} catch (Exception e) {
			return 0;
		}
	}

	public static double str2double(String s) {
		if (s == null) {
			return 0;
		} else {
			String temp = "";
			for (int i = 0; i < s.length(); i++) {
				if (!s.substring(i, i + 1).equals(",")) {
					temp += s.substring(i, i + 1);
				}
			}
			s = temp;
		}
		try {
			return Double.parseDouble(s.trim());
		} catch (Exception e) {
			return 0;
		}
	}

	public static String double2format(double toFormat) {
		NumberFormat numFormat;
		numFormat = NumberFormat.getInstance();
		((DecimalFormat) numFormat).applyPattern("#,##0.00;(#,##0.00)");
		return ((DecimalFormat) numFormat).format(toFormat);
	}

	public static String double2format(double dNumber, int type) {
		if (type == 0) {
			return double2format(dNumber);
		}

		NumberFormat numFormat;
		numFormat = NumberFormat.getInstance();
		((DecimalFormat) numFormat).applyPattern("###0.00;###0.00");
		return ((DecimalFormat) numFormat).format(dNumber);
	}

	public static java.util.Calendar getNow() {
		return java.util.Calendar.getInstance();
	}

	public static java.util.Calendar getCalendar(String date_str,int day) {
		java.util.Calendar cal = Util.str2calendar(date_str);
		cal.add(Calendar.DATE, day);
		return cal;
	}
	
	
	
	
	public static String getNow19() {
		return Util.calendar2str(Util.getNow(), true);
	}

	public static int calendar2unixtime(Calendar cal) {
		return (int) (cal.getTime().getTime() / 1000L);
	}

	public static Calendar unixtime2calendar(int unixtime) {
		java.util.Calendar ret = java.util.Calendar.getInstance();
		ret.setTime(new java.util.Date(unixtime * 1000L));
		return ret;
	}

	public static String calendar2str(java.util.Calendar t, boolean showTime) {
		String s = "";
		int i;
		if (t == null)
			return s;
		s += (t.get(java.util.Calendar.YEAR) + 0) + "-";
		i = (t.get(java.util.Calendar.MONTH) + 1);
		s += ((i < 10) ? "0" + i : i + "") + "-";
		i = (t.get(java.util.Calendar.DAY_OF_MONTH) + 0);
		s += ((i < 10) ? "0" + i : i + "") + " ";
		if (showTime) {
			i = t.get(java.util.Calendar.HOUR_OF_DAY);
			s += ((i < 10) ? "0" + i : i + "") + ":";
			i = t.get(java.util.Calendar.MINUTE);
			s += ((i < 10) ? "0" + i : i + "") + ":";
			i = t.get(java.util.Calendar.SECOND);
			s += ((i < 10) ? "0" + i : i + "");
		}
		return s.trim();
	}

	public static String calendar2str14(java.util.Calendar t) {
		String s = "";
		int i;
		//if(t==null)t=Util.getNow();
		if (t == null)
			return s;
		s += (t.get(java.util.Calendar.YEAR) + 0) + "";
		i = (t.get(java.util.Calendar.MONTH) + 1);
		s += ((i < 10) ? "0" + i : i + "") + "";
		i = (t.get(java.util.Calendar.DAY_OF_MONTH) + 0);
		s += ((i < 10) ? "0" + i : i + "") + "";
		i = t.get(java.util.Calendar.HOUR_OF_DAY);
		s += ((i < 10) ? "0" + i : i + "") + "";
		i = t.get(java.util.Calendar.MINUTE);
		s += ((i < 10) ? "0" + i : i + "") + "";
		i = t.get(java.util.Calendar.SECOND);
		s += ((i < 10) ? "0" + i : i + "");
		return s.trim();
	}

	public static java.util.Calendar str2calendar(String sData) {
		java.util.Calendar ret = getNow();
		try {
			sData = sData.trim();
			if (sData.length() == 10) {
				sData += " 00:00:00";
			}
			ret = (Calendar.getInstance());
			String temp = sData;
			ret.set(str2int(temp.substring(0, 4)),
					str2int(temp.substring(5, 7)) - 1, str2int(temp.substring(
							8, 10)), str2int(temp.substring(11, 13)),
					str2int(temp.substring(14, 16)),
					str2int(temp.substring(17)));
		} catch (Exception e) {
			ret = null;
		}
		return ret;
	}

	public static String escape(String src) {
		if (!(src instanceof String)) {
			return null;
		}

		byte[] b = null;
		b = src.getBytes();
		StringBuffer tmp = new StringBuffer();
		tmp.ensureCapacity(src.length() * 9);
		for (int i = 0; i < b.length; i++) {
			if (Character.isDigit(b[i]) || Character.isLowerCase(b[i])
					|| Character.isUpperCase(b[i]))
				tmp.append((char) b[i]);
			else
				tmp.append("%" + getHexString(b[i]));
		}
		return tmp.toString();
	}

	private static String getHexString(byte b) {
		String hexStr = Integer.toHexString(b).toUpperCase();
		int m = hexStr.length();
		if (m < 2) {
			hexStr = "0" + hexStr;
		} else {
			hexStr = hexStr.substring(m - 2);
		}
		return hexStr;
	}

	public static String escape2(String src) {
		return Util.escape(Util.escape(src));
	}

	public static String escape3(String src) {
		return Util.escape(Util.escape(Util.escape(src)));
	}

	public static String dmy2ymd(String sData) {
		String rtn = "";
		try {
			if ("".equals(sData)) {
				rtn = "";
			} else if (sData.length() < 10) {
				rtn = "";
			} else {
				//rtn = sData.substring(6,10) + "-" + sData.substring(3,5) +"-"+ sData.substring(0,2);
				rtn = sData;
			}
		} catch (Exception e) {
			log.debug(e.toString());
		}
		return rtn;
	}

	public static String getUrlContent(String s, String s_ch, String t_ch)
			throws Exception {
		java.net.URL _url = new java.net.URL(s);
		java.net.HttpURLConnection huc = (java.net.HttpURLConnection) _url
				.openConnection();
		huc.setReadTimeout(300000);
		huc.setConnectTimeout(300000);
		return getInputStreamContent(huc.getInputStream(), s_ch, t_ch);
	}

	public static String getInputStreamContent(InputStream in, String s_ch,
			String t_ch) throws Exception {
		BufferedReader BR = null;
		try {
			BR = new BufferedReader(new InputStreamReader(in, s_ch));
			char[] c = new char[20 << 10];
			StringBuffer sb_in = new StringBuffer();
			int len = 0;
			while ((len = BR.read(c)) > 0) {
				sb_in.append(c, 0, len);
			}
			String reText = sb_in.toString();
			if (t_ch != null && t_ch.length() != 0) {
				try {
					reText = new String(reText.getBytes(s_ch), t_ch);
				} catch (Exception e) {
				}
			}
			return reText;
		} catch (Exception e) {
			throw e;
		} finally {
			try {
				if (BR != null)
					BR.close();
			} catch (Exception e) {

			}
		}
	}

	public static String ymd2dmy(String sData) {
		String rtn = "";
		try {
			if ("".equals(sData)) {
				rtn = "";
			} else if (sData.length() < 10) {
				rtn = "";
			} else {
				rtn = sData.substring(8, 10) + "/" + sData.substring(5, 7)
						+ "/" + sData.substring(0, 4);
			}
		} catch (Exception e) {
			log.debug(e.toString());
		}
		return rtn;
	}
	public static String GetUrlDir(String url )
	{
		String dirurl="";
		if(url!=null&&url.indexOf("://")>0)
		{
			if(url.lastIndexOf('/')>url.indexOf("://")+2)
				dirurl= url.substring(0,url.lastIndexOf('/')+1);
			else
				dirurl= url+"/";
		}
		return dirurl;

		
	}
	public static String GetUrlCmd(String url )
	{
		String cmdurl="";
		if(url!=null)
		{
			if(url.indexOf('?')>0)
				cmdurl= url.substring(0,url.indexOf('?'));
			else
				cmdurl= url;
		}
		return cmdurl;
	}
	public static String GetUrlSite(String url )
	{
		String siteurl="";
		if(url!=null)
		{
			 Pattern urlPattern  =Pattern.compile("(((http|https)://)([a-zA-Z0-9-\\.:]+))(/?)(.*)");
			 Matcher urlMatcher = urlPattern.matcher(url);
			 if(urlMatcher.find()){
				 siteurl=urlMatcher.group(1);
			 }
		}
		return siteurl;
	}
	public static String BuildUrl(String href,String dir,String site,String cmd,String code)
	{
		String ret="";
		if(href!=null)
		{
			href = href.replaceAll("(#*)$", "");
			if(code!=null&&code.length()>0)
					href=Escape.escapech(href,code);
			if(href.length()==0||href.indexOf("javascript:")>=0)
				return ret;
			if(href.indexOf("http://")!=0&&href.indexOf("https://")!=0){
				if(href.indexOf('/')==0)
				{
					if(site.length()>0)
						ret=site+href;
				}
				else if(href.indexOf('?')==0)
				{
					if(cmd.length()>0)
						ret=cmd+href;
					else
						ret=dir+href;
				}else
				{
					if(dir.length()>0)
						ret=dir+href;
				}
			}else
			{
				ret=href;
			}
		}
		return ret;
	}
	public static String BuildUrl(String href,String dir,String site,String cmd)
	{
		String ret="";
		if(href!=null)
		{
			href = href.replaceAll("(#*)$", "");
			if(href.length()==0||href.indexOf("javascript:")>=0)
				return ret;
			if(href.indexOf("http://")!=0&&href.indexOf("https://")!=0){
				if(href.indexOf('/')==0)
				{
					if(site.length()>0)
						ret=site+href;
				}
				else if(href.indexOf('?')==0)
				{
					if(cmd.length()>0)
						ret=cmd+href;
					else
						ret=dir+href;
				}else
				{
					if(dir.length()>0)
						ret=dir+href;
				}
			}else
			{
				ret=href;
			}
		}
		return ret;
	}
	public static String BuildUrl(String href,String dir,String site)
	{
		String ret="";
		if(href!=null)
		{
			href = href.replaceAll("(#*)$", "");
			if(href.length()==0||href.indexOf("javascript:")>=0)
				return ret;
			if(href.indexOf("http://")!=0&&href.indexOf("https://")!=0){
				if(href.indexOf('/')==0)
				{
					if(site.length()>0)
						ret=site+href;
				}
				else
				{
					if(dir.length()>0)
						ret=dir+href;
				}
			}else
			{
				ret=href;
			}
		}
		return ret;
	}
	public static void main(String[] args) throws Exception {
		String url="http://blog.163.com/financeger.html";
		String href="http://blog.163.com/s_cheung/?fromFinance";
		String code=null;
		String urlsite=GetUrlSite( url );
		String urldir=GetUrlDir( url );
		String cmddir=GetUrlCmd( url );
		
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		href="aa";
		
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		
		url="http://www.ceh.com.cn:8080/epaper/ceh/";
		href="/epaper/ceh/hh";
		code="utf-8";
		urlsite=GetUrlSite( url );
		urldir=GetUrlDir( url );
		cmddir=GetUrlCmd( url );
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		href="rr";
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		href="/rr";
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		
		url="";
		href="/epaper/ceh/rr";
		urlsite=GetUrlSite( url );
		urldir=GetUrlDir( url );
		cmddir=GetUrlCmd( url );
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		href="rr";
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		
		url="http://bb.com";
		href="/epaper/ceh/rr";
		urlsite=GetUrlSite( url );
		urldir=GetUrlDir( url );
		cmddir=GetUrlCmd( url );
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		href="rr";
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		href="?rr";
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		
		url="http://aa.com/aa/b?cc";
		href="/epaper/ceh/rr";
		urlsite=GetUrlSite( url );
		urldir=GetUrlDir( url );
		cmddir=GetUrlCmd( url );
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		href="rr";
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		href="/rr";
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		href="?rr";
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		
		url="http://aa.com/aa/b?cc";
		href="/epaper/ceh/中国";
		urlsite=GetUrlSite( url );
		urldir=GetUrlDir( url );
		cmddir=GetUrlCmd( url );
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		href="中国";
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		href="/中国";
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		href="?中国";
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		
		url="http://aa.com/aa/b?cc";
		href="/epaper/ceh/中国";
		code="gb2312";
		urlsite=GetUrlSite( url );
		urldir=GetUrlDir( url );
		cmddir=GetUrlCmd( url );
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		href="中国";
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		href="/中国";
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		href="?中国";
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));
		
		url="http://www.yddb.cn/cn/index.php";
		href="news.php?nclass=中俄经贸要闻";
		code="gb2312";
		urlsite=GetUrlSite( url );
		urldir=GetUrlDir( url );
		cmddir=GetUrlCmd( url );
		System.out.println(BuildUrl(href,urldir,urlsite,cmddir,code));

	
	}
}
