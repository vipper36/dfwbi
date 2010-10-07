package nyapc.crawler.dao;

public class LonginInfo {
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
	public String getLogUrl() {
		return logUrl;
	}
	public void setLogUrl(String logUrl) {
		this.logUrl = logUrl;
	}
	private String logName;
	private String logPass;
	private String logUrl;
	
}
