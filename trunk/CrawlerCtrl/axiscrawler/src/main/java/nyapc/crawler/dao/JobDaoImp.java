package nyapc.crawler.dao;

import java.security.NoSuchAlgorithmException;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


import org.springframework.context.NoSuchMessageException;
import org.springframework.dao.DataAccessException;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.PreparedStatementSetter;
import org.springframework.jdbc.core.RowCallbackHandler;

import org.springframework.jdbc.core.RowMapper;

public class JobDaoImp implements JobDao {
	private Map<Integer,String> updateFlag=new HashMap<Integer,String>();
	public JdbcTemplate getJdbcTemplate() {
		return jdbcTemplate;
	}

	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	private JdbcTemplate jdbcTemplate;
	@Override
	public int AddJob(JobAtt jod) {

		try {
			final String seed=jod.getSeed();
			final String name=jod.getName();
			final String comment=jod.getComment();
			final String type=jod.getSeedType();
			final String catagory=jod.getCategory();
			final String dredb=jod.getDredb();
			final int interval=jod.getInterval();
			final String updateflag=jod.getUpdateFlag();
			final int jobId=jdbcTemplate.queryForInt("select job_id_sequence.nextval from dual");
			String sql="insert into job_list(job_id,job_name,job_comment,create_time,job_seed_url,job_seed_type,job_seed_category,dredb,update_time,interval,update_flag) values(?,?,?,sysdate,?,?,?,?,sysdate,?,?)";
			jdbcTemplate.update(sql,new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setInt(1, jobId);
					ps.setString(2,name);
					ps.setString(3,comment);
					ps.setString(4,seed);
					ps.setString(5,type);
					ps.setString(6,catagory);
					ps.setString(7,dredb);
					ps.setInt(8,interval);
					ps.setString(9,updateflag);
				}
			});
			return jobId;
		} catch (NoSuchMessageException e) {
			e.printStackTrace();
			return -1;
		} 
	}

	@Override
	public List getAllJob() {
		String sql = "select job_id,job_name,job_comment,job_seed_url,job_seed_type,to_char(create_time,'yyyy-mm-dd hh24:mi:ss') create_time,to_char(update_time,'yyyy-mm-dd hh24:mi:ss') update_time,job_stat,job_seed_category,dredb,interval,update_flag from job_list where job_stat=?";
		try {
			return jdbcTemplate.query(sql,new Object[]{"0"},new RowMapper() {
				public Object mapRow(ResultSet rs, int rowNum) throws SQLException  {
					final JobAtt tmp=new JobAtt();
					tmp.setId(rs.getInt("JOB_ID"));
					tmp.setName(rs.getString("JOB_NAME"));
					tmp.setComment(rs.getString("JOB_COMMENT"));
					tmp.setSeed(rs.getString("JOB_SEED_URL"));
					tmp.setSeedType(rs.getString("JOB_SEED_TYPE"));
					tmp.setCreateTime(rs.getString("create_time"));
					tmp.setUpdateTime(rs.getString("update_time"));
					tmp.setJobStat(rs.getString("job_stat"));
					tmp.setCategory(rs.getString("job_seed_category"));
					tmp.setDredb(rs.getString("dredb"));
					tmp.setUpdateFlag(rs.getString("update_flag"));
					tmp.setInterval(rs.getInt("interval"));
					return tmp;
				}
			} );

		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
	}


	@Override
	public List getAllJobWrapInvalid() {
		String sql = "select distinct j.job_id,j.job_name,j.job_comment,j.job_seed_url,w.wrap_type job_seed_type,to_char(j.create_time,'yyyy-mm-dd hh24:mi:ss') create_time,to_char(j.update_time,'yyyy-mm-dd hh24:mi:ss') update_time,j.job_stat,job_seed_category,dredb,interval,update_flag  from job_list j ,wrapper_list w  where w.wrap_stat=? and j.job_id=w.job_id";
		try {
			return jdbcTemplate.query(sql,new Object[]{"-1"},new RowMapper() {
				public Object mapRow(ResultSet rs, int rowNum) throws SQLException  {
					final JobAtt tmp=new JobAtt();
					tmp.setId(rs.getInt("JOB_ID"));

					tmp.setName(rs.getString("JOB_NAME"));
					tmp.setComment(rs.getString("JOB_COMMENT"));
					tmp.setSeed(rs.getString("JOB_SEED_URL"));
					tmp.setSeedType(rs.getString("JOB_SEED_TYPE"));
					tmp.setCreateTime(rs.getString("create_time"));
					tmp.setUpdateTime(rs.getString("update_time"));
					tmp.setJobStat(rs.getString("job_stat"));
					tmp.setCategory(rs.getString("job_seed_category"));
					tmp.setDredb(rs.getString("dredb"));
					tmp.setUpdateFlag(rs.getString("update_flag"));
					tmp.setInterval(rs.getInt("interval"));
					return tmp;
				}
			} );

		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
	}
	@Override
	public List getAllJobWrapStudy() {
		String sql = "select distinct j.job_id,j.job_name,j.job_comment,j.job_seed_url,w.wrap_type job_seed_type,to_char(j.create_time,'yyyy-mm-dd hh24:mi:ss') create_time,to_char(j.update_time,'yyyy-mm-dd hh24:mi:ss') update_time,j.job_stat,job_seed_category,dredb,interval,update_flag  from job_list j ,wrapper_study w  where j.job_id=w.job_id";
		try {
			return jdbcTemplate.query(sql,new RowMapper() {
				public Object mapRow(ResultSet rs, int rowNum) throws SQLException  {
					final JobAtt tmp=new JobAtt();
					tmp.setId(rs.getInt("JOB_ID"));

					tmp.setName(rs.getString("JOB_NAME"));
					tmp.setComment(rs.getString("JOB_COMMENT"));
					tmp.setSeed(rs.getString("JOB_SEED_URL"));
					tmp.setSeedType(rs.getString("JOB_SEED_TYPE"));
					tmp.setCreateTime(rs.getString("create_time"));
					tmp.setUpdateTime(rs.getString("update_time"));
					tmp.setJobStat(rs.getString("job_stat"));
					tmp.setCategory(rs.getString("job_seed_category"));
					tmp.setDredb(rs.getString("dredb"));
					tmp.setUpdateFlag(rs.getString("update_flag"));
					tmp.setInterval(rs.getInt("interval"));
					return tmp;
				}
			} );

		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
	}
	/*
	 * @brief update the column or channel of the job.
	 * 			when update flag equals '2' get the interval from the job_list.
	 * @see nyapc.crawler.dao.JobDao#updateJob(int)
	 */
	
	@Override
	public boolean updateJob(int jid) {
		// TODO Auto-generated method stub

		final JobAtt job=getJob(jid);
		final String stat = job.getJobStat();

		if("1".equals(job.getSeedType()))
		{
			try {

				int chlCount=jdbcTemplate.queryForInt("select count(*) from chl_list where job_id=?　",new Object[]{String.valueOf(jid)});
				if(chlCount>0)
				{
					String updateFlag=job.getUpdateFlag();
					int interval=0;
					if("2".equals(updateFlag))
					{
						interval=-job.getInterval();
					}else
					{
						interval=-1200;
					}
					Calendar curr = Calendar.getInstance();

					curr.add(Calendar.SECOND, interval);

					SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

					final String currTime=sdf.format(curr.getTime());

					final int job_id=jid;
					jdbcTemplate.update("update chl_list set chl_stat=?,update_time=sysdate where chl_stat='2' and job_id=? and update_time<to_date(?,'yyyy-mm-dd hh24:mi:ss')",
							new PreparedStatementSetter(){
						public void setValues(PreparedStatement ps) throws SQLException{
							ps.setString(1,stat);
							ps.setInt(2,job_id);
							ps.setString(3,currTime);
						}
					});
				}else
				{
					try {
						final String hash=AeSimpleSHA1.SHA1(job.getSeed());
						final String url=job.getSeed();
						final String name=job.getComment();
						final int jobid=job.getId();
						jdbcTemplate.update("insert into chl_list(chl_id, chl_hash, chl_url, chl_name, create_time, job_id, chl_stat, update_time) values(chl_id_sequence.nextval,?,?,?,sysdate,?,'0',sysdate)",new PreparedStatementSetter(){
							public void setValues(PreparedStatement ps) throws SQLException{
								ps.setString(1,hash);
								ps.setString(2,url);
								ps.setString(3,name);
								ps.setInt(4,jobid);
							}
						});
						System.out.println("insert into chl_list(chl_id, chl_hash, chl_url, chl_name, create_time, job_id, chl_stat, update_time) values(chl_id_sequence.nextval,?,?,?,sysdate,?,'0',sysdate)");
					} catch (NoSuchAlgorithmException e) {
						e.printStackTrace();
					}
				}
				return true;
			} catch (DataAccessException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return false;
			} 
		}else if("2".equals(job.getSeedType()))
		{
			try {
				int colCount=jdbcTemplate.queryForInt("select count(*) from col_list where job_id=?",new Object[]{String.valueOf(jid)});
				if(colCount>0)
				{
					String updateFlag=job.getUpdateFlag();
					int interval=0;
					if("2".equals(updateFlag))
					{
						interval=-job.getInterval();
					}else
					{
						interval=-1200;
					}
					Calendar curr = Calendar.getInstance();

					curr.add(Calendar.SECOND, interval);

					SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

					final String currTime=sdf.format(curr.getTime());
					
					final int job_id=jid;
					jdbcTemplate.update("update col_list set col_stat=?,update_time=sysdate where col_stat='2' and col_id=(select min(col_id) from col_list where job_id=?) and update_time<to_date(?,'yyyy-mm-dd hh24:mi:ss')",
							new PreparedStatementSetter(){
						public void setValues(PreparedStatement ps) throws SQLException{
							ps.setString(1,stat);
							ps.setInt(2,job_id);
							ps.setString(3,currTime);
						}
					});
					

				}else
				{

					try {
						final String hash=AeSimpleSHA1.SHA1(job.getSeed());
						final String urlstr=job.getSeed();
						final String name=job.getComment();
						final int jobid=job.getId();
						final int chlid=-1;
						jdbcTemplate.update("insert into col_list(col_id,col_hash,col_url,col_name,chl_id,create_time,col_stat,job_id, update_time) values(col_id_sequence.nextval,?,?,?,?,sysdate,'0',?,sysdate)",new PreparedStatementSetter(){
							public void setValues(PreparedStatement ps) throws SQLException{
								ps.setString(1,hash);
								ps.setString(2,urlstr);
								ps.setString(3,name);
								ps.setInt(4,chlid);
								ps.setInt(5,jobid);
							}
						});
						return true;
					} catch (NoSuchAlgorithmException e) {
						e.printStackTrace();
						return false;
					}

				}
				return true;
			} catch (DataAccessException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return false;
			}
		}

		return false;
	}

	@Override
	public JobAtt getJob(int jid) {
		try {
			final JobAtt tmp=new JobAtt();
			String sql = "select job_id,job_name,job_comment,job_seed_url,job_seed_type,to_char(create_time,'yyyy-mm-dd hh24:mi:ss') create_time,to_char(update_time,'yyyy-mm-dd hh24:mi:ss') update_time,job_stat,JOB_SEED_CATEGORY,DREDB,interval,update_flag  from job_list where job_id=?";
			jdbcTemplate.query(sql, new Object[]{jid},
					new RowCallbackHandler() {
				public void processRow(ResultSet rs) throws SQLException { 
					tmp.setId(rs.getInt("JOB_ID"));
					tmp.setName(rs.getString("JOB_NAME"));
					tmp.setComment(rs.getString("JOB_COMMENT"));
					tmp.setSeed(rs.getString("JOB_SEED_URL"));
					tmp.setSeedType(rs.getString("JOB_SEED_TYPE"));
					tmp.setCreateTime(rs.getString("create_time"));
					tmp.setUpdateTime(rs.getString("update_time"));
					tmp.setJobStat(rs.getString("job_stat"));	
					tmp.setCategory(rs.getString("JOB_SEED_CATEGORY"));
					tmp.setDredb(rs.getString("DREDB"));
					tmp.setUpdateFlag(rs.getString("update_flag"));
					tmp.setInterval(rs.getInt("interval"));
				}
			});
			return tmp;
		} catch (DataAccessException e) {
			e.printStackTrace();
			return null;
		} 
	}


	@Override
	public int del(int id) {
		// TODO Auto-generated method stub
		try {
			final String idStr = String.valueOf(id);
			//-1无效
			jdbcTemplate.update("update job_list set job_stat=?,update_time=sysdate where job_id=?", new Object[] { "-1",String.valueOf(id) });			
			return 1;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return 0;
		}
	}

	@Override
	public int updateJobUrl(int jobId,String url) {
		// TODO Auto-generated method stub
		try {
			jdbcTemplate.update("update job_list set job_seed_url=?,update_time=sysdate where job_id=?", new Object[] { url,String.valueOf(jobId) });
			int type=jdbcTemplate.queryForInt("select job_seed_type from job_list where job_id=?",new Object[]{String.valueOf(jobId)});
			if(type==1){
				jdbcTemplate.update("update chl_list set chl_url=?,update_time=sysdate where job_id=?", new Object[] { url,String.valueOf(jobId) });
			}else if(type==2){
				jdbcTemplate.update("update col_list set col_url=?,update_time=sysdate where job_id=?", new Object[] { url,String.valueOf(jobId) });
			}
			return 1;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return 0;
		}
	}	

	@Override
	public boolean needUpdate(int jobId)
	{

		try {

			String flag=updateFlag.get(jobId);
			if(flag!=null)
			{
				if("0".equals(flag))
				{
					return false;
				}
			}else
			{
				String newflag=(String)jdbcTemplate.queryForObject("select j.update_flag from job_list j,col_list c where j.job_id=c.job_id and c.col_id=?",new Object[]{jobId},java.lang.String.class);
				updateFlag.put(jobId, newflag);
				if("0".equals(flag))
				{
					return false;
				}
			}
		} catch (DataAccessException e) {
			return false;
		}

		return true;
	}
}
