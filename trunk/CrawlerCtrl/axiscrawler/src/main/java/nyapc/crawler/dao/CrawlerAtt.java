package nyapc.crawler.dao;

public class CrawlerAtt  {

	private int crawlerId;
	private String  crawlerName;
	private int  crawlerStatus;
	private String  createTime;
	private String  updateTime;
	private int  agentId;
	
	public int getCrawlerId() {
		return crawlerId;
	}
	public void setCrawlerId(int crawlerId) {
		this.crawlerId = crawlerId;
	}
	public String getCrawlerName() {
		return crawlerName;
	}
	public void setCrawlerName(String crawlerName) {
		this.crawlerName = crawlerName;
	}
	public int getCrawlerStatus() {
		return crawlerStatus;
	}
	public void setCrawlerStatus(int crawlerStatus) {
		this.crawlerStatus = crawlerStatus;
	}
	public String getCreateTime() {
		return createTime;
	}
	public void setCreateTime(String createTime) {
		this.createTime = createTime;
	}
	public String getUpdateTime() {
		return updateTime;
	}
	public void setUpdateTime(String updateTime) {
		this.updateTime = updateTime;
	}
	public int getAgentId() {
		return agentId;
	}
	public void setAgentId(int agentId) {
		this.agentId = agentId;
	}
}
