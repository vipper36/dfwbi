package nyapc.crawler.dao;

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


public class CookieDaoImp implements CookieDao {
	private static Log log = LogFactory.getLog(CrawlerDaoImp.class.getName());	
	private JdbcTemplate jdbcTemplate;
	public JdbcTemplate getJdbcTemplate() {
		return jdbcTemplate;
	}
	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}
	@Override
	public int AddCookie(CookieAtt cook) {
		try {
			final String cookStr=cook.getCookieStr();
			final int jobid=cook.getJobId();
			final String logName=cook.getLogName();
			final String logPass=cook.getLogPass();
			final String cookType=cook.getCookieType();
			final String logUrl=cook.getLogUrl();
			final int cookId=jdbcTemplate.queryForInt("select cook_id_sequence.nextval from dual");
			
			String sql = " INSERT INTO COOKIE_LIST(cookie_id,login_url,login_name,login_pass,job_id,cookie_string,cookie_type,create_time)" 
			    + " VALUES(?,?,?,?,?,?,?,sysdate)"; 
			 jdbcTemplate.update(sql,new PreparedStatementSetter(){
			       public void setValues(PreparedStatement ps) throws SQLException{
			    	   ps.setInt(1, cookId); 
				          ps.setString(2, logUrl);   
				          ps.setString(3, logName);   
				          ps.setString(4, logPass);
				          ps.setInt(5, jobid);
				          ps.setString(6,cookStr);
				          ps.setString(7,cookType);
			       }
			});
			return cookId;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return -1;
		} 
		
	}

	@Override
	public void SetCookieStr(int jid, String cookie) {
		try {
			jdbcTemplate.update("update COOKIE_LIST set cookie_string=? where job_id=?", new Object[] { cookie,String.valueOf(jid) });
			return;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return;
		}

	}

	@Override
	public CookieAtt getCookie(int id) {
		try {
			final CookieAtt tmp=new CookieAtt();
			String sql = "select cookie_id,login_url,login_name,login_pass,job_id,cookie_string from COOKIE_LIST where cookie_id=?";
			jdbcTemplate.query(sql, new Object[]{id},
					new RowCallbackHandler() {
				 public void processRow(ResultSet rs) throws SQLException { 
					tmp.setCookieId(rs.getInt("COOKIE_ID"));
			        tmp.setLogUrl(rs.getString("LOGIN_URL"));
			        tmp.setLogName(rs.getString("LOGIN_NAME"));
			        tmp.setLogPass(rs.getString("LOGIN_PASS"));
			        tmp.setJobId(rs.getInt("JOB_ID"));
					tmp.setCookieStr(rs.getString("COOKIE_STRING"));	        
			      }
			    });
			return tmp;
		} catch (DataAccessException e) {
			e.printStackTrace();
			return null;
		} 
	}

	@Override
	public CookieAtt getCookieByJobId(int jid) {
		try {
			final CookieAtt tmp=new CookieAtt();
			String sql = "select cookie_id,login_url,login_name,login_pass,job_id,cookie_string from COOKIE_LIST where job_id=?";
			jdbcTemplate.query(sql, new Object[]{jid},
					new RowCallbackHandler() {
				 public void processRow(ResultSet rs) throws SQLException { 
					tmp.setCookieId(rs.getInt("COOKIE_ID"));
			        tmp.setLogUrl(rs.getString("LOGIN_URL"));
			        tmp.setLogName(rs.getString("LOGIN_NAME"));
			        tmp.setLogPass(rs.getString("LOGIN_PASS"));
			        tmp.setJobId(rs.getInt("JOB_ID"));
					tmp.setCookieStr(rs.getString("COOKIE_STRING"));	        
			      }
			    });
			return tmp;
		} catch (DataAccessException e) {
			e.printStackTrace();
			return null;
		}
	}
	@Override
	public List<Integer> getAllJobId() {
		String sql = "select distinct job_id from cookie_list where cookie_type=0";
		 try {
				return jdbcTemplate.query(sql,new RowMapper() {
						public Object mapRow(ResultSet rs, int rowNum) throws SQLException  {
							final Integer tmp=new Integer(rs.getInt("JOB_ID"));		        	
				        	return tmp;
				        }
				    } );

			} catch (DataAccessException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return null;
			}
	}

}
