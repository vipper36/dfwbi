package nyapc.crawler.dao;

public class JobAtt {
	public int getId() {
		return Id;
	}
	public void setId(int id) {
		Id = id;
	}
	public String getName() {
		return Name;
	}
	public void setName(String name) {
		Name = name;
	}
	public String getComment() {
		return Comment;
	}
	public void setComment(String comment) {
		Comment = comment;
	}
	public String getSeed() {
		return Seed;
	}
	public void setSeed(String seed) {
		Seed = seed;
	}
	public String getSeedType() {
		return SeedType;
	}
	public void setSeedType(String seedType) {
		SeedType = seedType;
	}
	private int Id;
	private String  Name;
	private String  Comment;

	private String  Seed;
	private String  SeedType;
	
	private String createTime;
	private String updateTime;
	private String jobStat;
	private String category;
	private String dredb;
	public int getInterval() {
		return interval;
	}
	public void setInterval(int interval) {
		this.interval = interval;
	}
	public String getUpdateFlag() {
		return updateFlag;
	}
	public void setUpdateFlag(String updateFlag) {
		this.updateFlag = updateFlag;
	}
	private int interval;
	private String updateFlag;
	public String getCategory() {
		return category;
	}
	public void setCategory(String category) {
		this.category = category;
	}
	public String getDredb() {
		return dredb;
	}
	public void setDredb(String dredb) {
		this.dredb = dredb;
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
	public String getJobStat() {
		return jobStat;
	}
	public void setJobStat(String jobStat) {
		this.jobStat = jobStat;
	}
}
