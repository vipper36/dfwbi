package nyapc.crawler.dao;

public class CookieAtt {
	public int getCookieId() {
		return cookieId;
	}
	public void setCookieId(int cookieId) {
		this.cookieId = cookieId;
	}
	public String getLogUrl() {
		return logUrl;
	}
	public void setLogUrl(String logUrl) {
		this.logUrl = logUrl;
	}
	public String getLogName() {
		return logName;
	}
	public void setLogName(String logName) {
		this.logName = logName;
	}
	public String getLogPass() {
		return logPass;
	}
	public void setLogPass(String logPass) {
		this.logPass = logPass;
	}
	public int getJobId() {
		return jobId;
	}
	public void setJobId(int jobId) {
		this.jobId = jobId;
	}
	public String getCookieStr() {
		return cookieStr;
	}
	public void setCookieStr(String cookieStr) {
		this.cookieStr = cookieStr;
	}
	public String getCookieType() {
		return cookieType;
	}
	public void setCookieType(String cookieType) {
		this.cookieType = cookieType;
	}
	private int cookieId;
	private String logUrl;
	private String logName;
	private String logPass;
	private int jobId;
	private String cookieStr;
	
	private String cookieType;
}
