package nyapc.crawler.dao;

public class TaskAtt  {
	private int taskId;
	private int jobId;
	private int wrapperId;
	private int wrapperVersion;
	private int jobType;
	private int crawlerId;
	private String ids;
	private String createTime;
	private int taskStatus;
	private String urls;
	public int getTaskId() {
		return taskId;
	}
	public void setTaskId(int taskId) {
		this.taskId = taskId;
	}
	public int getJobId() {
		return jobId;
	}
	public void setJobId(int jobId) {
		this.jobId = jobId;
	}
	public int getWrapperId() {
		return wrapperId;
	}
	public void setWrapperId(int wrapperId) {
		this.wrapperId = wrapperId;
	}
	public int getJobType() {
		return jobType;
	}
	public void setJobType(int jobType) {
		this.jobType = jobType;
	}
	public int getCrawlerId() {
		return crawlerId;
	}
	public void setCrawlerId(int crawlerId) {
		this.crawlerId = crawlerId;
	}
	public String getIds() {
		return ids;
	}
	public void setIds(String ids) {
		this.ids = ids;
	}
	public String getCreateTime() {
		return createTime;
	}
	public void setCreateTime(String createTime) {
		this.createTime = createTime;
	}
	public int getTaskStatus() {
		return taskStatus;
	}
	public void setTaskStatus(int taskStatus) {
		this.taskStatus = taskStatus;
	}
	public String getUrls() {
		return urls;
	}
	public void setUrls(String urls) {
		this.urls = urls;
	}
	public int getWrapperVersion() {
		return wrapperVersion;
	}
	public void setWrapperVersion(int wrapperVersion) {
		this.wrapperVersion = wrapperVersion;
	}
}
