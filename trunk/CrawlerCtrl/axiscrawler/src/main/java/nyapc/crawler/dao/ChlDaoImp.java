package nyapc.crawler.dao;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import nyapc.crawler.Util;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.springframework.dao.DataAccessException;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.PreparedStatementSetter;
import org.springframework.jdbc.core.RowCallbackHandler;

import org.springframework.jdbc.core.RowMapper;

import java.security.*;
import java.util.List;
public class ChlDaoImp implements ChlDao {
	private static Log log = LogFactory.getLog(ChlDaoImp.class.getName());	
	private JdbcTemplate jdbcTemplate;
	public JdbcTemplate getJdbcTemplate() {
		return jdbcTemplate;
	}
	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	
	@Override
	public ChlAtt get(int id) {
		// TODO Auto-generated method stub
		final ChlAtt tmp = new ChlAtt();  
		jdbcTemplate.query("select * from chl_list  where chl_id = ?",  
		                   new Object[] {String.valueOf(id)},  
		                    new RowCallbackHandler() {  
		                         public void processRow(ResultSet rs) throws SQLException {  
		         					tmp.setId(rs.getInt("CHL_ID"));
		        					tmp.setName(rs.getString("CHL_NAME"));
		        					tmp.setUrl(rs.getString("CHL_URL"));
		        					tmp.setJobId(rs.getInt("JOB_ID"));  
		                         }  
		                     });
		if(tmp.getId()>0){
			return tmp;	
		}else{
			return null;
		}
		
	}
	
	@Override
	public List getChls(int jid,int num) {
		String sql = "select * from chl_list where job_id=? and rownum<=?";
		try {


			return jdbcTemplate.query(sql,new Object[]{String.valueOf(jid),String.valueOf(num)},new RowMapper() {
				public Object mapRow(ResultSet rs, int rowNum) throws SQLException  {
					final ChlAtt tmp=new ChlAtt();
					tmp.setId(rs.getInt("CHL_ID"));
					tmp.setName(rs.getString("CHL_NAME"));
					tmp.setUrl(rs.getString("CHL_URL"));
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
	public int puttChl(ChlAtt chl) {
		try {
			final String hash=AeSimpleSHA1.SHA1(chl.getUrl());
			final String url=chl.getUrl();
			final String name=chl.getName();
			final int jobid=chl.getJobId();
			final int chlId=jdbcTemplate.queryForInt("select chl_id_sequence.nextval from dual");
			jdbcTemplate.update("insert into chl_list(CHL_ID,CHL_HASH,CHL_URL,CHL_NAME,CREATE_TIME,JOB_ID,CHL_STAT,UPDATE_TIME,FAIL_COUNT) values(?,?,?,?,sysdate,?,'0',sysdate,0)",new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setInt(1,jobid);
					ps.setString(2,hash);
					ps.setString(3,url);
					ps.setString(4,name);
					ps.setInt(5,jobid);
				}
			});
			return chlId;

		} catch (DataAccessException e) {
			log.debug(e.toString());

			return -1;
		} catch (NoSuchAlgorithmException e) {
			log.debug(e.toString());

			return -1;
		}

	}
	@Override
	public boolean updateStat(int id, String stat) {

		try {
			final String chlstat=stat;
			final int chlid=id;
			jdbcTemplate.update("update chl_list set chl_stat=?,update_time=sysdate where chl_id=?",
					new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setString(1,chlstat);
					ps.setInt(2,chlid);
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
			jdbcTemplate.update("update chl_list set chl_stat=?,update_time=sysdate where job_id=?",
					new PreparedStatementSetter(){
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
			final String preStatus=pre_status;
			jdbcTemplate.update("update chl_list set chl_stat=?,update_time=sysdate where job_id=? and chl_stat=?",
					new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setString(1,chlstat);
					ps.setInt(2,jobId);
					ps.setString(3,preStatus);
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
	public int GetId(String hash) {
		try{
			int id=jdbcTemplate.queryForInt("select chl_id from chl_list where chl_hash=?",new Object[]{hash});
			return id;
		} catch (DataAccessException e) {
			return -1;
		}
	}
	@Override
	public int getJobId(int chlId) {
		try{
			int jobid=jdbcTemplate.queryForInt("select job_id from chl_list where chl_id=?",new Object[]{chlId});
			return jobid;
		} catch (DataAccessException e) {
			return -1;
		}
	}
	@Override
	public int getFailCount(int chlId) {
		// TODO Auto-generated method stub
		try{
			int failCount = jdbcTemplate.queryForInt("select fail_count from chl_list where chl_id=?",new Object[]{chlId});
			return failCount;
		} catch (DataAccessException e) {
			return 0;
		}		
	}
	@Override
	public boolean updateFailCount(int chlId) {
		// TODO Auto-generated method stub
		try {
			final int chlid=chlId;
			jdbcTemplate.update("update chl_list set fail_count=fail_count+1 where chl_id=?",
					new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setInt(1,chlid);
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
	public boolean resetFailCount(int chlId) {

		try {
			final int chlid = chlId;
			jdbcTemplate.update("update chl_list set fail_count=0 where chl_id=?",
					new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setInt(1,chlid);
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
	public boolean updateStat(int id, String stat, String oldstat) {
		try {
			final String chlstat=stat;
			final String oldchlstat=oldstat;
			final int chlid=id;
			jdbcTemplate.update("update chl_list set chl_stat=?,update_time=sysdate where chl_id=? and chl_stat=?",
					new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setString(1,chlstat);
					ps.setInt(2,chlid);
					ps.setString(3,oldchlstat);
				}
			});
			return true;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return false;
		}
	}	

}
