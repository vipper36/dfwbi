package nyapc.crawler.dao;

public class WrapAtt {
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public String getType() {
		return type;
	}
	public void setType(String type) {
		this.type = type;
	}
	public String getWrapper() {
		return Wrapper;
	}
	public void setWrapper(String wrapper) {
		Wrapper = wrapper;
	}
	public int getJobid() {
		return jobid;
	}
	public void setJobid(int jobid) {
		this.jobid = jobid;
	}
	public String getComment() {
		return comment;
	}
	public void setComment(String comment) {
		this.comment = comment;
	}

	public int getVersion() {
		return version;
	}
	public void setVersion(int version) {
		this.version = version;
	}
	public String getVargen() {
		return vargen;
	}
	public void setVargen(String vargen) {
		this.vargen = vargen;
	}
	private int id;
	private String type;
	private String Wrapper;
	private int jobid;
	private String comment;
	private int version;
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
	public String getWrapStat() {
		return wrapStat;
	}
	public void setWrapStat(String wrapStat) {
		this.wrapStat = wrapStat;
	}
	private String createTime;
	private String updateTime;
	private String wrapStat;
	


	private String vargen;
}
