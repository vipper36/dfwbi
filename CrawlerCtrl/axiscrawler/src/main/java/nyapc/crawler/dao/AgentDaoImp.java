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
public class AgentDaoImp implements AgentDao {
	private static Log log = LogFactory.getLog(AgentDaoImp.class.getName());	
	private JdbcTemplate jdbcTemplate;
	public JdbcTemplate getJdbcTemplate() {
		return jdbcTemplate;
	}
	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	@Override
	public int del(int id) {
		// TODO Auto-generated method stub
		try {
			final String idStr = ""+id;
//			jdbcTemplate.update("delete from agent_info where agent_id=?",new PreparedStatementSetter(){
//				public void setValues(PreparedStatement ps) throws SQLException{
//					ps.setString(1,idStr);
//				}
//			});
			jdbcTemplate.update("delete from agent_list where agent_id=?", new Object[] { String.valueOf(id)  });			
			return -1;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return 1;
		}		
	}

	@Override
	public AgentAtt get(int id) {
		// TODO Auto-generated method stub
		final AgentAtt theAgentAtt = new AgentAtt();  
		jdbcTemplate.query("select * from agent_list  where agent_id = ?",  
		                   new Object[] {String.valueOf(id)},  
		                    new RowCallbackHandler() {  
		                         public void processRow(ResultSet rs) throws SQLException {  
		                        	 theAgentAtt.setAgentId(Util.str2int(rs.getString("agent_id")));  
		                        	 theAgentAtt.setAgentName(rs.getString("agent_name"));  
		                        	 theAgentAtt.setAgentDesc(rs.getString("agent_desc"));  
		                        	 theAgentAtt.setAgentIp(rs.getString("agent_ip"));  
		                         }  
		                     });
		if(theAgentAtt.getAgentId()>0){
			return theAgentAtt;	
		}else{
			return null;
		}
		
	}

	@Override
	public List list() {
		// TODO Auto-generated method stub
		String sql = "select * from agent_list order by agent_id";
		try {
			return jdbcTemplate.query(sql,new RowMapper() {
				public Object mapRow(ResultSet rs, int rowNum) throws SQLException  {
					final AgentAtt theAgentAtt = new AgentAtt(); 
					theAgentAtt.setAgentId(Util.str2int(rs.getString("agent_id")));  
               	 	theAgentAtt.setAgentName(rs.getString("agent_name"));  
               	 	theAgentAtt.setAgentDesc(rs.getString("agent_desc"));  
               	 	theAgentAtt.setAgentIp(rs.getString("agent_ip"));
					return theAgentAtt;
				}
			} );

		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return null;
		}
	}

	@Override
	public int save(AgentAtt agentAtt) {
		// TODO Auto-generated method stub
		try {
			final String agentName = agentAtt.getAgentName();
			final String agentDesc = agentAtt.getAgentDesc();
			final String agentIp =  agentAtt.getAgentIp();

			if(agentAtt.getAgentId()==0){
				final int agentId = jdbcTemplate.queryForInt("select seq_agent_list.nextval from dual");
				jdbcTemplate.update("insert into agent_list(agent_id,agent_name,agent_desc,agent_ip) values(?,?,?,?)",new PreparedStatementSetter(){
					public void setValues(PreparedStatement ps) throws SQLException{
						ps.setLong(1,agentId);
						ps.setString(2,agentName);
						ps.setString(3,agentDesc);
						ps.setString(4,agentIp);
					}
				});
				return agentId;
			}else{
				final int agentId = agentAtt.getAgentId();
				jdbcTemplate.update("update agent_list set agent_name=?,agent_desc=?,agent_ip=? where agent_id=?",new PreparedStatementSetter(){
					public void setValues(PreparedStatement ps) throws SQLException{
						ps.setString(1,agentName);
						ps.setString(2,agentDesc);
						ps.setString(3,agentIp);
						ps.setLong(4,agentId);
					}
				});
				return agentId;
			}
		} catch (DataAccessException e) {
			log.debug(e.toString());
			return -1;
		}
	}
}


