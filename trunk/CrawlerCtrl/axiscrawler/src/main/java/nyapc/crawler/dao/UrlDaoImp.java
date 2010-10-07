package nyapc.crawler.dao;

import java.security.NoSuchAlgorithmException;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.springframework.dao.DataAccessException;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.PreparedStatementSetter;
import org.springframework.jdbc.core.RowCallbackHandler;
import org.springframework.jdbc.core.RowMapper;


public class UrlDaoImp implements UrlDao {
	private static Log log = LogFactory.getLog(UrlDaoImp.class.getName());	
	private JdbcTemplate jdbcTemplate;
	public JdbcTemplate getJdbcTemplate() {
		return jdbcTemplate;
	}

	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	@Override
	public boolean AddCol(int id, int colid) {
		log.debug("add col:"+id+":"+colid);
		try {
			final int urlid=id;
			final int colidf=colid;
			
			int colCount=jdbcTemplate.queryForInt("select count(*) from url_att where url_id=? and col_id=?",new Object[]{String.valueOf(urlid),String.valueOf(colid)});
			System.out.println("att count:"+colCount);
			if(colCount==0)
			{
				jdbcTemplate.update("insert into url_att(url_att_id,url_id,col_id,create_time) values(url_att_seq.nextval,?,?,sysdate)",new PreparedStatementSetter(){
					public void setValues(PreparedStatement ps) throws SQLException{
						ps.setInt(1,urlid);
						ps.setInt(2,colidf);
					}
				});
			}
			return true;
		} catch (DataAccessException e) {
			//log.debug(e.toString());
			return false;
		}
	}


	@Override
	public List getUrls(int jid,int num) {

		try {
			String sql = "select * from url_list where job_id=? and rownum<=?";


			return jdbcTemplate.query(sql,new Object[]{""+jid,""+num},new RowMapper() {
				public Object mapRow(ResultSet rs, int rowNum) throws SQLException  {
					final UrlAtt tmp=new UrlAtt();
					tmp.setId(rs.getInt("URL_ID"));
					tmp.setName(rs.getString("URL_NAME"));
					tmp.setUrl(rs.getString("URL_URL"));
					tmp.setJobId(rs.getInt("JOB_ID"));
					return tmp;
				}
			} );

		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return null;
		}
	}
	
	@Override
	public int puttUrl(UrlAtt url) {
		try {
			final String hash=AeSimpleSHA1.SHA1(url.getUrl());
			final String urlstr=url.getUrl();
			String tmpName=url.getName();
			if(tmpName.length()>1000)
			{
				tmpName=tmpName.substring(0,500);
			}
			final String name=tmpName;
			final int jobid=url.getJobId();
			if(jobid>0)
			{
				final int urlId=jdbcTemplate.queryForInt("select url_id_sequence.nextval from dual");
				log.debug(name+urlstr+jobid);
				jdbcTemplate.update("insert into url_list(url_id,url_hash,url_url,url_name,create_time,url_stat,job_id) values(?,?,?,?,sysdate,'0',?)",new PreparedStatementSetter(){
					public void setValues(PreparedStatement ps) throws SQLException{
						ps.setInt(1,urlId);
						ps.setString(2,hash);
						ps.setString(3,urlstr);
						ps.setString(4,name);
						ps.setInt(5,jobid);
					}
				});
				return urlId;
			}else
			{
				return -1;
			}
		} catch (NoSuchAlgorithmException e) {
			log.debug(e.toString());
			return -1;
		}
	}

	@Override
	public boolean updateStat(int id, String stat) {
		try {
			final String chlstat=stat;
			final int urlid=id;
			jdbcTemplate.update("update url_list set url_stat=? where url_id=?",new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setString(1,chlstat);
					ps.setInt(2,urlid);
				}
			});
			return true;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return false;
		}
	}
	
	
	@Override
	public boolean updateStatByJobId(int id, String stat) {
		try {
			final String chlstat=stat;
			final int jobId=id;
			jdbcTemplate.update("update url_list set url_stat=? where job_id=?",new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setString(1,chlstat);
					ps.setInt(2,jobId);
				}
			});
			return true;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return false;
		}
	}

	@Override
	public boolean updateStatByJobIdAndStatus(int id,String pre_status, String stat) {
		try {
			final String chlstat=stat;
			final int jobId=id;
			final String preStatus = pre_status;
			String sql="update url_list set url_stat=? where job_id=?  and url_stat=?";
			if ("9".equals(stat))
			{
				sql=sql+" and create_time>sysdate-1";
			}
			log.debug("stat:"+stat+" sql:"+sql);
			jdbcTemplate.update(sql,new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setString(1,chlstat);
					ps.setInt(2,jobId);
					ps.setString(3, preStatus);
				}
			});
			return true;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return false;
		}
	}
	
	public int GetId(String hash) {
		try{
			int id=jdbcTemplate.queryForInt("select url_id from url_list where url_hash=?",new Object[]{hash});
			return id;
		} catch (DataAccessException e) {
			return -1;
		}
	}
	public int getJobId(int urlId) {
		try{

			int jobid=jdbcTemplate.queryForInt("select job_id from url_list where url_id=?",new Object[]{urlId});
			return jobid;
		} catch (DataAccessException e) {
			return -1;
		}
	}

	@Override
	public List<Integer> getColIds(int urlId) {
		// TODO Auto-generated method stub
		try {
			String sql = "select col_id from url_att where url_id=?";
			return jdbcTemplate.query(sql,new Object[]{urlId},new RowMapper() {
				public Object mapRow(ResultSet rs, int rowNum) throws SQLException  {
					return rs.getInt("COL_ID");
				}
			} );

		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return null;
		}
	}
	
	@Override
	public int getFailCount(int urlId) {
		// TODO Auto-generated method stub
		try{
			int failCount = jdbcTemplate.queryForInt("select fail_count from url_list where url_id=?",new Object[]{urlId});
			return failCount;
		} catch (DataAccessException e) {
			return 0;
		}		
	}
	@Override
	public boolean updateFailCount(int urlId) {
		// TODO Auto-generated method stub
		try {
			final int urlid=urlId;
			jdbcTemplate.update("update url_list set fail_count=fail_count+1 where url_id=?",
					new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setInt(1,urlid);
				}
			});
			return true;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return false;
		}
	}
	
	@Override
	public boolean resetFailCount(int urlId) {

		try {
			final int urlid = urlId;
			jdbcTemplate.update("update url_list set fail_count=0 where url_id=?",
					new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setInt(1,urlid);
				}
			});
			return true;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return false;
		}

	}	
	
	@Override
	public void deleteall() {
		try {
			jdbcTemplate.update("delete from url_list");
		} catch (DataAccessException e) {
			//log.debug(e.toString());
		}
	}

	@Override
	public UrlAtt getUrl(int urlId) {
		try {
			final UrlAtt tmp=new UrlAtt();
			String sql = "select * from url_list where url_id=?";
			jdbcTemplate.query(sql, new Object[]{urlId},
					new RowCallbackHandler() {
				 public void processRow(ResultSet rs) throws SQLException { 

					tmp.setId(rs.getInt("URL_ID"));

					tmp.setName(rs.getString("URL_NAME"));
					tmp.setUrl(rs.getString("URL_URL"));
					tmp.setJobId(rs.getInt("JOB_ID"));
					 
			      }
			    });
			return tmp;
		} catch (DataAccessException e) {
			log.debug(e.toString());
			return null;
		} 
	}	
}
